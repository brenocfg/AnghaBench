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
typedef  int /*<<< orphan*/  uint64_t ;
struct proc {int /*<<< orphan*/  p_return_to_kernel_offset; } ;

/* Variables and functions */

__attribute__((used)) static void
proc_set_return_to_kernel_offset(struct proc *p, uint64_t offset)
{
	p->p_return_to_kernel_offset = offset;
}