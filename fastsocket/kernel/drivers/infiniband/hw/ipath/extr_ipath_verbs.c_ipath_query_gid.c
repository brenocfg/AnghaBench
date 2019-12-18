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
struct TYPE_3__ {int /*<<< orphan*/  interface_id; int /*<<< orphan*/  subnet_prefix; } ;
union ib_gid {TYPE_1__ global; } ;
typedef  int /*<<< orphan*/  u8 ;
struct ipath_ibdev {TYPE_2__* dd; int /*<<< orphan*/  gid_prefix; } ;
struct ib_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ipath_guid; } ;

/* Variables and functions */
 int EINVAL ; 
 struct ipath_ibdev* to_idev (struct ib_device*) ; 

__attribute__((used)) static int ipath_query_gid(struct ib_device *ibdev, u8 port,
			   int index, union ib_gid *gid)
{
	struct ipath_ibdev *dev = to_idev(ibdev);
	int ret;

	if (index >= 1) {
		ret = -EINVAL;
		goto bail;
	}
	gid->global.subnet_prefix = dev->gid_prefix;
	gid->global.interface_id = dev->dd->ipath_guid;

	ret = 0;

bail:
	return ret;
}