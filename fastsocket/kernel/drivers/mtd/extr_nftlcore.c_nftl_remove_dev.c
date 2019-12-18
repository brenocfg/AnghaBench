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
struct mtd_blktrans_dev {int /*<<< orphan*/  devnum; } ;
struct NFTLrecord {struct NFTLrecord* EUNtable; struct NFTLrecord* ReplUnitTable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTD_DEBUG_LEVEL1 ; 
 int /*<<< orphan*/  del_mtd_blktrans_dev (struct mtd_blktrans_dev*) ; 
 int /*<<< orphan*/  kfree (struct NFTLrecord*) ; 

__attribute__((used)) static void nftl_remove_dev(struct mtd_blktrans_dev *dev)
{
	struct NFTLrecord *nftl = (void *)dev;

	DEBUG(MTD_DEBUG_LEVEL1, "NFTL: remove_dev (i=%d)\n", dev->devnum);

	del_mtd_blktrans_dev(dev);
	kfree(nftl->ReplUnitTable);
	kfree(nftl->EUNtable);
	kfree(nftl);
}