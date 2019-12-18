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
struct vxge_vpath {int /*<<< orphan*/  handle; int /*<<< orphan*/  device_id; } ;
struct macInfo {int /*<<< orphan*/  macaddr; } ;
typedef  enum vxge_hw_status { ____Placeholder_vxge_hw_status } vxge_hw_status ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  VXGE_ERR ; 
 int VXGE_HW_OK ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  vxge_debug_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int vxge_hw_vpath_mac_addr_get (int /*<<< orphan*/ ,unsigned char*,unsigned char*) ; 
 int vxge_hw_vpath_mac_addr_get_next (int /*<<< orphan*/ ,unsigned char*,unsigned char*) ; 

__attribute__((used)) enum vxge_hw_status
static vxge_search_mac_addr_in_da_table(struct vxge_vpath *vpath,
					struct macInfo *mac)
{
	enum vxge_hw_status status = VXGE_HW_OK;
	unsigned char macmask[ETH_ALEN];
	unsigned char macaddr[ETH_ALEN];

	status = vxge_hw_vpath_mac_addr_get(vpath->handle,
				macaddr, macmask);
	if (status != VXGE_HW_OK) {
		vxge_debug_init(VXGE_ERR,
			"DA config list entry failed for vpath:%d",
			vpath->device_id);
		return status;
	}

	while (memcmp(mac->macaddr, macaddr, ETH_ALEN)) {

		status = vxge_hw_vpath_mac_addr_get_next(vpath->handle,
				macaddr, macmask);
		if (status != VXGE_HW_OK)
			break;
	}

	return status;
}