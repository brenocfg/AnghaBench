#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct ixgbe_adapter {TYPE_1__* vfinfo; } ;
struct TYPE_2__ {int vf_api; } ;

/* Variables and functions */
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  e_info (int /*<<< orphan*/ ,char*,size_t,int) ; 
#define  ixgbe_mbox_api_10 129 
#define  ixgbe_mbox_api_11 128 

__attribute__((used)) static int ixgbe_negotiate_vf_api(struct ixgbe_adapter *adapter,
				  u32 *msgbuf, u32 vf)
{
	int api = msgbuf[1];

	switch (api) {
	case ixgbe_mbox_api_10:
	case ixgbe_mbox_api_11:
		adapter->vfinfo[vf].vf_api = api;
		return 0;
	default:
		break;
	}

	e_info(drv, "VF %d requested invalid api version %u\n", vf, api);

	return -1;
}