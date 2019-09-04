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
struct TYPE_3__ {scalar_t__ stream_revision; int mbx; void** top_pred_Y; void** pred_mode_Y; } ;
typedef  TYPE_1__ AVSContext ;

/* Variables and functions */
 void* INTRA_L_LP ; 
 void* NOT_AVAIL ; 

__attribute__((used)) static inline void set_intra_mode_default(AVSContext *h)
{
    if (h->stream_revision > 0) {
        h->pred_mode_Y[3] =  h->pred_mode_Y[6] = NOT_AVAIL;
        h->top_pred_Y[h->mbx * 2 + 0] = h->top_pred_Y[h->mbx * 2 + 1] = NOT_AVAIL;
    } else {
        h->pred_mode_Y[3] =  h->pred_mode_Y[6] = INTRA_L_LP;
        h->top_pred_Y[h->mbx * 2 + 0] = h->top_pred_Y[h->mbx * 2 + 1] = INTRA_L_LP;
    }
}