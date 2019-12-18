#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ tv64; } ;
struct bcm_op {int flags; TYPE_1__ kt_ival1; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int RX_NO_AUTOTIMER ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,TYPE_1__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm_rx_starttimer(struct bcm_op *op)
{
	if (op->flags & RX_NO_AUTOTIMER)
		return;

	if (op->kt_ival1.tv64)
		hrtimer_start(&op->timer, op->kt_ival1, HRTIMER_MODE_REL);
}