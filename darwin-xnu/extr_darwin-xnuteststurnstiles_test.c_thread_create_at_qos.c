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
typedef  scalar_t__ qos_class_t ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRIO_DARWIN_ROLE ; 
 int /*<<< orphan*/  PRIO_DARWIN_ROLE_UI_FOCAL ; 
 int /*<<< orphan*/  T_EXPECT_EQ (scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_LOG (char*) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_set_qos_class_np (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void* (*) (void*),void*) ; 
 int /*<<< orphan*/  pthread_get_qos_class_np (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int setpriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
thread_create_at_qos(qos_class_t qos, void * (*function)(void *), int type)
{
	qos_class_t qos_thread;
	pthread_t thread;
        pthread_attr_t attr;
	int ret;

	ret = setpriority(PRIO_DARWIN_ROLE, 0, PRIO_DARWIN_ROLE_UI_FOCAL);
	if (ret != 0) {
		T_LOG("set priority failed\n");
	}

        pthread_attr_init(&attr);
        pthread_attr_set_qos_class_np(&attr, qos, 0);
        pthread_create(&thread, &attr, function, (void *)type);

	T_LOG("pthread created\n");
	pthread_get_qos_class_np(thread, &qos_thread, NULL);
        T_EXPECT_EQ(qos_thread, (qos_class_t)qos, NULL);
}