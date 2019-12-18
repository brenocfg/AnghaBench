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
 int T0_MODE ; 
 int /*<<< orphan*/  timer_interrupt_ticks ; 

__attribute__((used)) static int t0_interrupt_handler(int ca)
{
	timer_interrupt_ticks++;
	T0_MODE |= 0x800; // clear overflow status
	// __asm__ volatile("sync.l; ei"); // XXX: necessary?
	return -1; // XXX: or 0? what does it mean?
}