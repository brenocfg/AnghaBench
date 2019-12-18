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
struct spi_device {struct atmel_spi_device* controller_state; int /*<<< orphan*/  controller_data; int /*<<< orphan*/  master; } ;
struct atmel_spi_device {int dummy; } ;
struct atmel_spi {int /*<<< orphan*/  lock; struct spi_device* stay; } ;

/* Variables and functions */
 int /*<<< orphan*/  cs_deactivate (struct atmel_spi*,struct spi_device*) ; 
 int /*<<< orphan*/  gpio_free (unsigned int) ; 
 int /*<<< orphan*/  kfree (struct atmel_spi_device*) ; 
 struct atmel_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void atmel_spi_cleanup(struct spi_device *spi)
{
	struct atmel_spi	*as = spi_master_get_devdata(spi->master);
	struct atmel_spi_device	*asd = spi->controller_state;
	unsigned		gpio = (unsigned) spi->controller_data;
	unsigned long		flags;

	if (!asd)
		return;

	spin_lock_irqsave(&as->lock, flags);
	if (as->stay == spi) {
		as->stay = NULL;
		cs_deactivate(as, spi);
	}
	spin_unlock_irqrestore(&as->lock, flags);

	spi->controller_state = NULL;
	gpio_free(gpio);
	kfree(asd);
}