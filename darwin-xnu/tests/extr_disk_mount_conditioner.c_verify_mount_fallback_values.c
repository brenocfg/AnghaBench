#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  segwritecnt; int /*<<< orphan*/  segreadcnt; int /*<<< orphan*/  maxwritecnt; int /*<<< orphan*/  maxreadcnt; int /*<<< orphan*/  ioqueue_depth; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ disk_conditioner_info ;

/* Variables and functions */
 int /*<<< orphan*/  DISK_CONDITIONER_IOC_GET ; 
 int /*<<< orphan*/  DISK_CONDITIONER_IOC_SET ; 
 int /*<<< orphan*/  T_ASSERT_EQ_INT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  T_ASSERT_GT (int /*<<< orphan*/ ,unsigned int,char*) ; 
 int /*<<< orphan*/  T_ASSERT_LT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_WITH_ERRNO ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int fsctl (char const*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
verify_mount_fallback_values(const char *mount_path, disk_conditioner_info *info)
{
	int err;
	disk_conditioner_info newinfo = {0};

	err = fsctl(mount_path, DISK_CONDITIONER_IOC_SET, info, 0);
	T_WITH_ERRNO;
	T_ASSERT_EQ_INT(0, err, "fsctl(DISK_CONDITIONER_IOC_SET)");

	err = fsctl(mount_path, DISK_CONDITIONER_IOC_GET, &newinfo, 0);
	T_WITH_ERRNO;
	T_ASSERT_EQ_INT(0, err, "fsctl(DISK_CONDITIONER_IOC_GET) after SET");

	// without querying the drive for the expected values, the best we can do is
	// assert that they are not zero (impossible) or less than UINT32_MAX (unlikely)
	T_ASSERT_GT(newinfo.ioqueue_depth, 0u, "ioqueue_depth is the value from the mount");
	T_ASSERT_GT(newinfo.maxreadcnt, 0u, "maxreadcnt is value from the mount");
	T_ASSERT_GT(newinfo.maxwritecnt, 0u, "maxwritecnt is value from the mount");
	T_ASSERT_GT(newinfo.segreadcnt, 0u, "segreadcnt is value from the mount");
	T_ASSERT_GT(newinfo.segwritecnt, 0u, "segwritecnt is value from the mount");
	T_ASSERT_LT(newinfo.ioqueue_depth, UINT32_MAX, "ioqueue_depth is the value from the mount");
	T_ASSERT_LT(newinfo.maxreadcnt, UINT32_MAX, "maxreadcnt is value from the mount");
	T_ASSERT_LT(newinfo.maxwritecnt, UINT32_MAX, "maxwritecnt is value from the mount");
	T_ASSERT_LT(newinfo.segreadcnt, UINT32_MAX, "segreadcnt is value from the mount");
	T_ASSERT_LT(newinfo.segwritecnt, UINT32_MAX, "segwritecnt is value from the mount");
}