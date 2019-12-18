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
struct mmc_card {scalar_t__ type; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ MMC_TYPE_MMC ; 
 scalar_t__ MMC_TYPE_SD ; 
 int /*<<< orphan*/  dev_attr_test ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mmc_test_probe(struct mmc_card *card)
{
	int ret;

	if ((card->type != MMC_TYPE_MMC) && (card->type != MMC_TYPE_SD))
		return -ENODEV;

	ret = device_create_file(&card->dev, &dev_attr_test);
	if (ret)
		return ret;

	dev_info(&card->dev, "Card claimed for testing.\n");

	return 0;
}