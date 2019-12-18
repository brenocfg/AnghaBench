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
struct rb_root {int dummy; } ;
struct machine {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int machine__create_kernel_maps (struct machine*) ; 
 struct machine* machines__findnew (struct rb_root*,int /*<<< orphan*/ ) ; 

int machines__create_kernel_maps(struct rb_root *machines, pid_t pid)
{
	struct machine *machine = machines__findnew(machines, pid);

	if (machine == NULL)
		return -1;

	return machine__create_kernel_maps(machine);
}