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
struct ssfdcr_record {struct ssfdcr_record* logic_block_map; } ;
struct mtd_blktrans_dev {int /*<<< orphan*/  devnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTD_DEBUG_LEVEL1 ; 
 int /*<<< orphan*/  del_mtd_blktrans_dev (struct mtd_blktrans_dev*) ; 
 int /*<<< orphan*/  kfree (struct ssfdcr_record*) ; 

__attribute__((used)) static void ssfdcr_remove_dev(struct mtd_blktrans_dev *dev)
{
	struct ssfdcr_record *ssfdc = (struct ssfdcr_record *)dev;

	DEBUG(MTD_DEBUG_LEVEL1, "SSFDC_RO: remove_dev (i=%d)\n", dev->devnum);

	del_mtd_blktrans_dev(dev);
	kfree(ssfdc->logic_block_map);
	kfree(ssfdc);
}