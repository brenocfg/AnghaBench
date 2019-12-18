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
struct cpufreq_policy {TYPE_1__* governor; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* show_setspeed ) (struct cpufreq_policy*,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 int /*<<< orphan*/  stub1 (struct cpufreq_policy*,char*) ; 

__attribute__((used)) static ssize_t show_scaling_setspeed(struct cpufreq_policy *policy, char *buf)
{
	if (!policy->governor || !policy->governor->show_setspeed)
		return sprintf(buf, "<unsupported>\n");

	return policy->governor->show_setspeed(policy, buf);
}