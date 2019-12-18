#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cond; } ;
struct TYPE_3__ {scalar_t__ show_total_period; scalar_t__ show_nr_samples; scalar_t__ show_cpu_utilization; } ;

/* Variables and functions */
 size_t PERF_HPP__OVERHEAD_GUEST_SYS ; 
 size_t PERF_HPP__OVERHEAD_GUEST_US ; 
 size_t PERF_HPP__OVERHEAD_SYS ; 
 size_t PERF_HPP__OVERHEAD_US ; 
 size_t PERF_HPP__PERIOD ; 
 size_t PERF_HPP__SAMPLES ; 
 scalar_t__ perf_guest ; 
 TYPE_2__* perf_hpp__format ; 
 TYPE_1__ symbol_conf ; 

void perf_hpp__init(void)
{
	if (symbol_conf.show_cpu_utilization) {
		perf_hpp__format[PERF_HPP__OVERHEAD_SYS].cond = true;
		perf_hpp__format[PERF_HPP__OVERHEAD_US].cond = true;

		if (perf_guest) {
			perf_hpp__format[PERF_HPP__OVERHEAD_GUEST_SYS].cond = true;
			perf_hpp__format[PERF_HPP__OVERHEAD_GUEST_US].cond = true;
		}
	}

	if (symbol_conf.show_nr_samples)
		perf_hpp__format[PERF_HPP__SAMPLES].cond = true;

	if (symbol_conf.show_total_period)
		perf_hpp__format[PERF_HPP__PERIOD].cond = true;
}