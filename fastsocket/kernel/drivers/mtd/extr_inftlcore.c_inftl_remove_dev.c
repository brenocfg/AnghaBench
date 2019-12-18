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
struct INFTLrecord {struct INFTLrecord* VUtable; struct INFTLrecord* PUtable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTD_DEBUG_LEVEL3 ; 
 int /*<<< orphan*/  del_mtd_blktrans_dev (struct mtd_blktrans_dev*) ; 
 int /*<<< orphan*/  kfree (struct INFTLrecord*) ; 

__attribute__((used)) static void inftl_remove_dev(struct mtd_blktrans_dev *dev)
{
	struct INFTLrecord *inftl = (void *)dev;

	DEBUG(MTD_DEBUG_LEVEL3, "INFTL: remove_dev (i=%d)\n", dev->devnum);

	del_mtd_blktrans_dev(dev);

	kfree(inftl->PUtable);
	kfree(inftl->VUtable);
	kfree(inftl);
}