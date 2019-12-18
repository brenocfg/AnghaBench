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
struct TYPE_4__ {int /*<<< orphan*/  mon_retrans_timer; } ;
struct TYPE_5__ {TYPE_1__ fcrb; } ;
typedef  TYPE_2__ tL2C_CCB ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btu_free_quick_timer (int /*<<< orphan*/ *) ; 

void l2c_fcr_free_timer (tL2C_CCB *p_ccb)
{
    assert(p_ccb != NULL);
    btu_free_quick_timer (&p_ccb->fcrb.mon_retrans_timer);
}