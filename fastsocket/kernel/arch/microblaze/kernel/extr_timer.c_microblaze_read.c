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
typedef  int /*<<< orphan*/  cycle_t ;

/* Variables and functions */
 scalar_t__ TCR1 ; 
 scalar_t__ TIMER_BASE ; 
 int /*<<< orphan*/  in_be32 (scalar_t__) ; 

__attribute__((used)) static cycle_t microblaze_read(struct clocksource *cs)
{
	/* reading actual value of timer 1 */
	return (cycle_t) (in_be32(TIMER_BASE + TCR1));
}