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
struct perf_event_attr {scalar_t__ type; scalar_t__ config; } ;

/* Variables and functions */
 scalar_t__ PERF_COUNT_SW_PAGE_FAULTS ; 
 scalar_t__ PERF_COUNT_SW_PAGE_FAULTS_MAJ ; 
 scalar_t__ PERF_COUNT_SW_PAGE_FAULTS_MIN ; 
 scalar_t__ PERF_TYPE_SOFTWARE ; 
 scalar_t__ is_bts_event (struct perf_event_attr*) ; 

__attribute__((used)) static bool sample_addr_correlates_sym(struct perf_event_attr *attr)
{
	if ((attr->type == PERF_TYPE_SOFTWARE) &&
	    ((attr->config == PERF_COUNT_SW_PAGE_FAULTS) ||
	     (attr->config == PERF_COUNT_SW_PAGE_FAULTS_MIN) ||
	     (attr->config == PERF_COUNT_SW_PAGE_FAULTS_MAJ)))
		return true;

	if (is_bts_event(attr))
		return true;

	return false;
}