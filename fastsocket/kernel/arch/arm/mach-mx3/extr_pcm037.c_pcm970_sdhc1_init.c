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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  IOMUX_TO_IRQ (int /*<<< orphan*/ ) ; 
 int IRQF_DISABLED ; 
 int IRQF_TRIGGER_FALLING ; 
 int /*<<< orphan*/  MX31_PIN_SCK6 ; 
 int /*<<< orphan*/  SDHC1_GPIO_DET ; 
 int /*<<< orphan*/  SDHC1_GPIO_WP ; 
 int /*<<< orphan*/  gpio_direction_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,void*) ; 

__attribute__((used)) static int pcm970_sdhc1_init(struct device *dev, irq_handler_t detect_irq,
		void *data)
{
	int ret;

	ret = gpio_request(SDHC1_GPIO_DET, "sdhc-detect");
	if (ret)
		return ret;

	gpio_direction_input(SDHC1_GPIO_DET);

#ifdef PCM970_SDHC_RW_SWITCH
	ret = gpio_request(SDHC1_GPIO_WP, "sdhc-wp");
	if (ret)
		goto err_gpio_free;
	gpio_direction_input(SDHC1_GPIO_WP);
#endif

	ret = request_irq(IOMUX_TO_IRQ(MX31_PIN_SCK6), detect_irq,
			IRQF_DISABLED | IRQF_TRIGGER_FALLING,
				"sdhc-detect", data);
	if (ret)
		goto err_gpio_free_2;

	return 0;

err_gpio_free_2:
#ifdef PCM970_SDHC_RW_SWITCH
	gpio_free(SDHC1_GPIO_WP);
err_gpio_free:
#endif
	gpio_free(SDHC1_GPIO_DET);

	return ret;
}