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
struct snd_soc_dai {int /*<<< orphan*/  private_data; } ;
struct omap_mcbsp_reg_cfg {int /*<<< orphan*/  srgr1; } ;
struct omap_mcbsp_data {struct omap_mcbsp_reg_cfg regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLKGDV (int) ; 
 int ENODEV ; 
 int OMAP_MCBSP_CLKGDV ; 
 struct omap_mcbsp_data* to_mcbsp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_mcbsp_dai_set_clkdiv(struct snd_soc_dai *cpu_dai,
				     int div_id, int div)
{
	struct omap_mcbsp_data *mcbsp_data = to_mcbsp(cpu_dai->private_data);
	struct omap_mcbsp_reg_cfg *regs = &mcbsp_data->regs;

	if (div_id != OMAP_MCBSP_CLKGDV)
		return -ENODEV;

	regs->srgr1	|= CLKGDV(div - 1);

	return 0;
}