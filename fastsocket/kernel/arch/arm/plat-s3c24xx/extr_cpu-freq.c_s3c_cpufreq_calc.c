#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned long fclk; unsigned long hclk; unsigned long pclk; int hclk_tns; } ;
struct TYPE_6__ {unsigned long h_divisor; unsigned long p_divisor; } ;
struct TYPE_4__ {unsigned long frequency; } ;
struct s3c_cpufreq_config {TYPE_2__ freq; TYPE_3__ divs; TYPE_1__ pll; } ;

/* Variables and functions */

__attribute__((used)) static inline void s3c_cpufreq_calc(struct s3c_cpufreq_config *cfg)
{
	unsigned long pll = cfg->pll.frequency;

	cfg->freq.fclk = pll;
	cfg->freq.hclk = pll / cfg->divs.h_divisor;
	cfg->freq.pclk = pll / cfg->divs.p_divisor;

	/* convert hclk into 10ths of nanoseconds for io calcs */
	cfg->freq.hclk_tns = 1000000000 / (cfg->freq.hclk / 10);
}