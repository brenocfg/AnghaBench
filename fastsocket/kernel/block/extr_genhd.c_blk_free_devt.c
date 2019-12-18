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
typedef  scalar_t__ dev_t ;

/* Variables and functions */
 scalar_t__ BLOCK_EXT_MAJOR ; 
 scalar_t__ MAJOR (scalar_t__) ; 
 int /*<<< orphan*/  MINOR (scalar_t__) ; 
 scalar_t__ MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mangle_minor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext_devt_idr ; 
 int /*<<< orphan*/  ext_devt_mutex ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void blk_free_devt(dev_t devt)
{
	might_sleep();

	if (devt == MKDEV(0, 0))
		return;

	if (MAJOR(devt) == BLOCK_EXT_MAJOR) {
		mutex_lock(&ext_devt_mutex);
		idr_remove(&ext_devt_idr, blk_mangle_minor(MINOR(devt)));
		mutex_unlock(&ext_devt_mutex);
	}
}