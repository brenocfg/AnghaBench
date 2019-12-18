#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* avctx; } ;
struct TYPE_9__ {int*** motion_val; int* mb_type; } ;
struct TYPE_10__ {int f_code; scalar_t__ pict_type; scalar_t__ out_format; scalar_t__ codec_id; int b8_stride; int mb_height; int mb_stride; int mb_width; int* mb_type; TYPE_3__ current_picture; TYPE_2__* avctx; scalar_t__ msmpeg4_version; TYPE_5__ me; } ;
struct TYPE_8__ {scalar_t__ strict_std_compliance; int flags; } ;
struct TYPE_7__ {int me_range; } ;
typedef  TYPE_4__ MpegEncContext ;
typedef  TYPE_5__ MotionEstContext ;

/* Variables and functions */
 int AV_CODEC_FLAG_4MV ; 
 scalar_t__ AV_CODEC_ID_MPEG2VIDEO ; 
 scalar_t__ AV_PICTURE_TYPE_P ; 
 int CANDIDATE_MB_TYPE_INTER4V ; 
 scalar_t__ FF_COMPLIANCE_NORMAL ; 
 scalar_t__ FMT_MPEG1 ; 
 int /*<<< orphan*/  av_assert0 (int) ; 

void ff_fix_long_p_mvs(MpegEncContext * s, int type)
{
    MotionEstContext * const c= &s->me;
    const int f_code= s->f_code;
    int y, range;
    av_assert0(s->pict_type==AV_PICTURE_TYPE_P);

    range = (((s->out_format == FMT_MPEG1 || s->msmpeg4_version) ? 8 : 16) << f_code);

    av_assert0(range <= 16 || !s->msmpeg4_version);
    av_assert0(range <=256 || !(s->codec_id == AV_CODEC_ID_MPEG2VIDEO && s->avctx->strict_std_compliance >= FF_COMPLIANCE_NORMAL));

    if(c->avctx->me_range && range > c->avctx->me_range) range= c->avctx->me_range;

    if (s->avctx->flags & AV_CODEC_FLAG_4MV) {
        const int wrap= s->b8_stride;

        /* clip / convert to intra 8x8 type MVs */
        for(y=0; y<s->mb_height; y++){
            int xy= y*2*wrap;
            int i= y*s->mb_stride;
            int x;

            for(x=0; x<s->mb_width; x++){
                if(s->mb_type[i]&CANDIDATE_MB_TYPE_INTER4V){
                    int block;
                    for(block=0; block<4; block++){
                        int off= (block& 1) + (block>>1)*wrap;
                        int mx = s->current_picture.motion_val[0][ xy + off ][0];
                        int my = s->current_picture.motion_val[0][ xy + off ][1];

                        if(   mx >=range || mx <-range
                           || my >=range || my <-range){
                            s->mb_type[i] &= ~CANDIDATE_MB_TYPE_INTER4V;
                            s->mb_type[i] |= type;
                            s->current_picture.mb_type[i] = type;
                        }
                    }
                }
                xy+=2;
                i++;
            }
        }
    }
}