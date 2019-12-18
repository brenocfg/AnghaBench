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
 int /*<<< orphan*/  max (int,int) ; 
 int num_online_cpus () ; 
 int /*<<< orphan*/  percpu_counter_batch ; 

__attribute__((used)) static void compute_batch_value(void)
{
	int nr = num_online_cpus();

	percpu_counter_batch = max(32, nr*2);
}