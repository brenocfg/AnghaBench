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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int16_t ;
struct TYPE_6__ {scalar_t__* mc_mb_var; scalar_t__* mb_var; } ;
struct TYPE_7__ {scalar_t__ motion_est; scalar_t__ codec_id; int mb_num; int mb_height; int mb_stride; int mb_width; int* mb_type; scalar_t__ pict_type; TYPE_2__ current_picture; TYPE_1__* avctx; scalar_t__ msmpeg4_version; int /*<<< orphan*/ * fcode_tab; } ;
struct TYPE_5__ {int me_range; scalar_t__ strict_std_compliance; } ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_MPEG2VIDEO ; 
 scalar_t__ AV_PICTURE_TYPE_B ; 
 int FFMAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FFMIN (int,int) ; 
 scalar_t__ FF_COMPLIANCE_NORMAL ; 
 scalar_t__ FF_ME_ZERO ; 
 int INT_MAX ; 
 int MAX_MV ; 

int ff_get_best_fcode(MpegEncContext * s, int16_t (*mv_table)[2], int type)
{
    if (s->motion_est != FF_ME_ZERO) {
        int score[8];
        int i, y, range= s->avctx->me_range ? s->avctx->me_range : (INT_MAX/2);
        uint8_t * fcode_tab= s->fcode_tab;
        int best_fcode=-1;
        int best_score=-10000000;

        if(s->msmpeg4_version)
            range= FFMIN(range, 16);
        else if(s->codec_id == AV_CODEC_ID_MPEG2VIDEO && s->avctx->strict_std_compliance >= FF_COMPLIANCE_NORMAL)
            range= FFMIN(range, 256);

        for(i=0; i<8; i++) score[i]= s->mb_num*(8-i);

        for(y=0; y<s->mb_height; y++){
            int x;
            int xy= y*s->mb_stride;
            for(x=0; x<s->mb_width; x++){
                if(s->mb_type[xy] & type){
                    int mx= mv_table[xy][0];
                    int my= mv_table[xy][1];
                    int fcode= FFMAX(fcode_tab[mx + MAX_MV],
                                     fcode_tab[my + MAX_MV]);
                    int j;

                        if(mx >= range || mx < -range ||
                           my >= range || my < -range)
                            continue;

                    for(j=0; j<fcode && j<8; j++){
                        if(s->pict_type==AV_PICTURE_TYPE_B || s->current_picture.mc_mb_var[xy] < s->current_picture.mb_var[xy])
                            score[j]-= 170;
                    }
                }
                xy++;
            }
        }

        for(i=1; i<8; i++){
            if(score[i] > best_score){
                best_score= score[i];
                best_fcode= i;
            }
        }

        return best_fcode;
    }else{
        return 1;
    }
}