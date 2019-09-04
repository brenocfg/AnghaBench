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
struct TYPE_3__ {int* pred_mode_Y; int* top_pred_Y; int mbx; int flags; } ;
typedef  TYPE_1__ AVSContext ;

/* Variables and functions */
 int A_AVAIL ; 
 int B_AVAIL ; 
 int /*<<< orphan*/  left_modifier_c ; 
 int /*<<< orphan*/  left_modifier_l ; 
 int /*<<< orphan*/  modify_pred (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  top_modifier_c ; 
 int /*<<< orphan*/  top_modifier_l ; 

void ff_cavs_modify_mb_i(AVSContext *h, int *pred_mode_uv)
{
    /* save pred modes before they get modified */
    h->pred_mode_Y[3]             = h->pred_mode_Y[5];
    h->pred_mode_Y[6]             = h->pred_mode_Y[8];
    h->top_pred_Y[h->mbx * 2 + 0] = h->pred_mode_Y[7];
    h->top_pred_Y[h->mbx * 2 + 1] = h->pred_mode_Y[8];

    /* modify pred modes according to availability of neighbour samples */
    if (!(h->flags & A_AVAIL)) {
        modify_pred(left_modifier_l, &h->pred_mode_Y[4]);
        modify_pred(left_modifier_l, &h->pred_mode_Y[7]);
        modify_pred(left_modifier_c, pred_mode_uv);
    }
    if (!(h->flags & B_AVAIL)) {
        modify_pred(top_modifier_l, &h->pred_mode_Y[4]);
        modify_pred(top_modifier_l, &h->pred_mode_Y[5]);
        modify_pred(top_modifier_c, pred_mode_uv);
    }
}