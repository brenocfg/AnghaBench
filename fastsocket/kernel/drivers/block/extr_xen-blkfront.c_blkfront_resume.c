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
struct xenbus_device {int /*<<< orphan*/  nodename; int /*<<< orphan*/  dev; } ;
struct blkfront_info {scalar_t__ connected; } ;

/* Variables and functions */
 scalar_t__ BLKIF_STATE_CONNECTED ; 
 scalar_t__ BLKIF_STATE_SUSPENDED ; 
 int /*<<< orphan*/  blkif_free (struct blkfront_info*,int) ; 
 int blkif_recover (struct blkfront_info*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct blkfront_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int talk_to_blkback (struct xenbus_device*,struct blkfront_info*) ; 

__attribute__((used)) static int blkfront_resume(struct xenbus_device *dev)
{
	struct blkfront_info *info = dev_get_drvdata(&dev->dev);
	int err;

	dev_dbg(&dev->dev, "blkfront_resume: %s\n", dev->nodename);

	blkif_free(info, info->connected == BLKIF_STATE_CONNECTED);

	err = talk_to_blkback(dev, info);
	if (info->connected == BLKIF_STATE_SUSPENDED && !err)
		err = blkif_recover(info);

	return err;
}