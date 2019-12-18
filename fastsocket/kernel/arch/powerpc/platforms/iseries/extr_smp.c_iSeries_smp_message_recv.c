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

/* Variables and functions */
 int /*<<< orphan*/ * iSeries_smp_message ; 
 int num_online_cpus () ; 
 int /*<<< orphan*/  smp_message_recv (int) ; 
 int smp_processor_id () ; 
 scalar_t__ test_and_clear_bit (int,int /*<<< orphan*/ *) ; 

void iSeries_smp_message_recv(void)
{
	int cpu = smp_processor_id();
	int msg;

	if (num_online_cpus() < 2)
		return;

	for (msg = 0; msg < 4; msg++)
		if (test_and_clear_bit(msg, &iSeries_smp_message[cpu]))
			smp_message_recv(msg);
}