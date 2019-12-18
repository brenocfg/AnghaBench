#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct mlx4_ib_dev {TYPE_6__* dev; } ;
struct ib_wc {int wc_flags; TYPE_5__* qp; } ;
struct ib_sa_mad {int dummy; } ;
struct TYPE_9__ {int method; int mgmt_class; int /*<<< orphan*/  tid; } ;
struct ib_mad {TYPE_3__ mad_hdr; } ;
struct TYPE_7__ {int /*<<< orphan*/  interface_id; } ;
struct TYPE_8__ {TYPE_1__ global; } ;
struct ib_grh {TYPE_2__ dgid; } ;
struct ib_device {int dummy; } ;
struct TYPE_10__ {int sqp_demux; } ;
struct TYPE_12__ {TYPE_4__ caps; } ;
struct TYPE_11__ {int /*<<< orphan*/  qp_type; } ;

/* Variables and functions */
 int ENOENT ; 
#define  IB_MGMT_CLASS_CM 130 
#define  IB_MGMT_CLASS_DEVICE_MGMT 129 
#define  IB_MGMT_CLASS_SUBN_ADM 128 
 int IB_MGMT_METHOD_GET_RESP ; 
 int IB_WC_GRH ; 
 int /*<<< orphan*/  mlx4_ib_demux_cm_handler (struct ib_device*,int,int*,struct ib_mad*) ; 
 int /*<<< orphan*/  mlx4_ib_demux_sa_handler (struct ib_device*,int,int,struct ib_sa_mad*) ; 
 int mlx4_ib_find_real_gid (struct ib_device*,int,int /*<<< orphan*/ ) ; 
 int mlx4_ib_send_to_slave (struct mlx4_ib_dev*,int,int,int /*<<< orphan*/ ,struct ib_wc*,struct ib_grh*,struct ib_mad*) ; 
 int /*<<< orphan*/  mlx4_ib_warn (struct ib_device*,char*,...) ; 
 int mlx4_master_func_num (TYPE_6__*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 
 struct mlx4_ib_dev* to_mdev (struct ib_device*) ; 

__attribute__((used)) static int mlx4_ib_demux_mad(struct ib_device *ibdev, u8 port,
			struct ib_wc *wc, struct ib_grh *grh,
			struct ib_mad *mad)
{
	struct mlx4_ib_dev *dev = to_mdev(ibdev);
	int err;
	int slave;
	u8 *slave_id;

	/* Initially assume that this mad is for us */
	slave = mlx4_master_func_num(dev->dev);

	/* See if the slave id is encoded in a response mad */
	if (mad->mad_hdr.method & 0x80) {
		slave_id = (u8 *) &mad->mad_hdr.tid;
		slave = *slave_id;
		if (slave != 255) /*255 indicates the dom0*/
			*slave_id = 0; /* remap tid */
	}

	/* If a grh is present, we demux according to it */
	if (wc->wc_flags & IB_WC_GRH) {
		slave = mlx4_ib_find_real_gid(ibdev, port, grh->dgid.global.interface_id);
		if (slave < 0) {
			mlx4_ib_warn(ibdev, "failed matching grh\n");
			return -ENOENT;
		}
	}
	/* Class-specific handling */
	switch (mad->mad_hdr.mgmt_class) {
	case IB_MGMT_CLASS_SUBN_ADM:
		if (mlx4_ib_demux_sa_handler(ibdev, port, slave,
					     (struct ib_sa_mad *) mad))
			return 0;
		break;
	case IB_MGMT_CLASS_CM:
		if (mlx4_ib_demux_cm_handler(ibdev, port, &slave, mad))
			return 0;
		break;
	case IB_MGMT_CLASS_DEVICE_MGMT:
		if (mad->mad_hdr.method != IB_MGMT_METHOD_GET_RESP)
			return 0;
		break;
	default:
		/* Drop unsupported classes for slaves in tunnel mode */
		if (slave != mlx4_master_func_num(dev->dev)) {
			pr_debug("dropping unsupported ingress mad from class:%d "
				 "for slave:%d\n", mad->mad_hdr.mgmt_class, slave);
			return 0;
		}
	}
	/*make sure that no slave==255 was not handled yet.*/
	if (slave >= dev->dev->caps.sqp_demux) {
		mlx4_ib_warn(ibdev, "slave id: %d is bigger than allowed:%d\n",
			     slave, dev->dev->caps.sqp_demux);
		return -ENOENT;
	}

	err = mlx4_ib_send_to_slave(dev, slave, port, wc->qp->qp_type, wc, grh, mad);
	if (err)
		pr_debug("failed sending to slave %d via tunnel qp (%d)\n",
			 slave, err);
	return 0;
}