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
struct workqueue_struct {int dummy; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 struct cpumask const* cpu_populated_map ; 
 struct cpumask const* cpu_singlethread_map ; 
 scalar_t__ is_wq_single_threaded (struct workqueue_struct*) ; 

__attribute__((used)) static const struct cpumask *wq_cpu_map(struct workqueue_struct *wq)
{
	return is_wq_single_threaded(wq)
		? cpu_singlethread_map : cpu_populated_map;
}