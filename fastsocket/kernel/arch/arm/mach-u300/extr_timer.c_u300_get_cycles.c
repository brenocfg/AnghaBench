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
struct clocksource {int dummy; } ;
typedef  int /*<<< orphan*/  cycles_t ;
typedef  int /*<<< orphan*/  cycle_t ;

/* Variables and functions */
 scalar_t__ U300_TIMER_APP_GPT2CC ; 
 scalar_t__ U300_TIMER_APP_VBASE ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static cycle_t u300_get_cycles(struct clocksource *cs)
{
	return (cycles_t) readl(U300_TIMER_APP_VBASE + U300_TIMER_APP_GPT2CC);
}