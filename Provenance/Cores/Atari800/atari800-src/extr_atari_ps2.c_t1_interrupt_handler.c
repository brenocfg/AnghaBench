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
 scalar_t__ T1_MODE ; 
 int /*<<< orphan*/  iWakeupThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleeping_thread_id ; 

__attribute__((used)) static int t1_interrupt_handler(int ca)
{
	iWakeupThread(sleeping_thread_id);
	T1_MODE = 0; // disable
	// __asm__ volatile("sync.l; ei"); // XXX: necessary?
	return -1; // XXX: or 0? what does it mean?
}