#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_17__ {int pixelformat; int height; } ;
struct TYPE_16__ {int pixelformat; int height; } ;
struct TYPE_18__ {TYPE_3__ pix; TYPE_2__ pix_mp; } ;
struct v4l2_format {TYPE_4__ fmt; int /*<<< orphan*/  type; } ;
struct TYPE_20__ {int num_planes; TYPE_1__* context; } ;
typedef  TYPE_6__ V4L2Buffer ;
struct TYPE_22__ {int* linesize; TYPE_10__** buf; int /*<<< orphan*/ * data; int /*<<< orphan*/  format; } ;
struct TYPE_21__ {int nb_components; int /*<<< orphan*/  log2_chroma_h; TYPE_5__* comp; } ;
struct TYPE_19__ {scalar_t__ plane; } ;
struct TYPE_15__ {struct v4l2_format format; } ;
struct TYPE_14__ {int size; int /*<<< orphan*/  data; } ;
typedef  TYPE_7__ AVPixFmtDescriptor ;
typedef  TYPE_8__ AVFrame ;

/* Variables and functions */
 int AV_CEIL_RSHIFT (int,int /*<<< orphan*/ ) ; 
 int FFMAX (int,scalar_t__) ; 
#define  V4L2_PIX_FMT_NV12M 139 
#define  V4L2_PIX_FMT_NV12MT 138 
#define  V4L2_PIX_FMT_NV12MT_16X16 137 
#define  V4L2_PIX_FMT_NV16M 136 
#define  V4L2_PIX_FMT_NV21M 135 
#define  V4L2_PIX_FMT_NV61M 134 
#define  V4L2_PIX_FMT_YUV420M 133 
#define  V4L2_PIX_FMT_YUV422M 132 
#define  V4L2_PIX_FMT_YUV444M 131 
#define  V4L2_PIX_FMT_YVU420M 130 
#define  V4L2_PIX_FMT_YVU422M 129 
#define  V4L2_PIX_FMT_YVU444M 128 
 scalar_t__ V4L2_TYPE_IS_MULTIPLANAR (int /*<<< orphan*/ ) ; 
 TYPE_7__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int v4l2_bufref_to_buf (TYPE_6__*,int,int /*<<< orphan*/ ,int,int,TYPE_10__*) ; 

__attribute__((used)) static int v4l2_buffer_swframe_to_buf(const AVFrame *frame, V4L2Buffer *out)
{
    int i, ret;
    struct v4l2_format fmt = out->context->format;
    int pixel_format = V4L2_TYPE_IS_MULTIPLANAR(fmt.type) ?
                       fmt.fmt.pix_mp.pixelformat : fmt.fmt.pix.pixelformat;
    int height       = V4L2_TYPE_IS_MULTIPLANAR(fmt.type) ?
                       fmt.fmt.pix_mp.height : fmt.fmt.pix.height;
    int is_planar_format = 0;

    switch (pixel_format) {
    case V4L2_PIX_FMT_YUV420M:
    case V4L2_PIX_FMT_YVU420M:
#ifdef V4L2_PIX_FMT_YUV422M
    case V4L2_PIX_FMT_YUV422M:
#endif
#ifdef V4L2_PIX_FMT_YVU422M
    case V4L2_PIX_FMT_YVU422M:
#endif
#ifdef V4L2_PIX_FMT_YUV444M
    case V4L2_PIX_FMT_YUV444M:
#endif
#ifdef V4L2_PIX_FMT_YVU444M
    case V4L2_PIX_FMT_YVU444M:
#endif
    case V4L2_PIX_FMT_NV12M:
    case V4L2_PIX_FMT_NV21M:
    case V4L2_PIX_FMT_NV12MT_16X16:
    case V4L2_PIX_FMT_NV12MT:
    case V4L2_PIX_FMT_NV16M:
    case V4L2_PIX_FMT_NV61M:
        is_planar_format = 1;
    }

    if (!is_planar_format) {
        const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(frame->format);
        int planes_nb = 0;
        int offset = 0;

        for (i = 0; i < desc->nb_components; i++)
            planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

        for (i = 0; i < planes_nb; i++) {
            int size, h = height;
            if (i == 1 || i == 2) {
                h = AV_CEIL_RSHIFT(h, desc->log2_chroma_h);
            }
            size = frame->linesize[i] * h;
            ret = v4l2_bufref_to_buf(out, 0, frame->data[i], size, offset, frame->buf[i]);
            if (ret)
                return ret;
            offset += size;
        }
        return 0;
    }

    for (i = 0; i < out->num_planes; i++) {
        ret = v4l2_bufref_to_buf(out, i, frame->buf[i]->data, frame->buf[i]->size, 0, frame->buf[i]);
        if (ret)
            return ret;
    }

    return 0;
}