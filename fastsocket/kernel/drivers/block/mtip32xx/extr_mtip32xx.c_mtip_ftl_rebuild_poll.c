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
struct driver_data {TYPE_2__* pdev; TYPE_1__* port; int /*<<< orphan*/  dd_flag; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__* identify; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  MTIP_DDF_REMOVE_PENDING_BIT ; 
 scalar_t__ MTIP_FTL_REBUILD_MAGIC ; 
 int MTIP_FTL_REBUILD_OFFSET ; 
 int /*<<< orphan*/  MTIP_FTL_REBUILD_TIMEOUT_MS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 unsigned long jiffies ; 
 int jiffies_to_msecs (unsigned long) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtip_block_initialize (struct driver_data*) ; 
 scalar_t__ mtip_check_surprise_removal (TYPE_2__*) ; 
 scalar_t__ mtip_get_identify (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssleep (int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtip_ftl_rebuild_poll(struct driver_data *dd)
{
	unsigned long timeout, cnt = 0, start;

	dev_warn(&dd->pdev->dev,
		"FTL rebuild in progress. Polling for completion.\n");

	start = jiffies;
	timeout = jiffies + msecs_to_jiffies(MTIP_FTL_REBUILD_TIMEOUT_MS);

	do {
		if (unlikely(test_bit(MTIP_DDF_REMOVE_PENDING_BIT,
				&dd->dd_flag)))
			return -EFAULT;
		if (mtip_check_surprise_removal(dd->pdev))
			return -EFAULT;

		if (mtip_get_identify(dd->port, NULL) < 0)
			return -EFAULT;

		if (*(dd->port->identify + MTIP_FTL_REBUILD_OFFSET) ==
			MTIP_FTL_REBUILD_MAGIC) {
			ssleep(1);
			/* Print message every 3 minutes */
			if (cnt++ >= 180) {
				dev_warn(&dd->pdev->dev,
				"FTL rebuild in progress (%d secs).\n",
				jiffies_to_msecs(jiffies - start) / 1000);
				cnt = 0;
			}
		} else {
			dev_warn(&dd->pdev->dev,
				"FTL rebuild complete (%d secs).\n",
			jiffies_to_msecs(jiffies - start) / 1000);
			mtip_block_initialize(dd);
			return 0;
		}
		ssleep(10);
	} while (time_before(jiffies, timeout));

	/* Check for timeout */
	dev_err(&dd->pdev->dev,
		"Timed out waiting for FTL rebuild to complete (%d secs).\n",
		jiffies_to_msecs(jiffies - start) / 1000);
	return -EFAULT;
}