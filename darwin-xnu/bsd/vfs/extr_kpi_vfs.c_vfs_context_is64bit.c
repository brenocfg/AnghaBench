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
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  scalar_t__ proc_t ;

/* Variables and functions */
 int proc_is64bit (scalar_t__) ; 
 scalar_t__ vfs_context_proc (int /*<<< orphan*/ ) ; 

int
vfs_context_is64bit(vfs_context_t ctx)
{
	proc_t proc = vfs_context_proc(ctx);

	if (proc)
		return(proc_is64bit(proc));
	return(0);
}