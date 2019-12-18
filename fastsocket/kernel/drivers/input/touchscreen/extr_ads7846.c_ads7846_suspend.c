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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct ads7846 {int is_suspended; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  ads7846_disable (struct ads7846*) ; 
 struct ads7846* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ads7846_suspend(struct spi_device *spi, pm_message_t message)
{
	struct ads7846 *ts = dev_get_drvdata(&spi->dev);

	spin_lock_irq(&ts->lock);

	ts->is_suspended = 1;
	ads7846_disable(ts);

	spin_unlock_irq(&ts->lock);

	return 0;

}