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
struct task_struct {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int EIO ; 
 int access_process_vm (struct task_struct*,long,long*,int,int) ; 

int generic_ptrace_pokedata(struct task_struct *tsk, long addr, long data)
{
	int copied;

	copied = access_process_vm(tsk, addr, &data, sizeof(data), 1);
	return (copied == sizeof(data)) ? 0 : -EIO;
}