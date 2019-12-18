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
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ tL2C_LCB ;
typedef  int UINT8 ;

/* Variables and functions */
 int L2CAP_ADJ_ZERO_ID ; 

void l2cu_adj_id (tL2C_LCB *p_lcb, UINT8 adj_mask)
{
    if ((adj_mask & L2CAP_ADJ_ZERO_ID) && !p_lcb->id) {
        p_lcb->id++;
    }
}