#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ct_timer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ct_xfitimer_irq_stop (struct ct_timer*) ; 

__attribute__((used)) static void ct_xfitimer_free_global(struct ct_timer *atimer)
{
	ct_xfitimer_irq_stop(atimer);
}