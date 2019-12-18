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
 int ENODEV ; 
 int /*<<< orphan*/  cpu_mid_prop () ; 
 int prom_getintdefault (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sparc_cpu_model ; 
 scalar_t__ sun4m ; 

__attribute__((used)) static int cpu_mid_compare(int nd, int instance, void *_arg)
{
	int desired_mid = (int) _arg;
	int this_mid;

	this_mid = prom_getintdefault(nd, cpu_mid_prop(), 0);
	if (this_mid == desired_mid
	    || (sparc_cpu_model == sun4m && (this_mid & 3) == desired_mid))
		return 0;
	return -ENODEV;
}