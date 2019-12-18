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
typedef  int cvmx_cmd_queue_id_t ;

/* Variables and functions */

__attribute__((used)) static inline int __cvmx_cmd_queue_get_index(cvmx_cmd_queue_id_t queue_id)
{
	/*
	 * Warning: This code currently only works with devices that
	 * have 256 queues or less. Devices with more than 16 queues
	 * are layed out in memory to allow cores quick access to
	 * every 16th queue. This reduces cache thrashing when you are
	 * running 16 queues per port to support lockless operation.
	 */
	int unit = queue_id >> 16;
	int q = (queue_id >> 4) & 0xf;
	int core = queue_id & 0xf;
	return unit * 256 + core * 16 + q;
}