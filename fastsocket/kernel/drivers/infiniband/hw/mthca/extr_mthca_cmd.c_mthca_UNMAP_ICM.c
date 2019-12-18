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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct mthca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_TIME_CLASS_B ; 
 int /*<<< orphan*/  CMD_UNMAP_ICM ; 
 int mthca_cmd (struct mthca_dev*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_dbg (struct mthca_dev*,char*,int /*<<< orphan*/ ,unsigned long long) ; 

int mthca_UNMAP_ICM(struct mthca_dev *dev, u64 virt, u32 page_count)
{
	mthca_dbg(dev, "Unmapping %d pages at %llx from ICM.\n",
		  page_count, (unsigned long long) virt);

	return mthca_cmd(dev, virt, page_count, 0,
			CMD_UNMAP_ICM, CMD_TIME_CLASS_B);
}