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
struct TYPE_5__ {int mpv_flags; int lambda2; scalar_t__* coded_score; int dquant; int* block_last_index; int /*<<< orphan*/ * block; TYPE_1__ bdsp; } ;
typedef  TYPE_2__ MpegEncContext ;

/* Variables and functions */
 int FF_LAMBDA_SHIFT ; 
 int FF_MPV_FLAG_CBP_RD ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int get_b_cbp(MpegEncContext *s, int16_t block[6][64],
                            int motion_x, int motion_y, int mb_type)
{
    int cbp = 0, i;

    if (s->mpv_flags & FF_MPV_FLAG_CBP_RD) {
        int score        = 0;
        const int lambda = s->lambda2 >> (FF_LAMBDA_SHIFT - 6);

        for (i = 0; i < 6; i++) {
            if (s->coded_score[i] < 0) {
                score += s->coded_score[i];
                cbp   |= 1 << (5 - i);
            }
        }

        if (cbp) {
            int zero_score = -6;
            if ((motion_x | motion_y | s->dquant | mb_type) == 0)
                zero_score -= 4;  // 2 * MV + mb_type + cbp bit

            zero_score *= lambda;
            if (zero_score <= score)
                cbp = 0;
        }

        for (i = 0; i < 6; i++) {
            if (s->block_last_index[i] >= 0 && ((cbp >> (5 - i)) & 1) == 0) {
                s->block_last_index[i] = -1;
                s->bdsp.clear_block(s->block[i]);
            }
        }
    } else {
        for (i = 0; i < 6; i++) {
            if (s->block_last_index[i] >= 0)
                cbp |= 1 << (5 - i);
        }
    }
    return cbp;
}