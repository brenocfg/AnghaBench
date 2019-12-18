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
struct perf_output_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_output_put_handle (struct perf_output_handle*) ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

void perf_output_end(struct perf_output_handle *handle)
{
	perf_output_put_handle(handle);
	rcu_read_unlock();
}