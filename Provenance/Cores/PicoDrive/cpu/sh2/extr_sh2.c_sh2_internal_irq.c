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
struct TYPE_3__ {int pending_int_irq; int pending_int_vector; int pending_level; int test_irq; } ;
typedef  TYPE_1__ SH2 ;

/* Variables and functions */

void sh2_internal_irq(SH2 *sh2, int level, int vector)
{
	// FIXME: multiple internal irqs not handled..
	// assuming internal irqs never clear until accepted
	sh2->pending_int_irq = level;
	sh2->pending_int_vector = vector;
	if (level > sh2->pending_level)
		sh2->pending_level = level;

	sh2->test_irq = 1;
}