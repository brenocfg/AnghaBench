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
typedef  int u64 ;
struct __vxge_hw_vpath_handle {struct __vxge_hw_virtualpath* vpath; } ;
struct __vxge_hw_virtualpath {TYPE_2__* vp_reg; TYPE_1__* hldev; int /*<<< orphan*/ * ringh; } ;
typedef  enum vxge_hw_status { ____Placeholder_vxge_hw_status } vxge_hw_status ;
struct TYPE_4__ {int /*<<< orphan*/  rxmac_vcfg0; } ;
struct TYPE_3__ {int access_rights; } ;

/* Variables and functions */
 int VXGE_HW_DEVICE_ACCESS_RIGHT_MRPCIM ; 
 int VXGE_HW_ERR_INVALID_HANDLE ; 
 int VXGE_HW_OK ; 
 int VXGE_HW_RXMAC_VCFG0_ALL_VID_EN ; 
 int VXGE_HW_RXMAC_VCFG0_BCAST_EN ; 
 int VXGE_HW_RXMAC_VCFG0_MCAST_ALL_ADDR_EN ; 
 int VXGE_HW_RXMAC_VCFG0_UCAST_ALL_ADDR_EN ; 
 int readq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeq (int,int /*<<< orphan*/ *) ; 

enum vxge_hw_status vxge_hw_vpath_promisc_enable(
			struct __vxge_hw_vpath_handle *vp)
{
	u64 val64;
	struct __vxge_hw_virtualpath *vpath;
	enum vxge_hw_status status = VXGE_HW_OK;

	if ((vp == NULL) || (vp->vpath->ringh == NULL)) {
		status = VXGE_HW_ERR_INVALID_HANDLE;
		goto exit;
	}

	vpath = vp->vpath;

	/* Enable promiscous mode for function 0 only */
	if (!(vpath->hldev->access_rights &
		VXGE_HW_DEVICE_ACCESS_RIGHT_MRPCIM))
		return VXGE_HW_OK;

	val64 = readq(&vpath->vp_reg->rxmac_vcfg0);

	if (!(val64 & VXGE_HW_RXMAC_VCFG0_UCAST_ALL_ADDR_EN)) {

		val64 |= VXGE_HW_RXMAC_VCFG0_UCAST_ALL_ADDR_EN |
			 VXGE_HW_RXMAC_VCFG0_MCAST_ALL_ADDR_EN |
			 VXGE_HW_RXMAC_VCFG0_BCAST_EN |
			 VXGE_HW_RXMAC_VCFG0_ALL_VID_EN;

		writeq(val64, &vpath->vp_reg->rxmac_vcfg0);
	}
exit:
	return status;
}