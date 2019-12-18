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
typedef  int /*<<< orphan*/  user_addr_t ;
struct proc {int /*<<< orphan*/  user_stack; } ;

/* Variables and functions */

__attribute__((used)) static user_addr_t
proc_get_user_stack(struct proc *p)
{
	return p->user_stack;
}