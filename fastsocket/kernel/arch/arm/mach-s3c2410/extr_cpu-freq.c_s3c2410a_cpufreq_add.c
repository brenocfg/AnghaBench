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
struct sys_device {int dummy; } ;
struct TYPE_3__ {int fclk; int hclk; int pclk; } ;
struct TYPE_4__ {char* name; TYPE_1__ max; } ;

/* Variables and functions */
 int s3c2410_cpufreq_add (struct sys_device*) ; 
 TYPE_2__ s3c2410_cpufreq_info ; 

__attribute__((used)) static int s3c2410a_cpufreq_add(struct sys_device *sysdev)
{
	/* alter the maximum freq settings for S3C2410A. If a board knows
	 * it only has a maximum of 200, then it should register its own
	 * limits. */

	s3c2410_cpufreq_info.max.fclk = 266000000;
	s3c2410_cpufreq_info.max.hclk = 133000000;
	s3c2410_cpufreq_info.max.pclk =  66500000;
	s3c2410_cpufreq_info.name = "s3c2410a";

	return s3c2410_cpufreq_add(sysdev);
}