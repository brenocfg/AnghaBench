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
struct radeon_device {unsigned int debugfs_count; TYPE_1__* ddev; TYPE_2__* debugfs; } ;
struct TYPE_4__ {int /*<<< orphan*/  num_files; int /*<<< orphan*/  files; } ;
struct TYPE_3__ {int /*<<< orphan*/  primary; int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_debugfs_remove_files (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void radeon_debugfs_remove_files(struct radeon_device *rdev)
{
#if defined(CONFIG_DEBUG_FS)
	unsigned i;

	for (i = 0; i < rdev->debugfs_count; i++) {
		drm_debugfs_remove_files(rdev->debugfs[i].files,
					 rdev->debugfs[i].num_files,
					 rdev->ddev->control);
		drm_debugfs_remove_files(rdev->debugfs[i].files,
					 rdev->debugfs[i].num_files,
					 rdev->ddev->primary);
	}
#endif
}