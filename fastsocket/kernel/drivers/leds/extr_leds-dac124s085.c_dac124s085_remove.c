#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct spi_device {int dummy; } ;
struct dac124s085 {TYPE_1__* leds; } ;
struct TYPE_2__ {int /*<<< orphan*/  work; int /*<<< orphan*/  ldev; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dac124s085*) ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 
 struct dac124s085* spi_get_drvdata (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dac124s085_remove(struct spi_device *spi)
{
	struct dac124s085	*dac = spi_get_drvdata(spi);
	int i;

	for (i = 0; i < ARRAY_SIZE(dac->leds); i++) {
		led_classdev_unregister(&dac->leds[i].ldev);
		cancel_work_sync(&dac->leds[i].work);
	}

	spi_set_drvdata(spi, NULL);
	kfree(dac);

	return 0;
}