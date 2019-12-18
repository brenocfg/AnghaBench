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
struct clocksource {int dummy; } ;
typedef  int /*<<< orphan*/  cycle_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_tick ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 () ; 
 TYPE_1__* tick_ops ; 

__attribute__((used)) static cycle_t clocksource_tick_read(struct clocksource *cs)
{
	return tick_ops->get_tick();
}