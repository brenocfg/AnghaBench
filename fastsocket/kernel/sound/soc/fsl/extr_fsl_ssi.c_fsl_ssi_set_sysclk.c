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
struct snd_soc_dai {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int SND_SOC_CLOCK_IN ; 

__attribute__((used)) static int fsl_ssi_set_sysclk(struct snd_soc_dai *cpu_dai,
			      int clk_id, unsigned int freq, int dir)
{

	return (dir == SND_SOC_CLOCK_IN) ? 0 : -EINVAL;
}