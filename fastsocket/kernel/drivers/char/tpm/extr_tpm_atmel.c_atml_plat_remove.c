#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  iobase; int /*<<< orphan*/  region_size; int /*<<< orphan*/  base; scalar_t__ have_region; } ;
struct tpm_chip {int /*<<< orphan*/  dev; TYPE_1__ vendor; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  atmel_put_base_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tpm_chip* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 TYPE_2__* pdev ; 
 int /*<<< orphan*/  platform_device_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  tpm_remove_hardware (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atml_plat_remove(void)
{
	struct tpm_chip *chip = dev_get_drvdata(&pdev->dev);

	if (chip) {
		if (chip->vendor.have_region)
			atmel_release_region(chip->vendor.base,
					     chip->vendor.region_size);
		atmel_put_base_addr(chip->vendor.iobase);
		tpm_remove_hardware(chip->dev);
		platform_device_unregister(pdev);
	}
}