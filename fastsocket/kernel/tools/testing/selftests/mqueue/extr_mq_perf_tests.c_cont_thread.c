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
typedef  int /*<<< orphan*/  buff ;

/* Variables and functions */
 int MSG_SIZE ; 
 scalar_t__* cpu_threads ; 
 int* cpus_to_pin ; 
 int /*<<< orphan*/  mq_receive (int /*<<< orphan*/ ,char*,int,int*) ; 
 scalar_t__ mq_send (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int num_cpus_to_pin ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 scalar_t__ pthread_self () ; 
 int /*<<< orphan*/  queue ; 

void *cont_thread(void *arg)
{
	char buff[MSG_SIZE];
	int i, priority;

	for (i = 0; i < num_cpus_to_pin; i++)
		if (cpu_threads[i] == pthread_self())
			break;
	printf("\tStarted continuous mode thread %d on CPU %d\n", i,
	       cpus_to_pin[i]);
	while (1) {
		while(mq_send(queue, buff, sizeof(buff), 0) == 0)
			;
		mq_receive(queue, buff, sizeof(buff), &priority);
	}
}