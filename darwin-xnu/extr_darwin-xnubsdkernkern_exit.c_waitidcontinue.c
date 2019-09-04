#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  struct uthread* uthread_t ;
typedef  int /*<<< orphan*/  thread_t ;
struct waitid_nocancel_args {int dummy; } ;
struct _waitid_data {int* retval; struct waitid_nocancel_args* args; } ;
struct TYPE_2__ {struct _waitid_data uus_waitid_data; } ;
struct uthread {TYPE_1__ uu_save; } ;
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 int /*<<< orphan*/  current_proc () ; 
 int /*<<< orphan*/  current_thread () ; 
 scalar_t__ get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int waitid_nocancel (int /*<<< orphan*/ ,struct waitid_nocancel_args*,int*) ; 

int
waitidcontinue(int result)
{
	proc_t p;
	thread_t thread;
	uthread_t uth;
	struct _waitid_data *waitid_data;
	struct waitid_nocancel_args *uap;
	int *retval;

	if (result)
		return (result);

	p = current_proc();
	thread = current_thread();
	uth = (struct uthread *)get_bsdthread_info(thread);

	waitid_data = &uth->uu_save.uus_waitid_data;
	uap = waitid_data->args;
	retval = waitid_data->retval;
	return(waitid_nocancel(p, uap, retval));
}