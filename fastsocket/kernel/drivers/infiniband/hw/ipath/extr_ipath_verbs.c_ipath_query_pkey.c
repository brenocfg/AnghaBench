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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct ipath_ibdev {int /*<<< orphan*/  dd; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ipath_get_npkeys (int /*<<< orphan*/ ) ; 
 scalar_t__ ipath_get_pkey (int /*<<< orphan*/ ,scalar_t__) ; 
 struct ipath_ibdev* to_idev (struct ib_device*) ; 

__attribute__((used)) static int ipath_query_pkey(struct ib_device *ibdev, u8 port, u16 index,
			    u16 *pkey)
{
	struct ipath_ibdev *dev = to_idev(ibdev);
	int ret;

	if (index >= ipath_get_npkeys(dev->dd)) {
		ret = -EINVAL;
		goto bail;
	}

	*pkey = ipath_get_pkey(dev->dd, index);
	ret = 0;

bail:
	return ret;
}