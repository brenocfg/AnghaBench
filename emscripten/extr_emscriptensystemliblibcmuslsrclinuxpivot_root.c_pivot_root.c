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
 int /*<<< orphan*/  SYS_pivot_root ; 
 int syscall (int /*<<< orphan*/ ,char const*,char const*) ; 

int pivot_root(const char *new, const char *old)
{
	return syscall(SYS_pivot_root, new, old);
}