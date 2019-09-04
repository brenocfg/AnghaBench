#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_9__ {int image_width; int image_height; int image_row_pitch; int /*<<< orphan*/  image_channel_order; int /*<<< orphan*/  image_channel_data_type; int /*<<< orphan*/  image_type; } ;
typedef  TYPE_1__ cl_image_format ;
typedef  TYPE_1__ cl_image_desc ;
struct TYPE_11__ {int plane; int step; int shift; int depth; int offset; } ;
struct TYPE_10__ {int flags; int log2_chroma_w; int log2_chroma_h; int nb_components; TYPE_4__* comp; } ;
typedef  TYPE_3__ AVPixFmtDescriptor ;
typedef  TYPE_4__ AVComponentDescriptor ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_NUM_DATA_POINTERS ; 
 int AV_PIX_FMT_FLAG_ALPHA ; 
 int AV_PIX_FMT_FLAG_BE ; 
 int AV_PIX_FMT_FLAG_BITSTREAM ; 
 int AV_PIX_FMT_FLAG_HWACCEL ; 
 int AV_PIX_FMT_FLAG_PAL ; 
 int /*<<< orphan*/  CL_ARGB ; 
 int /*<<< orphan*/  CL_BGRA ; 
 int /*<<< orphan*/  CL_MEM_OBJECT_IMAGE2D ; 
 int /*<<< orphan*/  CL_R ; 
 int /*<<< orphan*/  CL_RG ; 
 int /*<<< orphan*/  CL_RGBA ; 
 int /*<<< orphan*/  CL_UNORM_INT16 ; 
 int /*<<< orphan*/  CL_UNORM_INT8 ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int HAVE_BIGENDIAN ; 
 TYPE_3__* av_pix_fmt_desc_get (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int opencl_get_plane_format(enum AVPixelFormat pixfmt,
                                   int plane, int width, int height,
                                   cl_image_format *image_format,
                                   cl_image_desc *image_desc)
{
    const AVPixFmtDescriptor *desc;
    const AVComponentDescriptor *comp;
    int channels = 0, order = 0, depth = 0, step = 0;
    int wsub, hsub, alpha;
    int c;

    if (plane >= AV_NUM_DATA_POINTERS)
        return AVERROR(ENOENT);

    desc = av_pix_fmt_desc_get(pixfmt);

    // Only normal images are allowed.
    if (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM |
                       AV_PIX_FMT_FLAG_HWACCEL   |
                       AV_PIX_FMT_FLAG_PAL))
        return AVERROR(EINVAL);

    wsub = 1 << desc->log2_chroma_w;
    hsub = 1 << desc->log2_chroma_h;
    // Subsampled components must be exact.
    if (width & wsub - 1 || height & hsub - 1)
        return AVERROR(EINVAL);

    for (c = 0; c < desc->nb_components; c++) {
        comp = &desc->comp[c];
        if (comp->plane != plane)
            continue;
        // The step size must be a power of two.
        if (comp->step != 1 && comp->step != 2 &&
            comp->step != 4 && comp->step != 8)
            return AVERROR(EINVAL);
        // The bits in each component must be packed in the
        // most-significant-bits of the relevant bytes.
        if (comp->shift + comp->depth != 8 &&
            comp->shift + comp->depth != 16)
            return AVERROR(EINVAL);
        // The depth must not vary between components.
        if (depth && comp->depth != depth)
            return AVERROR(EINVAL);
        // If a single data element crosses multiple bytes then
        // it must match the native endianness.
        if (comp->depth > 8 &&
            HAVE_BIGENDIAN == !(desc->flags & AV_PIX_FMT_FLAG_BE))
            return AVERROR(EINVAL);
        // A single data element must not contain multiple samples
        // from the same component.
        if (step && comp->step != step)
            return AVERROR(EINVAL);

        depth = comp->depth;
        order = order * 10 + comp->offset / ((depth + 7) / 8) + 1;
        step  = comp->step;
        alpha = (desc->flags & AV_PIX_FMT_FLAG_ALPHA &&
                 c == desc->nb_components - 1);
        ++channels;
    }
    if (channels == 0)
        return AVERROR(ENOENT);

    memset(image_format, 0, sizeof(*image_format));
    memset(image_desc,   0, sizeof(*image_desc));
    image_desc->image_type = CL_MEM_OBJECT_IMAGE2D;

    if (plane == 0 || alpha) {
        image_desc->image_width     = width;
        image_desc->image_height    = height;
        image_desc->image_row_pitch = step * width;
    } else {
        image_desc->image_width     = width  / wsub;
        image_desc->image_height    = height / hsub;
        image_desc->image_row_pitch = step * width / wsub;
    }

    if (depth <= 8) {
        image_format->image_channel_data_type = CL_UNORM_INT8;
    } else {
        if (depth <= 16)
            image_format->image_channel_data_type = CL_UNORM_INT16;
        else
            return AVERROR(EINVAL);
    }

#define CHANNEL_ORDER(order, type) \
    case order: image_format->image_channel_order = type; break;
    switch (order) {
        CHANNEL_ORDER(1,    CL_R);
        CHANNEL_ORDER(12,   CL_RG);
        CHANNEL_ORDER(1234, CL_RGBA);
        CHANNEL_ORDER(2341, CL_ARGB);
        CHANNEL_ORDER(3214, CL_BGRA);
#ifdef CL_ABGR
        CHANNEL_ORDER(4321, CL_ABGR);
#endif
    default:
        return AVERROR(EINVAL);
    }
#undef CHANNEL_ORDER

    return 0;
}