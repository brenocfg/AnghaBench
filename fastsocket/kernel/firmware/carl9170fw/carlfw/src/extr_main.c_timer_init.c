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

/* Variables and functions */
 int /*<<< orphan*/  AR9170_TIMER_REG_CONTROL ; 
 int /*<<< orphan*/  AR9170_TIMER_REG_INTERRUPT ; 
 scalar_t__ AR9170_TIMER_REG_TIMER0 ; 
 int /*<<< orphan*/  BIT (unsigned int const) ; 
 int /*<<< orphan*/  orl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set (scalar_t__,unsigned int const) ; 

__attribute__((used)) static void timer_init(const unsigned int timer, const unsigned int interval)
{
	/* Set timer to periodic mode */
	orl(AR9170_TIMER_REG_CONTROL, BIT(timer));

	/* Set time interval */
	set(AR9170_TIMER_REG_TIMER0 + (timer << 2), interval - 1);

	/* Clear timer interrupt flag */
	orl(AR9170_TIMER_REG_INTERRUPT, BIT(timer));
}