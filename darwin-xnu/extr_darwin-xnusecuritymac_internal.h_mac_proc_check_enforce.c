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
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */

__attribute__((used)) static __inline__ bool mac_proc_check_enforce(proc_t p)
{
#if CONFIG_MACF
	// Don't apply policies to the kernel itself.
	return (p != kernproc);
#else
#pragma unused(p)
	return false;
#endif // CONFIG_MACF
}