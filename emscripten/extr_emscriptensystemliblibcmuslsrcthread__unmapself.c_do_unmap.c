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
 int /*<<< orphan*/  SYS_exit ; 
 int /*<<< orphan*/  SYS_munmap ; 
 int /*<<< orphan*/  __syscall (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  unmap_base ; 
 int /*<<< orphan*/  unmap_size ; 

__attribute__((used)) static void do_unmap()
{
	__syscall(SYS_munmap, unmap_base, unmap_size);
	__syscall(SYS_exit);
}