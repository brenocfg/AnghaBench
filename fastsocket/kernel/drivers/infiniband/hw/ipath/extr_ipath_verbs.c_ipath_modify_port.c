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
struct ipath_ibdev {scalar_t__ qkey_violations; int /*<<< orphan*/  dd; int /*<<< orphan*/  port_cap_flags; } ;
struct ib_port_modify {int /*<<< orphan*/  clr_port_cap_mask; int /*<<< orphan*/  set_port_cap_mask; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int IB_PORT_RESET_QKEY_CNTR ; 
 int IB_PORT_SHUTDOWN ; 
 int /*<<< orphan*/  IPATH_IB_LINKDOWN ; 
 int /*<<< orphan*/  ipath_set_linkstate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ipath_ibdev* to_idev (struct ib_device*) ; 

__attribute__((used)) static int ipath_modify_port(struct ib_device *ibdev,
			     u8 port, int port_modify_mask,
			     struct ib_port_modify *props)
{
	struct ipath_ibdev *dev = to_idev(ibdev);

	dev->port_cap_flags |= props->set_port_cap_mask;
	dev->port_cap_flags &= ~props->clr_port_cap_mask;
	if (port_modify_mask & IB_PORT_SHUTDOWN)
		ipath_set_linkstate(dev->dd, IPATH_IB_LINKDOWN);
	if (port_modify_mask & IB_PORT_RESET_QKEY_CNTR)
		dev->qkey_violations = 0;
	return 0;
}