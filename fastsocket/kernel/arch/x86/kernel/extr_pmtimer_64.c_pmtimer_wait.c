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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned int cyc2us (scalar_t__) ; 
 scalar_t__ inl (int /*<<< orphan*/ ) ; 
 scalar_t__ pmtimer_wait_tick () ; 
 int /*<<< orphan*/  pmtmr_ioport ; 

void pmtimer_wait(unsigned us)
{
	u32 a, b;
	a = pmtimer_wait_tick();
	do {
		b = inl(pmtmr_ioport);
		cpu_relax();
	} while (cyc2us(b - a) < us);
}