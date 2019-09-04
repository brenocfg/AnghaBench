#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int dia_size; int pre_dia_size; int me_sub_cmp; int me_cmp; int me_pre_cmp; int mb_cmp; int flags; } ;
struct TYPE_13__ {void** me_sub_cmp; void** me_cmp; void** mb_cmp; void** me_pre_cmp; } ;
struct TYPE_12__ {int stride; int uvstride; void* sub_motion_search; int /*<<< orphan*/ ** hpel_put; TYPE_8__* avctx; int /*<<< orphan*/  hpel_avg; int /*<<< orphan*/  qpel_put; int /*<<< orphan*/  qpel_avg; void* mb_flags; void* sub_flags; void* flags; } ;
struct TYPE_10__ {int /*<<< orphan*/ ** put_pixels_tab; int /*<<< orphan*/ ** put_no_rnd_pixels_tab; int /*<<< orphan*/  avg_pixels_tab; } ;
struct TYPE_9__ {int /*<<< orphan*/  put_qpel_pixels_tab; int /*<<< orphan*/  put_no_rnd_qpel_pixels_tab; int /*<<< orphan*/  avg_qpel_pixels_tab; } ;
struct TYPE_11__ {scalar_t__ codec_id; int linesize; int uvlinesize; int mb_width; TYPE_6__ mecc; TYPE_2__ hdsp; scalar_t__ no_rounding; TYPE_1__ qdsp; TYPE_8__* avctx; TYPE_4__ me; } ;
typedef  TYPE_3__ MpegEncContext ;
typedef  TYPE_4__ MotionEstContext ;

/* Variables and functions */
 int AV_CODEC_FLAG_QPEL ; 
 scalar_t__ AV_CODEC_ID_H261 ; 
 scalar_t__ AV_CODEC_ID_SNOW ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int FFABS (int) ; 
 int FFMAX (int,int) ; 
 int FFMIN (int,int) ; 
 int FF_CMP_CHROMA ; 
 int FF_CMP_SAD ; 
 int MAX_SAB_SIZE ; 
 int ME_MAP_SHIFT ; 
 int ME_MAP_SIZE ; 
 int /*<<< orphan*/  av_log (TYPE_8__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_set_cmp (TYPE_6__*,void**,int) ; 
 void* get_flags (TYPE_4__* const,int /*<<< orphan*/ ,int) ; 
 void* hpel_motion_search ; 
 void* no_sub_motion_search ; 
 void* qpel_motion_search ; 
 void* sad_hpel_motion_search ; 
 void* zero_cmp ; 
 int /*<<< orphan*/  zero_hpel ; 

int ff_init_me(MpegEncContext *s){
    MotionEstContext * const c= &s->me;
    int cache_size= FFMIN(ME_MAP_SIZE>>ME_MAP_SHIFT, 1<<ME_MAP_SHIFT);
    int dia_size= FFMAX(FFABS(s->avctx->dia_size)&255, FFABS(s->avctx->pre_dia_size)&255);

    if(FFMIN(s->avctx->dia_size, s->avctx->pre_dia_size) < -FFMIN(ME_MAP_SIZE, MAX_SAB_SIZE)){
        av_log(s->avctx, AV_LOG_ERROR, "ME_MAP size is too small for SAB diamond\n");
        return -1;
    }

    c->avctx= s->avctx;

    if(s->codec_id == AV_CODEC_ID_H261)
        c->avctx->me_sub_cmp = c->avctx->me_cmp;

    if(cache_size < 2*dia_size && !c->stride){
        av_log(s->avctx, AV_LOG_INFO, "ME_MAP size may be a little small for the selected diamond size\n");
    }

    ff_set_cmp(&s->mecc, s->mecc.me_pre_cmp, c->avctx->me_pre_cmp);
    ff_set_cmp(&s->mecc, s->mecc.me_cmp,     c->avctx->me_cmp);
    ff_set_cmp(&s->mecc, s->mecc.me_sub_cmp, c->avctx->me_sub_cmp);
    ff_set_cmp(&s->mecc, s->mecc.mb_cmp,     c->avctx->mb_cmp);

    c->flags    = get_flags(c, 0, c->avctx->me_cmp    &FF_CMP_CHROMA);
    c->sub_flags= get_flags(c, 0, c->avctx->me_sub_cmp&FF_CMP_CHROMA);
    c->mb_flags = get_flags(c, 0, c->avctx->mb_cmp    &FF_CMP_CHROMA);

/*FIXME s->no_rounding b_type*/
    if (s->avctx->flags & AV_CODEC_FLAG_QPEL) {
        c->sub_motion_search= qpel_motion_search;
        c->qpel_avg = s->qdsp.avg_qpel_pixels_tab;
        if (s->no_rounding)
            c->qpel_put = s->qdsp.put_no_rnd_qpel_pixels_tab;
        else
            c->qpel_put = s->qdsp.put_qpel_pixels_tab;
    }else{
        if(c->avctx->me_sub_cmp&FF_CMP_CHROMA)
            c->sub_motion_search= hpel_motion_search;
        else if(   c->avctx->me_sub_cmp == FF_CMP_SAD
                && c->avctx->    me_cmp == FF_CMP_SAD
                && c->avctx->    mb_cmp == FF_CMP_SAD)
            c->sub_motion_search= sad_hpel_motion_search; // 2050 vs. 2450 cycles
        else
            c->sub_motion_search= hpel_motion_search;
    }
    c->hpel_avg = s->hdsp.avg_pixels_tab;
    if (s->no_rounding)
        c->hpel_put = s->hdsp.put_no_rnd_pixels_tab;
    else
        c->hpel_put = s->hdsp.put_pixels_tab;

    if(s->linesize){
        c->stride  = s->linesize;
        c->uvstride= s->uvlinesize;
    }else{
        c->stride  = 16*s->mb_width + 32;
        c->uvstride=  8*s->mb_width + 16;
    }

    /* 8x8 fullpel search would need a 4x4 chroma compare, which we do
     * not have yet, and even if we had, the motion estimation code
     * does not expect it. */
    if (s->codec_id != AV_CODEC_ID_SNOW) {
        if ((c->avctx->me_cmp & FF_CMP_CHROMA) /* && !s->mecc.me_cmp[2] */)
            s->mecc.me_cmp[2] = zero_cmp;
        if ((c->avctx->me_sub_cmp & FF_CMP_CHROMA) && !s->mecc.me_sub_cmp[2])
            s->mecc.me_sub_cmp[2] = zero_cmp;
        c->hpel_put[2][0]= c->hpel_put[2][1]=
        c->hpel_put[2][2]= c->hpel_put[2][3]= zero_hpel;
    }

    if(s->codec_id == AV_CODEC_ID_H261){
        c->sub_motion_search= no_sub_motion_search;
    }

    return 0;
}