#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* f; } ;
struct TYPE_9__ {scalar_t__ pict_type; scalar_t__ picture_structure; scalar_t__ codec_id; scalar_t__ out_format; scalar_t__ encoding; scalar_t__ noise_reduction; scalar_t__ dct_error_sum; int /*<<< orphan*/  dct_unquantize_mpeg1_inter; int /*<<< orphan*/  dct_unquantize_inter; int /*<<< orphan*/  dct_unquantize_mpeg1_intra; int /*<<< orphan*/  dct_unquantize_intra; int /*<<< orphan*/  dct_unquantize_h263_inter; int /*<<< orphan*/  dct_unquantize_h263_intra; int /*<<< orphan*/  dct_unquantize_mpeg2_inter; int /*<<< orphan*/  dct_unquantize_mpeg2_intra; scalar_t__ mpeg_quant; TYPE_5__ next_picture; TYPE_5__ last_picture; TYPE_5__ current_picture; TYPE_5__* next_picture_ptr; int /*<<< orphan*/  avctx; TYPE_5__* last_picture_ptr; TYPE_5__* current_picture_ptr; int /*<<< orphan*/  droppable; } ;
struct TYPE_8__ {scalar_t__ pict_type; int key_frame; int* data; int* linesize; scalar_t__* buf; } ;
typedef  TYPE_2__ MpegEncContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_MPEG2VIDEO ; 
 scalar_t__ AV_PICTURE_TYPE_B ; 
 scalar_t__ AV_PICTURE_TYPE_I ; 
 scalar_t__ FMT_H261 ; 
 scalar_t__ FMT_H263 ; 
 scalar_t__ PICT_BOTTOM_FIELD ; 
 scalar_t__ PICT_FRAME ; 
 int /*<<< orphan*/  av_assert2 (int) ; 
 int ff_mpeg_ref_picture (int /*<<< orphan*/ ,TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ff_mpeg_unref_picture (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  update_noise_reduction (TYPE_2__*) ; 

__attribute__((used)) static int frame_start(MpegEncContext *s)
{
    int ret;

    /* mark & release old frames */
    if (s->pict_type != AV_PICTURE_TYPE_B && s->last_picture_ptr &&
        s->last_picture_ptr != s->next_picture_ptr &&
        s->last_picture_ptr->f->buf[0]) {
        ff_mpeg_unref_picture(s->avctx, s->last_picture_ptr);
    }

    s->current_picture_ptr->f->pict_type = s->pict_type;
    s->current_picture_ptr->f->key_frame = s->pict_type == AV_PICTURE_TYPE_I;

    ff_mpeg_unref_picture(s->avctx, &s->current_picture);
    if ((ret = ff_mpeg_ref_picture(s->avctx, &s->current_picture,
                                   s->current_picture_ptr)) < 0)
        return ret;

    if (s->pict_type != AV_PICTURE_TYPE_B) {
        s->last_picture_ptr = s->next_picture_ptr;
        if (!s->droppable)
            s->next_picture_ptr = s->current_picture_ptr;
    }

    if (s->last_picture_ptr) {
        ff_mpeg_unref_picture(s->avctx, &s->last_picture);
        if (s->last_picture_ptr->f->buf[0] &&
            (ret = ff_mpeg_ref_picture(s->avctx, &s->last_picture,
                                       s->last_picture_ptr)) < 0)
            return ret;
    }
    if (s->next_picture_ptr) {
        ff_mpeg_unref_picture(s->avctx, &s->next_picture);
        if (s->next_picture_ptr->f->buf[0] &&
            (ret = ff_mpeg_ref_picture(s->avctx, &s->next_picture,
                                       s->next_picture_ptr)) < 0)
            return ret;
    }

    if (s->picture_structure!= PICT_FRAME) {
        int i;
        for (i = 0; i < 4; i++) {
            if (s->picture_structure == PICT_BOTTOM_FIELD) {
                s->current_picture.f->data[i] +=
                    s->current_picture.f->linesize[i];
            }
            s->current_picture.f->linesize[i] *= 2;
            s->last_picture.f->linesize[i]    *= 2;
            s->next_picture.f->linesize[i]    *= 2;
        }
    }

    if (s->mpeg_quant || s->codec_id == AV_CODEC_ID_MPEG2VIDEO) {
        s->dct_unquantize_intra = s->dct_unquantize_mpeg2_intra;
        s->dct_unquantize_inter = s->dct_unquantize_mpeg2_inter;
    } else if (s->out_format == FMT_H263 || s->out_format == FMT_H261) {
        s->dct_unquantize_intra = s->dct_unquantize_h263_intra;
        s->dct_unquantize_inter = s->dct_unquantize_h263_inter;
    } else {
        s->dct_unquantize_intra = s->dct_unquantize_mpeg1_intra;
        s->dct_unquantize_inter = s->dct_unquantize_mpeg1_inter;
    }

    if (s->dct_error_sum) {
        av_assert2(s->noise_reduction && s->encoding);
        update_noise_reduction(s);
    }

    return 0;
}