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
struct mpc8xxx_spi_probe_info {int* gpios; int* alow_flags; } ;
struct fsl_spi_platform_data {int max_chipselect; int /*<<< orphan*/  cs_control; } ;
struct device_node {int dummy; } ;
struct device {struct fsl_spi_platform_data* platform_data; int /*<<< orphan*/  archdata; } ;
typedef  enum of_gpio_flags { ____Placeholder_of_gpio_flags } of_gpio_flags ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int OF_GPIO_ACTIVE_LOW ; 
 struct device_node* dev_archdata_get_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int gpio_direction_output (int,int) ; 
 int /*<<< orphan*/  gpio_free (int) ; 
 scalar_t__ gpio_is_valid (int) ; 
 int gpio_request (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int* kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,unsigned int) ; 
 int /*<<< orphan*/  mpc8xxx_spi_cs_control ; 
 int of_get_gpio_flags (struct device_node*,int,int*) ; 
 unsigned int of_gpio_count (struct device_node*) ; 
 struct mpc8xxx_spi_probe_info* to_of_pinfo (struct fsl_spi_platform_data*) ; 

__attribute__((used)) static int of_mpc8xxx_spi_get_chipselects(struct device *dev)
{
	struct device_node *np = dev_archdata_get_node(&dev->archdata);
	struct fsl_spi_platform_data *pdata = dev->platform_data;
	struct mpc8xxx_spi_probe_info *pinfo = to_of_pinfo(pdata);
	unsigned int ngpios;
	int i = 0;
	int ret;

	ngpios = of_gpio_count(np);
	if (!ngpios) {
		/*
		 * SPI w/o chip-select line. One SPI device is still permitted
		 * though.
		 */
		pdata->max_chipselect = 1;
		return 0;
	}

	pinfo->gpios = kmalloc(ngpios * sizeof(*pinfo->gpios), GFP_KERNEL);
	if (!pinfo->gpios)
		return -ENOMEM;
	memset(pinfo->gpios, -1, ngpios * sizeof(*pinfo->gpios));

	pinfo->alow_flags = kzalloc(ngpios * sizeof(*pinfo->alow_flags),
				    GFP_KERNEL);
	if (!pinfo->alow_flags) {
		ret = -ENOMEM;
		goto err_alloc_flags;
	}

	for (; i < ngpios; i++) {
		int gpio;
		enum of_gpio_flags flags;

		gpio = of_get_gpio_flags(np, i, &flags);
		if (!gpio_is_valid(gpio)) {
			dev_err(dev, "invalid gpio #%d: %d\n", i, gpio);
			goto err_loop;
		}

		ret = gpio_request(gpio, dev_name(dev));
		if (ret) {
			dev_err(dev, "can't request gpio #%d: %d\n", i, ret);
			goto err_loop;
		}

		pinfo->gpios[i] = gpio;
		pinfo->alow_flags[i] = flags & OF_GPIO_ACTIVE_LOW;

		ret = gpio_direction_output(pinfo->gpios[i],
					    pinfo->alow_flags[i]);
		if (ret) {
			dev_err(dev, "can't set output direction for gpio "
				"#%d: %d\n", i, ret);
			goto err_loop;
		}
	}

	pdata->max_chipselect = ngpios;
	pdata->cs_control = mpc8xxx_spi_cs_control;

	return 0;

err_loop:
	while (i >= 0) {
		if (gpio_is_valid(pinfo->gpios[i]))
			gpio_free(pinfo->gpios[i]);
		i--;
	}

	kfree(pinfo->alow_flags);
	pinfo->alow_flags = NULL;
err_alloc_flags:
	kfree(pinfo->gpios);
	pinfo->gpios = NULL;
	return ret;
}