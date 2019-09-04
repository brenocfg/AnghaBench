#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int int16_t ;
struct TYPE_7__ {TYPE_1__* avctx; } ;
struct TYPE_6__ {scalar_t__ out_format; int mb_height; int mb_stride; int mb_width; int* mb_type; scalar_t__ msmpeg4_version; TYPE_3__ me; } ;
struct TYPE_5__ {int me_range; } ;
typedef  TYPE_2__ MpegEncContext ;
typedef  TYPE_3__ MotionEstContext ;

/* Variables and functions */
 int CANDIDATE_MB_TYPE_INTRA ; 
 scalar_t__ FMT_MPEG1 ; 

void ff_fix_long_mvs(MpegEncContext * s, uint8_t *field_select_table, int field_select,
                     int16_t (*mv_table)[2], int f_code, int type, int truncate)
{
    MotionEstContext * const c= &s->me;
    int y, h_range, v_range;

    // RAL: 8 in MPEG-1, 16 in MPEG-4
    int range = (((s->out_format == FMT_MPEG1 || s->msmpeg4_version) ? 8 : 16) << f_code);

    if(c->avctx->me_range && range > c->avctx->me_range) range= c->avctx->me_range;

    h_range= range;
    v_range= field_select_table ? range>>1 : range;

    /* clip / convert to intra 16x16 type MVs */
    for(y=0; y<s->mb_height; y++){
        int x;
        int xy= y*s->mb_stride;
        for(x=0; x<s->mb_width; x++){
            if (s->mb_type[xy] & type){    // RAL: "type" test added...
                if (!field_select_table || field_select_table[xy] == field_select) {
                    if(   mv_table[xy][0] >=h_range || mv_table[xy][0] <-h_range
                       || mv_table[xy][1] >=v_range || mv_table[xy][1] <-v_range){

                        if(truncate){
                            if     (mv_table[xy][0] > h_range-1) mv_table[xy][0]=  h_range-1;
                            else if(mv_table[xy][0] < -h_range ) mv_table[xy][0]= -h_range;
                            if     (mv_table[xy][1] > v_range-1) mv_table[xy][1]=  v_range-1;
                            else if(mv_table[xy][1] < -v_range ) mv_table[xy][1]= -v_range;
                        }else{
                            s->mb_type[xy] &= ~type;
                            s->mb_type[xy] |= CANDIDATE_MB_TYPE_INTRA;
                            mv_table[xy][0]=
                            mv_table[xy][1]= 0;
                        }
                    }
                }
            }
            xy++;
        }
    }
}