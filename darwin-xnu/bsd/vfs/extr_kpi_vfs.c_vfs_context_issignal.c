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
typedef  int /*<<< orphan*/  sigset_t ;
typedef  scalar_t__ proc_t ;

/* Variables and functions */
 int proc_pendingsignals (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ vfs_context_proc (int /*<<< orphan*/ ) ; 

int
vfs_context_issignal(vfs_context_t ctx, sigset_t mask)
{
	proc_t p = vfs_context_proc(ctx);
	if (p)
		return(proc_pendingsignals(p, mask));
	return(0);
}