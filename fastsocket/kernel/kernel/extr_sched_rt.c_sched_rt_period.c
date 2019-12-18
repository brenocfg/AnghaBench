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
typedef  int /*<<< orphan*/  u64 ;
struct rt_rq {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rt_period; } ;

/* Variables and functions */
 TYPE_1__ def_rt_bandwidth ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64 sched_rt_period(struct rt_rq *rt_rq)
{
	return ktime_to_ns(def_rt_bandwidth.rt_period);
}