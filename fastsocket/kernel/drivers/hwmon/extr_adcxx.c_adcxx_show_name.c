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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adcxx {int channels; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct adcxx* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static ssize_t adcxx_show_name(struct device *dev, struct device_attribute
			      *devattr, char *buf)
{
	struct spi_device *spi = to_spi_device(dev);
	struct adcxx *adc = dev_get_drvdata(&spi->dev);

	return sprintf(buf, "adcxx%ds\n", adc->channels);
}