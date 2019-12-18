#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int num_blocks; int use_frame_exp_strategy; int fbw_channels; int** exp_strategy; int* frame_exp_strategy; int /*<<< orphan*/  cpl_on; } ;
typedef  TYPE_1__ AC3EncodeContext ;

/* Variables and functions */
 int****** eac3_frame_expstr_index_tab ; 

void ff_eac3_get_frame_exp_strategy(AC3EncodeContext *s)
{
    int ch;

    if (s->num_blocks < 6) {
        s->use_frame_exp_strategy = 0;
        return;
    }

    s->use_frame_exp_strategy = 1;
    for (ch = !s->cpl_on; ch <= s->fbw_channels; ch++) {
        int expstr = eac3_frame_expstr_index_tab[s->exp_strategy[ch][0]-1]
                                                [s->exp_strategy[ch][1]]
                                                [s->exp_strategy[ch][2]]
                                                [s->exp_strategy[ch][3]]
                                                [s->exp_strategy[ch][4]]
                                                [s->exp_strategy[ch][5]];
        if (expstr < 0) {
            s->use_frame_exp_strategy = 0;
            break;
        }
        s->frame_exp_strategy[ch] = expstr;
    }
}