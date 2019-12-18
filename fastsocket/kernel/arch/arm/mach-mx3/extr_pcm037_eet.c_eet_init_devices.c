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

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ PCM037_EET ; 
 int /*<<< orphan*/  machine_is_pcm037 () ; 
 int /*<<< orphan*/  mxc_iomux_setup_multiple_pins (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mxc_register_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mxc_spi_device0 ; 
 int /*<<< orphan*/  pcm037_eet_pins ; 
 int /*<<< orphan*/  pcm037_gpio_keys_device ; 
 int /*<<< orphan*/  pcm037_spi1_master ; 
 int /*<<< orphan*/  pcm037_spi_dev ; 
 scalar_t__ pcm037_variant () ; 
 int /*<<< orphan*/  platform_device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_register_board_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int eet_init_devices(void)
{
	if (!machine_is_pcm037() || pcm037_variant() != PCM037_EET)
		return 0;

	mxc_iomux_setup_multiple_pins(pcm037_eet_pins,
				ARRAY_SIZE(pcm037_eet_pins), "pcm037_eet");

	/* SPI */
	spi_register_board_info(pcm037_spi_dev, ARRAY_SIZE(pcm037_spi_dev));
#if defined(CONFIG_SPI_IMX) || defined(CONFIG_SPI_IMX_MODULE)
	mxc_register_device(&mxc_spi_device0, &pcm037_spi1_master);
#endif

	platform_device_register(&pcm037_gpio_keys_device);

	return 0;
}