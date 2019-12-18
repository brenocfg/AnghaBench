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
struct TYPE_2__ {int /*<<< orphan*/  sysdev; } ;

/* Variables and functions */
 int MAX_RT_TEST_MUTEXES ; 
 int MAX_RT_TEST_THREADS ; 
 int /*<<< orphan*/  attr_command ; 
 int /*<<< orphan*/  attr_status ; 
 int init_test_thread (int) ; 
 int /*<<< orphan*/ * mutexes ; 
 int /*<<< orphan*/  printk (char*,char*) ; 
 int /*<<< orphan*/  rt_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rttest_lock ; 
 int /*<<< orphan*/  rttest_sysclass ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int sysdev_class_register (int /*<<< orphan*/ *) ; 
 int sysdev_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* thread_data ; 

__attribute__((used)) static int init_rttest(void)
{
	int ret, i;

	spin_lock_init(&rttest_lock);

	for (i = 0; i < MAX_RT_TEST_MUTEXES; i++)
		rt_mutex_init(&mutexes[i]);

	ret = sysdev_class_register(&rttest_sysclass);
	if (ret)
		return ret;

	for (i = 0; i < MAX_RT_TEST_THREADS; i++) {
		ret = init_test_thread(i);
		if (ret)
			break;
		ret = sysdev_create_file(&thread_data[i].sysdev, &attr_status);
		if (ret)
			break;
		ret = sysdev_create_file(&thread_data[i].sysdev, &attr_command);
		if (ret)
			break;
	}

	printk("Initializing RT-Tester: %s\n", ret ? "Failed" : "OK" );

	return ret;
}