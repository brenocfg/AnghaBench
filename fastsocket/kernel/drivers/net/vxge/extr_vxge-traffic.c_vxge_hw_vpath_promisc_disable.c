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
typedef  int u64 ;
struct __vxge_hw_vpath_handle {struct __vxge_hw_virtualpath* vpath; } ;
struct __vxge_hw_virtualpath {TYPE_1__* vp_reg; int /*<<< orphan*/ * ringh; } ;
typedef  enum vxge_hw_status { ____Placeholder_vxge_hw_status } vxge_hw_status ;
struct TYPE_2__ {int /*<<< orphan*/  rxmac_vcfg0; } ;

/* Variables and functions */
 int VXGE_HW_ERR_INVALID_HANDLE ; 
 int VXGE_HW_OK ; 
 int VXGE_HW_RXMAC_VCFG0_ALL_VID_EN ; 
 int VXGE_HW_RXMAC_VCFG0_MCAST_ALL_ADDR_EN ; 
 int VXGE_HW_RXMAC_VCFG0_UCAST_ALL_ADDR_EN ; 
 int readq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeq (int,int /*<<< orphan*/ *) ; 

enum vxge_hw_status vxge_hw_vpath_promisc_disable(
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

	val64 = readq(&vpath->vp_reg->rxmac_vcfg0);

	if (val64 & VXGE_HW_RXMAC_VCFG0_UCAST_ALL_ADDR_EN) {

		val64 &= ~(VXGE_HW_RXMAC_VCFG0_UCAST_ALL_ADDR_EN |
			   VXGE_HW_RXMAC_VCFG0_MCAST_ALL_ADDR_EN |
			   VXGE_HW_RXMAC_VCFG0_ALL_VID_EN);

		writeq(val64, &vpath->vp_reg->rxmac_vcfg0);
	}
exit:
	return status;
}