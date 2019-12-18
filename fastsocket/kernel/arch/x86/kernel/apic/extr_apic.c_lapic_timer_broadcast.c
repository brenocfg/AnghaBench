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
struct cpumask {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* send_IPI_mask ) (struct cpumask const*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LOCAL_TIMER_VECTOR ; 
 TYPE_1__* apic ; 
 int /*<<< orphan*/  stub1 (struct cpumask const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lapic_timer_broadcast(const struct cpumask *mask)
{
#ifdef CONFIG_SMP
	apic->send_IPI_mask(mask, LOCAL_TIMER_VECTOR);
#endif
}