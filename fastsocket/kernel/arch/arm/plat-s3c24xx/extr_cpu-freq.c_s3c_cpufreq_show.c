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
struct TYPE_6__ {int /*<<< orphan*/  p_divisor; int /*<<< orphan*/  h_divisor; } ;
struct TYPE_5__ {int /*<<< orphan*/  pclk; int /*<<< orphan*/  hclk; int /*<<< orphan*/  armclk; int /*<<< orphan*/  fclk; } ;
struct TYPE_4__ {int /*<<< orphan*/  frequency; } ;
struct s3c_cpufreq_config {TYPE_3__ divs; TYPE_2__ freq; TYPE_1__ pll; } ;

/* Variables and functions */
 int /*<<< orphan*/  s3c_freq_dbg (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s3c_cpufreq_show(const char *pfx,
				 struct s3c_cpufreq_config *cfg)
{
	s3c_freq_dbg("%s: Fvco=%u, F=%lu, A=%lu, H=%lu (%u), P=%lu (%u)\n",
		     pfx, cfg->pll.frequency, cfg->freq.fclk, cfg->freq.armclk,
		     cfg->freq.hclk, cfg->divs.h_divisor,
		     cfg->freq.pclk, cfg->divs.p_divisor);
}