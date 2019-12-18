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
struct TYPE_2__ {int /*<<< orphan*/  index; } ;
struct s3c_cpufreq_config {TYPE_1__ pll; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3C2410_MPLLCON ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void s3c2410_set_fvco(struct s3c_cpufreq_config *cfg)
{
	__raw_writel(cfg->pll.index, S3C2410_MPLLCON);
}