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
struct TYPE_2__ {int /*<<< orphan*/  (* cancel ) (struct tpm_chip*) ;} ;
struct tpm_chip {TYPE_1__ vendor; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 struct tpm_chip* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct tpm_chip*) ; 

ssize_t tpm_store_cancel(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count)
{
	struct tpm_chip *chip = dev_get_drvdata(dev);
	if (chip == NULL)
		return 0;

	chip->vendor.cancel(chip);
	return count;
}