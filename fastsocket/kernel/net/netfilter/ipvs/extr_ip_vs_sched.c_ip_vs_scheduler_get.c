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
struct ip_vs_scheduler {int dummy; } ;

/* Variables and functions */
 struct ip_vs_scheduler* ip_vs_sched_getbyname (char const*) ; 
 int /*<<< orphan*/  request_module (char*,char const*) ; 

struct ip_vs_scheduler *ip_vs_scheduler_get(const char *sched_name)
{
	struct ip_vs_scheduler *sched;

	/*
	 *  Search for the scheduler by sched_name
	 */
	sched = ip_vs_sched_getbyname(sched_name);

	/*
	 *  If scheduler not found, load the module and search again
	 */
	if (sched == NULL) {
		request_module("ip_vs_%s", sched_name);
		sched = ip_vs_sched_getbyname(sched_name);
	}

	return sched;
}