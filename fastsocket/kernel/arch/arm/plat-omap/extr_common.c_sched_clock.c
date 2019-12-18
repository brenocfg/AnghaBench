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
struct TYPE_3__ {int /*<<< orphan*/  shift; int /*<<< orphan*/  mult; int /*<<< orphan*/  (* read ) (TYPE_1__*) ;} ;

/* Variables and functions */
 TYPE_1__ clocksource_32k ; 
 unsigned long long clocksource_cyc2ns (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

unsigned long long sched_clock(void)
{
	return clocksource_cyc2ns(clocksource_32k.read(&clocksource_32k),
				  clocksource_32k.mult, clocksource_32k.shift);
}