#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  rsp_timer_ent; scalar_t__ in_use; } ;
typedef  TYPE_1__ tGATT_CLCB ;

/* Variables and functions */
 int /*<<< orphan*/  btu_free_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void gatt_clcb_dealloc (tGATT_CLCB *p_clcb)
{
    if (p_clcb && p_clcb->in_use) {
        btu_free_timer(&p_clcb->rsp_timer_ent);
        memset(p_clcb, 0, sizeof(tGATT_CLCB));
    }
}