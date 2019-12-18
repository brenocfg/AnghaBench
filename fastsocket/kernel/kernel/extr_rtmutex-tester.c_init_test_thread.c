#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int id; int /*<<< orphan*/ * cls; } ;
struct TYPE_4__ {TYPE_2__ sysdev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  rttest_sysclass ; 
 int sysdev_register (TYPE_2__*) ; 
 int /*<<< orphan*/  test_func ; 
 TYPE_1__* thread_data ; 
 int /*<<< orphan*/ * threads ; 

__attribute__((used)) static int init_test_thread(int id)
{
	thread_data[id].sysdev.cls = &rttest_sysclass;
	thread_data[id].sysdev.id = id;

	threads[id] = kthread_run(test_func, &thread_data[id], "rt-test-%d", id);
	if (IS_ERR(threads[id]))
		return PTR_ERR(threads[id]);

	return sysdev_register(&thread_data[id].sysdev);
}