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
struct TYPE_3__ {int /*<<< orphan*/  sec_act; } ;
typedef  TYPE_1__ tGATT_TCB ;
typedef  int /*<<< orphan*/  tGATT_SEC_ACTION ;

/* Variables and functions */

void gatt_set_sec_act(tGATT_TCB *p_tcb, tGATT_SEC_ACTION sec_act)
{
    if (p_tcb) {
        p_tcb->sec_act = sec_act;
    }
}