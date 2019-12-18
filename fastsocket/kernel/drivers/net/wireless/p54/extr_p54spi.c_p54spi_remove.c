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
struct spi_device {int dummy; } ;
struct p54s_priv {int /*<<< orphan*/  hw; int /*<<< orphan*/  mutex; int /*<<< orphan*/  firmware; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct spi_device*) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p54_free_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p54_unregister_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p54spi_gpio_irq ; 
 int /*<<< orphan*/  p54spi_gpio_power ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 
 struct p54s_priv* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int p54spi_remove(struct spi_device *spi)
{
	struct p54s_priv *priv = spi_get_drvdata(spi);

	p54_unregister_common(priv->hw);

	free_irq(gpio_to_irq(p54spi_gpio_irq), spi);

	gpio_free(p54spi_gpio_power);
	gpio_free(p54spi_gpio_irq);
	release_firmware(priv->firmware);

	mutex_destroy(&priv->mutex);

	p54_free_common(priv->hw);

	return 0;
}