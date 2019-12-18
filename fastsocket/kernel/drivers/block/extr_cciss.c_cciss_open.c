#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct block_device {int /*<<< orphan*/  bd_dev; TYPE_5__* bd_disk; } ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_9__ {scalar_t__ heads; int /*<<< orphan*/  usage_count; int /*<<< orphan*/  LunID; scalar_t__ busy_configuring; } ;
typedef  TYPE_2__ drive_info_struct ;
struct TYPE_10__ {int /*<<< orphan*/  usage_count; TYPE_1__* pdev; } ;
typedef  TYPE_3__ ctlr_info_t ;
struct TYPE_11__ {int /*<<< orphan*/  disk_name; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  CTLR_LUNID ; 
 int EBUSY ; 
 int ENXIO ; 
 int EPERM ; 
 int MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* get_drv (TYPE_5__*) ; 
 TYPE_3__* get_host (TYPE_5__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cciss_open(struct block_device *bdev, fmode_t mode)
{
	ctlr_info_t *h = get_host(bdev->bd_disk);
	drive_info_struct *drv = get_drv(bdev->bd_disk);

	dev_dbg(&h->pdev->dev, "cciss_open %s\n", bdev->bd_disk->disk_name);
	if (drv->busy_configuring)
		return -EBUSY;
	/*
	 * Root is allowed to open raw volume zero even if it's not configured
	 * so array config can still work. Root is also allowed to open any
	 * volume that has a LUN ID, so it can issue IOCTL to reread the
	 * disk information.  I don't think I really like this
	 * but I'm already using way to many device nodes to claim another one
	 * for "raw controller".
	 */
	if (drv->heads == 0) {
		if (MINOR(bdev->bd_dev) != 0) {	/* not node 0? */
			/* if not node 0 make sure it is a partition = 0 */
			if (MINOR(bdev->bd_dev) & 0x0f) {
				return -ENXIO;
				/* if it is, make sure we have a LUN ID */
			} else if (memcmp(drv->LunID, CTLR_LUNID,
				sizeof(drv->LunID))) {
				return -ENXIO;
			}
		}
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
	}
	drv->usage_count++;
	h->usage_count++;
	return 0;
}