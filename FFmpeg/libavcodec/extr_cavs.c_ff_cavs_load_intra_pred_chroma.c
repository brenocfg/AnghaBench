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
struct TYPE_3__ {int flags; int mbx; int /*<<< orphan*/ * top_border_v; int /*<<< orphan*/ * top_border_u; int /*<<< orphan*/ * left_border_v; int /*<<< orphan*/ * left_border_u; int /*<<< orphan*/  topleft_border_v; int /*<<< orphan*/  topleft_border_u; } ;
typedef  TYPE_1__ AVSContext ;

/* Variables and functions */
 int A_AVAIL ; 
 int B_AVAIL ; 
 int C_AVAIL ; 

void ff_cavs_load_intra_pred_chroma(AVSContext *h)
{
    /* extend borders by one pixel */
    h->left_border_u[9]              = h->left_border_u[8];
    h->left_border_v[9]              = h->left_border_v[8];
    if(h->flags & C_AVAIL) {
        h->top_border_u[h->mbx*10 + 9] = h->top_border_u[h->mbx*10 + 11];
        h->top_border_v[h->mbx*10 + 9] = h->top_border_v[h->mbx*10 + 11];
    } else {
        h->top_border_u[h->mbx * 10 + 9] = h->top_border_u[h->mbx * 10 + 8];
        h->top_border_v[h->mbx * 10 + 9] = h->top_border_v[h->mbx * 10 + 8];
    }
    if((h->flags & A_AVAIL) && (h->flags & B_AVAIL)) {
        h->top_border_u[h->mbx * 10] = h->left_border_u[0] = h->topleft_border_u;
        h->top_border_v[h->mbx * 10] = h->left_border_v[0] = h->topleft_border_v;
    } else {
        h->left_border_u[0]          = h->left_border_u[1];
        h->left_border_v[0]          = h->left_border_v[1];
        h->top_border_u[h->mbx * 10] = h->top_border_u[h->mbx * 10 + 1];
        h->top_border_v[h->mbx * 10] = h->top_border_v[h->mbx * 10 + 1];
    }
}