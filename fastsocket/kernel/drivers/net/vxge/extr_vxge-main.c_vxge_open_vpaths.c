#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_15__ {int /*<<< orphan*/  vpath_open_fail; int /*<<< orphan*/  vpaths_open; } ;
struct TYPE_13__ {int /*<<< orphan*/  gro_enable; int /*<<< orphan*/  fifo_indicate_max_pkts; int /*<<< orphan*/  tx_steering_type; } ;
struct vxgedev {int no_of_vpath; int /*<<< orphan*/  vpaths_deployed; TYPE_9__* vpaths; TYPE_7__* ndev; TYPE_6__ stats; int /*<<< orphan*/  vlan_tag_strip; TYPE_4__ config; scalar_t__* vp_handles; int /*<<< orphan*/  rx_csum; int /*<<< orphan*/  pdev; int /*<<< orphan*/  devh; } ;
struct vxge_tx_priv {int dummy; } ;
struct vxge_rx_priv {int dummy; } ;
struct TYPE_11__ {int per_rxd_space; void* userdata; int /*<<< orphan*/  rxd_term; int /*<<< orphan*/  rxd_init; int /*<<< orphan*/  callback; } ;
struct TYPE_10__ {int per_txdl_space; void* userdata; int /*<<< orphan*/  txdl_term; int /*<<< orphan*/  callback; } ;
struct vxge_hw_vpath_attr {TYPE_2__ ring_attr; TYPE_1__ fifo_attr; int /*<<< orphan*/  vp_id; } ;
struct __vxge_hw_vpath_handle {TYPE_8__* vpath; } ;
struct __vxge_hw_ring {int dummy; } ;
struct __vxge_hw_fifo {int dummy; } ;
typedef  enum vxge_hw_status { ____Placeholder_vxge_hw_status } vxge_hw_status ;
struct TYPE_14__ {int /*<<< orphan*/  vlan_tag_strip; int /*<<< orphan*/  gro_enable; int /*<<< orphan*/  rx_csum; scalar_t__ rx_vector_no; struct __vxge_hw_ring* handle; int /*<<< orphan*/  pdev; TYPE_7__* ndev; } ;
struct TYPE_12__ {int /*<<< orphan*/  indicate_max_pkts; int /*<<< orphan*/  pdev; TYPE_7__* ndev; int /*<<< orphan*/  tx_steering_type; struct __vxge_hw_fifo* handle; } ;
struct TYPE_18__ {int is_open; scalar_t__ handle; int /*<<< orphan*/  device_id; TYPE_5__ ring; TYPE_3__ fifo; int /*<<< orphan*/  is_configured; } ;
struct TYPE_17__ {int /*<<< orphan*/  vp_id; } ;
struct TYPE_16__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  VXGE_ERR ; 
 int VXGE_HW_OK ; 
 int /*<<< orphan*/  vxge_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxge_close_vpaths (struct vxgedev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxge_debug_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int vxge_hw_vpath_open (int /*<<< orphan*/ ,struct vxge_hw_vpath_attr*,scalar_t__*) ; 
 int /*<<< orphan*/  vxge_mBIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxge_rx_1b_compl ; 
 int /*<<< orphan*/  vxge_rx_initial_replenish ; 
 int /*<<< orphan*/  vxge_rx_term ; 
 int /*<<< orphan*/  vxge_tx_term ; 
 int /*<<< orphan*/  vxge_xmit_compl ; 

int vxge_open_vpaths(struct vxgedev *vdev)
{
	enum vxge_hw_status status;
	int i;
	u32 vp_id = 0;
	struct vxge_hw_vpath_attr attr;

	for (i = 0; i < vdev->no_of_vpath; i++) {
		vxge_assert(vdev->vpaths[i].is_configured);
		attr.vp_id = vdev->vpaths[i].device_id;
		attr.fifo_attr.callback = vxge_xmit_compl;
		attr.fifo_attr.txdl_term = vxge_tx_term;
		attr.fifo_attr.per_txdl_space = sizeof(struct vxge_tx_priv);
		attr.fifo_attr.userdata = (void *)&vdev->vpaths[i].fifo;

		attr.ring_attr.callback = vxge_rx_1b_compl;
		attr.ring_attr.rxd_init = vxge_rx_initial_replenish;
		attr.ring_attr.rxd_term = vxge_rx_term;
		attr.ring_attr.per_rxd_space = sizeof(struct vxge_rx_priv);
		attr.ring_attr.userdata = (void *)&vdev->vpaths[i].ring;

		vdev->vpaths[i].ring.ndev = vdev->ndev;
		vdev->vpaths[i].ring.pdev = vdev->pdev;
		status = vxge_hw_vpath_open(vdev->devh, &attr,
				&(vdev->vpaths[i].handle));
		if (status == VXGE_HW_OK) {
			vdev->vpaths[i].fifo.handle =
			    (struct __vxge_hw_fifo *)attr.fifo_attr.userdata;
			vdev->vpaths[i].ring.handle =
			    (struct __vxge_hw_ring *)attr.ring_attr.userdata;
			vdev->vpaths[i].fifo.tx_steering_type =
				vdev->config.tx_steering_type;
			vdev->vpaths[i].fifo.ndev = vdev->ndev;
			vdev->vpaths[i].fifo.pdev = vdev->pdev;
			vdev->vpaths[i].fifo.indicate_max_pkts =
				vdev->config.fifo_indicate_max_pkts;
			vdev->vpaths[i].ring.rx_vector_no = 0;
			vdev->vpaths[i].ring.rx_csum = vdev->rx_csum;
			vdev->vpaths[i].is_open = 1;
			vdev->vp_handles[i] = vdev->vpaths[i].handle;
			vdev->vpaths[i].ring.gro_enable =
						vdev->config.gro_enable;
			vdev->vpaths[i].ring.vlan_tag_strip =
						vdev->vlan_tag_strip;
			vdev->stats.vpaths_open++;
		} else {
			vdev->stats.vpath_open_fail++;
			vxge_debug_init(VXGE_ERR,
				"%s: vpath: %d failed to open "
				"with status: %d",
			    vdev->ndev->name, vdev->vpaths[i].device_id,
				status);
			vxge_close_vpaths(vdev, 0);
			return -EPERM;
		}

		vp_id =
		  ((struct __vxge_hw_vpath_handle *)vdev->vpaths[i].handle)->
		  vpath->vp_id;
		vdev->vpaths_deployed |= vxge_mBIT(vp_id);
	}
	return VXGE_HW_OK;
}