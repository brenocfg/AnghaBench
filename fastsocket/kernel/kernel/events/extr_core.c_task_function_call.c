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
struct remote_function_call {int (* func ) (void*) ;void* info; int ret; struct task_struct* p; } ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  remote_function ; 
 int /*<<< orphan*/  smp_call_function_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct remote_function_call*,int) ; 
 int /*<<< orphan*/  task_cpu (struct task_struct*) ; 
 scalar_t__ task_curr (struct task_struct*) ; 

__attribute__((used)) static int
task_function_call(struct task_struct *p, int (*func) (void *info), void *info)
{
	struct remote_function_call data = {
		.p	= p,
		.func	= func,
		.info	= info,
		.ret	= -ESRCH, /* No such (running) process */
	};

	if (task_curr(p))
		smp_call_function_single(task_cpu(p), remote_function, &data, 1);

	return data.ret;
}