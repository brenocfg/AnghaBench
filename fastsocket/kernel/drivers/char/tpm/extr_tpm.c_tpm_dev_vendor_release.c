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
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ miscdev; int /*<<< orphan*/  (* release ) (int /*<<< orphan*/ ) ;} ;
struct tpm_chip {TYPE_2__ vendor; int /*<<< orphan*/  dev_num; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_mask ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void tpm_dev_vendor_release(struct tpm_chip *chip)
{
	if (chip->vendor.release)
		chip->vendor.release(chip->dev);

	clear_bit(chip->dev_num, dev_mask);
	kfree(chip->vendor.miscdev.name);
}