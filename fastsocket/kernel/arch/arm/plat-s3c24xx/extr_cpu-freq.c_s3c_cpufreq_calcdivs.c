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
struct s3c_cpufreq_config {TYPE_1__* info; } ;
struct TYPE_2__ {int (* calc_divs ) (struct s3c_cpufreq_config*) ;} ;

/* Variables and functions */
 int stub1 (struct s3c_cpufreq_config*) ; 

__attribute__((used)) static int s3c_cpufreq_calcdivs(struct s3c_cpufreq_config *cfg)
{
	return (cfg->info->calc_divs)(cfg);
}