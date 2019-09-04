#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int slice_flags; int /*<<< orphan*/  (* draw_horiz_band ) (TYPE_5__*,TYPE_4__ const*,int*,int,scalar_t__,int) ;scalar_t__ height; int /*<<< orphan*/  pix_fmt; } ;
struct TYPE_13__ {int* linesize; } ;
struct TYPE_12__ {int log2_chroma_h; } ;
struct TYPE_10__ {TYPE_4__* f; } ;
struct TYPE_11__ {scalar_t__ picture_structure; scalar_t__ first_field; TYPE_1__ cur_pic; TYPE_5__* avctx; } ;
typedef  int /*<<< orphan*/  H264SliceContext ;
typedef  TYPE_2__ H264Context ;
typedef  TYPE_3__ AVPixFmtDescriptor ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AV_NUM_DATA_POINTERS ; 
 int FFMIN (int,scalar_t__) ; 
 scalar_t__ PICT_FRAME ; 
 int SLICE_FLAG_ALLOW_FIELD ; 
 TYPE_3__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emms_c () ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,TYPE_4__ const*,int*,int,scalar_t__,int) ; 

void ff_h264_draw_horiz_band(const H264Context *h, H264SliceContext *sl,
                             int y, int height)
{
    AVCodecContext *avctx = h->avctx;
    const AVFrame   *src  = h->cur_pic.f;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(avctx->pix_fmt);
    int vshift = desc->log2_chroma_h;
    const int field_pic = h->picture_structure != PICT_FRAME;
    if (field_pic) {
        height <<= 1;
        y      <<= 1;
    }

    height = FFMIN(height, avctx->height - y);

    if (field_pic && h->first_field && !(avctx->slice_flags & SLICE_FLAG_ALLOW_FIELD))
        return;

    if (avctx->draw_horiz_band) {
        int offset[AV_NUM_DATA_POINTERS];
        int i;

        offset[0] = y * src->linesize[0];
        offset[1] =
        offset[2] = (y >> vshift) * src->linesize[1];
        for (i = 3; i < AV_NUM_DATA_POINTERS; i++)
            offset[i] = 0;

        emms_c();

        avctx->draw_horiz_band(avctx, src, offset,
                               y, h->picture_structure, height);
    }
}