#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ptrdiff_t ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_10__ {int log2_chroma_w; int log2_chroma_h; int nb_components; } ;
struct TYPE_9__ {TYPE_2__* csp; int /*<<< orphan*/  (* lowpass_line ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int,int,int) ;} ;
struct TYPE_8__ {TYPE_1__* comp; } ;
struct TYPE_7__ {int depth; } ;
typedef  TYPE_3__ TInterlaceContext ;
typedef  TYPE_4__ AVPixFmtDescriptor ;

/* Variables and functions */
 int AV_CEIL_RSHIFT (int,int) ; 
 int FIELD_LOWER ; 
 int FIELD_UPPER ; 
 int FIELD_UPPER_AND_LOWER ; 
 int TINTERLACE_FLAG_CVLPF ; 
 int TINTERLACE_FLAG_VLPF ; 
 int /*<<< orphan*/  av_image_copy_plane (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int,int,int) ; 
 TYPE_4__* av_pix_fmt_desc_get (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int,int,int) ; 

__attribute__((used)) static inline
void copy_picture_field(TInterlaceContext *tinterlace,
                        uint8_t *dst[4], int dst_linesize[4],
                        const uint8_t *src[4], int src_linesize[4],
                        enum AVPixelFormat format, int w, int src_h,
                        int src_field, int interleave, int dst_field,
                        int flags)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(format);
    int hsub = desc->log2_chroma_w;
    int plane, vsub = desc->log2_chroma_h;
    int k = src_field == FIELD_UPPER_AND_LOWER ? 1 : 2;
    int h;

    for (plane = 0; plane < desc->nb_components; plane++) {
        int lines = plane == 1 || plane == 2 ? AV_CEIL_RSHIFT(src_h, vsub) : src_h;
        int cols  = plane == 1 || plane == 2 ? AV_CEIL_RSHIFT(    w, hsub) : w;
        uint8_t *dstp = dst[plane];
        const uint8_t *srcp = src[plane];
        int srcp_linesize = src_linesize[plane] * k;
        int dstp_linesize = dst_linesize[plane] * (interleave ? 2 : 1);
        int clip_max = (1 << tinterlace->csp->comp[plane].depth) - 1;

        lines = (lines + (src_field == FIELD_UPPER)) / k;
        if (src_field == FIELD_LOWER)
            srcp += src_linesize[plane];
        if (interleave && dst_field == FIELD_LOWER)
            dstp += dst_linesize[plane];
        // Low-pass filtering is required when creating an interlaced destination from
        // a progressive source which contains high-frequency vertical detail.
        // Filtering will reduce interlace 'twitter' and Moire patterning.
        if (flags & (TINTERLACE_FLAG_VLPF | TINTERLACE_FLAG_CVLPF)) {
            int x = !!(flags & TINTERLACE_FLAG_CVLPF);
            for (h = lines; h > 0; h--) {
                ptrdiff_t pref = src_linesize[plane];
                ptrdiff_t mref = -pref;
                if (h >= (lines - x))  mref = 0; // there is no line above
                else if (h <= (1 + x)) pref = 0; // there is no line below

                tinterlace->lowpass_line(dstp, cols, srcp, mref, pref, clip_max);
                dstp += dstp_linesize;
                srcp += srcp_linesize;
            }
        } else {
            if (tinterlace->csp->comp[plane].depth > 8)
                cols *= 2;
            av_image_copy_plane(dstp, dstp_linesize, srcp, srcp_linesize, cols, lines);
        }
    }
}