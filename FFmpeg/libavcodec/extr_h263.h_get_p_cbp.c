#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* clear_block ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int mpv_flags; scalar_t__ mv_type; int dquant; int lambda2; int* block_last_index; int /*<<< orphan*/ * block; TYPE_1__ bdsp; scalar_t__* coded_score; } ;
typedef  TYPE_2__ MpegEncContext ;

/* Variables and functions */
 int FF_LAMBDA_SHIFT ; 
 int FF_MPV_FLAG_CBP_RD ; 
 int INT_MAX ; 
 scalar_t__ MV_TYPE_16X16 ; 
 int const** ff_h263_cbpy_tab ; 
 int const* ff_h263_inter_MCBPC_bits ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int get_p_cbp(MpegEncContext * s,
                      int16_t block[6][64],
                      int motion_x, int motion_y){
    int cbp, i;

    if (s->mpv_flags & FF_MPV_FLAG_CBP_RD) {
        int best_cbpy_score= INT_MAX;
        int best_cbpc_score= INT_MAX;
        int cbpc = (-1), cbpy= (-1);
        const int offset= (s->mv_type==MV_TYPE_16X16 ? 0 : 16) + (s->dquant ? 8 : 0);
        const int lambda= s->lambda2 >> (FF_LAMBDA_SHIFT - 6);

        for(i=0; i<4; i++){
            int score= ff_h263_inter_MCBPC_bits[i + offset] * lambda;
            if(i&1) score += s->coded_score[5];
            if(i&2) score += s->coded_score[4];

            if(score < best_cbpc_score){
                best_cbpc_score= score;
                cbpc= i;
            }
        }

        for(i=0; i<16; i++){
            int score= ff_h263_cbpy_tab[i ^ 0xF][1] * lambda;
            if(i&1) score += s->coded_score[3];
            if(i&2) score += s->coded_score[2];
            if(i&4) score += s->coded_score[1];
            if(i&8) score += s->coded_score[0];

            if(score < best_cbpy_score){
                best_cbpy_score= score;
                cbpy= i;
            }
        }
        cbp= cbpc + 4*cbpy;
        if ((motion_x | motion_y | s->dquant) == 0 && s->mv_type==MV_TYPE_16X16){
            if(best_cbpy_score + best_cbpc_score + 2*lambda >= 0)
                cbp= 0;
        }

        for (i = 0; i < 6; i++) {
            if (s->block_last_index[i] >= 0 && ((cbp >> (5 - i))&1)==0 ){
                s->block_last_index[i]= -1;
                s->bdsp.clear_block(s->block[i]);
            }
        }
    }else{
        cbp= 0;
        for (i = 0; i < 6; i++) {
            if (s->block_last_index[i] >= 0)
                cbp |= 1 << (5 - i);
        }
    }
    return cbp;
}