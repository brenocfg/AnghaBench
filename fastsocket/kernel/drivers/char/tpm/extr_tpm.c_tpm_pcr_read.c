#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct tpm_chip {TYPE_2__* dev; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int ENODEV ; 
 int __tpm_pcr_read (struct tpm_chip*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 struct tpm_chip* tpm_chip_find_get (int /*<<< orphan*/ ) ; 

int tpm_pcr_read(u32 chip_num, int pcr_idx, u8 *res_buf)
{
	struct tpm_chip *chip;
	int rc;

	chip = tpm_chip_find_get(chip_num);
	if (chip == NULL)
		return -ENODEV;
	rc = __tpm_pcr_read(chip, pcr_idx, res_buf);
	module_put(chip->dev->driver->owner);
	return rc;
}