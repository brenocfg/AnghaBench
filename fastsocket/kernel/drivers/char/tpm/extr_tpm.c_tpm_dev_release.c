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
struct tpm_chip {int /*<<< orphan*/  (* release ) (struct device*) ;} ;
struct device {int dummy; } ;

/* Variables and functions */
 struct tpm_chip* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  kfree (struct tpm_chip*) ; 
 int /*<<< orphan*/  stub1 (struct device*) ; 
 int /*<<< orphan*/  tpm_dev_vendor_release (struct tpm_chip*) ; 

void tpm_dev_release(struct device *dev)
{
	struct tpm_chip *chip = dev_get_drvdata(dev);

	tpm_dev_vendor_release(chip);

	chip->release(dev);
	kfree(chip);
}