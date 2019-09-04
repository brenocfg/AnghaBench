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
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SYS_brk ; 
 scalar_t__ __syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __syscall_ret (int /*<<< orphan*/ ) ; 

void *sbrk(intptr_t inc)
{
	if (inc) return (void *)__syscall_ret(-ENOMEM);
	return (void *)__syscall(SYS_brk, 0);
}