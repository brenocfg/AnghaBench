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
struct mpc8xxx_spi_probe_info {int /*<<< orphan*/ * alow_flags; int /*<<< orphan*/ * gpios; } ;
struct fsl_spi_platform_data {int max_chipselect; } ;
struct device {struct fsl_spi_platform_data* platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 struct mpc8xxx_spi_probe_info* to_of_pinfo (struct fsl_spi_platform_data*) ; 

__attribute__((used)) static int of_mpc8xxx_spi_free_chipselects(struct device *dev)
{
	struct fsl_spi_platform_data *pdata = dev->platform_data;
	struct mpc8xxx_spi_probe_info *pinfo = to_of_pinfo(pdata);
	int i;

	if (!pinfo->gpios)
		return 0;

	for (i = 0; i < pdata->max_chipselect; i++) {
		if (gpio_is_valid(pinfo->gpios[i]))
			gpio_free(pinfo->gpios[i]);
	}

	kfree(pinfo->gpios);
	kfree(pinfo->alow_flags);
	return 0;
}