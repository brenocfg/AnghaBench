#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int slice_flags; scalar_t__ codec_id; int /*<<< orphan*/  (* draw_horiz_band ) (TYPE_3__*,TYPE_2__*,int*,int,int,int) ;scalar_t__ height; int /*<<< orphan*/  pix_fmt; } ;
struct TYPE_11__ {scalar_t__ pict_type; int* linesize; } ;
struct TYPE_10__ {int log2_chroma_h; } ;
typedef  TYPE_1__ AVPixFmtDescriptor ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_SVQ3 ; 
 int AV_NUM_DATA_POINTERS ; 
 scalar_t__ AV_PICTURE_TYPE_B ; 
 int FFMIN (int,scalar_t__) ; 
 int PICT_FRAME ; 
 int SLICE_FLAG_ALLOW_FIELD ; 
 int SLICE_FLAG_CODED_ORDER ; 
 TYPE_1__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emms_c () ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,TYPE_2__*,int*,int,int,int) ; 

void ff_draw_horiz_band(AVCodecContext *avctx,
                        AVFrame *cur, AVFrame *last,
                        int y, int h, int picture_structure,
                        int first_field, int low_delay)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(avctx->pix_fmt);
    int vshift = desc->log2_chroma_h;
    const int field_pic = picture_structure != PICT_FRAME;
    if (field_pic) {
        h <<= 1;
        y <<= 1;
    }

    h = FFMIN(h, avctx->height - y);

    if (field_pic && first_field &&
        !(avctx->slice_flags & SLICE_FLAG_ALLOW_FIELD))
        return;

    if (avctx->draw_horiz_band) {
        AVFrame *src;
        int offset[AV_NUM_DATA_POINTERS];
        int i;

        if (cur->pict_type == AV_PICTURE_TYPE_B || low_delay ||
           (avctx->slice_flags & SLICE_FLAG_CODED_ORDER))
            src = cur;
        else if (last)
            src = last;
        else
            return;

        if (cur->pict_type == AV_PICTURE_TYPE_B &&
            picture_structure == PICT_FRAME &&
            avctx->codec_id != AV_CODEC_ID_SVQ3) {
            for (i = 0; i < AV_NUM_DATA_POINTERS; i++)
                offset[i] = 0;
        } else {
            offset[0]= y * src->linesize[0];
            offset[1]=
            offset[2]= (y >> vshift) * src->linesize[1];
            for (i = 3; i < AV_NUM_DATA_POINTERS; i++)
                offset[i] = 0;
        }

        emms_c();

        avctx->draw_horiz_band(avctx, src, offset,
                               y, picture_structure, h);
    }
}