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
 int /*<<< orphan*/  in_nmi () ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  tracing_off_permanent () ; 

__attribute__((used)) static inline int rb_ok_to_lock(void)
{
	/*
	 * If an NMI die dumps out the content of the ring buffer
	 * do not grab locks. We also permanently disable the ring
	 * buffer too. A one time deal is all you get from reading
	 * the ring buffer from an NMI.
	 */
	if (likely(!in_nmi()))
		return 1;

	tracing_off_permanent();
	return 0;
}