#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
typedef  void* u32 ;
typedef  size_t u16 ;
struct mlx4_mad_snd_buf {int /*<<< orphan*/  payload; } ;
struct TYPE_15__ {size_t*** virt2phys_pkey; } ;
struct TYPE_14__ {struct mlx4_ib_demux_pv_ctx** sqps; } ;
struct mlx4_ib_dev {int /*<<< orphan*/  ib_dev; TYPE_2__ pkeys; int /*<<< orphan*/  dev; TYPE_1__ sriov; } ;
struct mlx4_ib_demux_pv_qp {int tx_ix_head; int tx_ix_tail; TYPE_7__* tx_ring; int /*<<< orphan*/  tx_lock; struct ib_qp* qp; } ;
struct mlx4_ib_demux_pv_ctx {scalar_t__ state; TYPE_8__* mr; int /*<<< orphan*/  pd; struct mlx4_ib_demux_pv_qp* qp; } ;
struct ib_sge {int length; int /*<<< orphan*/  lkey; int /*<<< orphan*/  addr; } ;
struct TYPE_22__ {int port_num; size_t pkey_index; void* remote_qpn; void* remote_qkey; struct ib_ah* ah; } ;
struct TYPE_12__ {TYPE_9__ ud; } ;
struct ib_send_wr {int wr_id; int num_sge; int /*<<< orphan*/  send_flags; int /*<<< orphan*/  opcode; struct ib_sge* sg_list; int /*<<< orphan*/ * next; TYPE_10__ wr; } ;
struct ib_qp {int dummy; } ;
struct ib_mad {int dummy; } ;
struct TYPE_16__ {int sgid_index; } ;
struct ib_ah_attr {TYPE_3__ grh; } ;
struct ib_ah {int dummy; } ;
typedef  enum ib_qp_type { ____Placeholder_ib_qp_type } ib_qp_type ;
struct TYPE_21__ {int /*<<< orphan*/  lkey; } ;
struct TYPE_19__ {int /*<<< orphan*/  map; scalar_t__ addr; } ;
struct TYPE_20__ {TYPE_6__ buf; struct ib_ah* ah; } ;
struct TYPE_17__ {int gid_index; int /*<<< orphan*/  port_pd; } ;
struct TYPE_18__ {TYPE_4__ ib; } ;
struct TYPE_13__ {TYPE_5__ av; } ;

/* Variables and functions */
 scalar_t__ DEMUX_PV_STATE_ACTIVE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int IB_QPT_SMI ; 
 int /*<<< orphan*/  IB_SEND_SIGNALED ; 
 int /*<<< orphan*/  IB_WR_SEND ; 
 scalar_t__ IS_ERR (struct ib_ah*) ; 
 int MLX4_NUM_TUNNEL_BUFS ; 
 int MLX4_TUN_SET_WRID_QPN (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 struct ib_ah* ib_create_ah (int /*<<< orphan*/ ,struct ib_ah_attr*) ; 
 int /*<<< orphan*/  ib_destroy_ah (struct ib_ah*) ; 
 int /*<<< orphan*/  ib_dma_sync_single_for_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_sync_single_for_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ib_post_send (struct ib_qp*,struct ib_send_wr*,struct ib_send_wr**) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ib_mad*,int) ; 
 int mlx4_master_func_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_11__* to_mah (struct ib_ah*) ; 

int mlx4_ib_send_to_wire(struct mlx4_ib_dev *dev, int slave, u8 port,
			 enum ib_qp_type dest_qpt, u16 pkey_index, u32 remote_qpn,
			 u32 qkey, struct ib_ah_attr *attr, struct ib_mad *mad)
{
	struct ib_sge list;
	struct ib_send_wr wr, *bad_wr;
	struct mlx4_ib_demux_pv_ctx *sqp_ctx;
	struct mlx4_ib_demux_pv_qp *sqp;
	struct mlx4_mad_snd_buf *sqp_mad;
	struct ib_ah *ah;
	struct ib_qp *send_qp = NULL;
	unsigned wire_tx_ix = 0;
	int ret = 0;
	u16 wire_pkey_ix;
	int src_qpnum;
	u8 sgid_index;


	sqp_ctx = dev->sriov.sqps[port-1];

	/* check if proxy qp created */
	if (!sqp_ctx || sqp_ctx->state != DEMUX_PV_STATE_ACTIVE)
		return -EAGAIN;

	/* QP0 forwarding only for Dom0 */
	if (dest_qpt == IB_QPT_SMI && (mlx4_master_func_num(dev->dev) != slave))
		return -EINVAL;

	if (dest_qpt == IB_QPT_SMI) {
		src_qpnum = 0;
		sqp = &sqp_ctx->qp[0];
		wire_pkey_ix = dev->pkeys.virt2phys_pkey[slave][port - 1][0];
	} else {
		src_qpnum = 1;
		sqp = &sqp_ctx->qp[1];
		wire_pkey_ix = dev->pkeys.virt2phys_pkey[slave][port - 1][pkey_index];
	}

	send_qp = sqp->qp;

	/* create ah */
	sgid_index = attr->grh.sgid_index;
	attr->grh.sgid_index = 0;
	ah = ib_create_ah(sqp_ctx->pd, attr);
	if (IS_ERR(ah))
		return -ENOMEM;
	attr->grh.sgid_index = sgid_index;
	to_mah(ah)->av.ib.gid_index = sgid_index;
	/* get rid of force-loopback bit */
	to_mah(ah)->av.ib.port_pd &= cpu_to_be32(0x7FFFFFFF);
	spin_lock(&sqp->tx_lock);
	if (sqp->tx_ix_head - sqp->tx_ix_tail >=
	    (MLX4_NUM_TUNNEL_BUFS - 1))
		ret = -EAGAIN;
	else
		wire_tx_ix = (++sqp->tx_ix_head) & (MLX4_NUM_TUNNEL_BUFS - 1);
	spin_unlock(&sqp->tx_lock);
	if (ret)
		goto out;

	sqp_mad = (struct mlx4_mad_snd_buf *) (sqp->tx_ring[wire_tx_ix].buf.addr);
	if (sqp->tx_ring[wire_tx_ix].ah)
		ib_destroy_ah(sqp->tx_ring[wire_tx_ix].ah);
	sqp->tx_ring[wire_tx_ix].ah = ah;
	ib_dma_sync_single_for_cpu(&dev->ib_dev,
				   sqp->tx_ring[wire_tx_ix].buf.map,
				   sizeof (struct mlx4_mad_snd_buf),
				   DMA_TO_DEVICE);

	memcpy(&sqp_mad->payload, mad, sizeof *mad);

	ib_dma_sync_single_for_device(&dev->ib_dev,
				      sqp->tx_ring[wire_tx_ix].buf.map,
				      sizeof (struct mlx4_mad_snd_buf),
				      DMA_TO_DEVICE);

	list.addr = sqp->tx_ring[wire_tx_ix].buf.map;
	list.length = sizeof (struct mlx4_mad_snd_buf);
	list.lkey = sqp_ctx->mr->lkey;

	wr.wr.ud.ah = ah;
	wr.wr.ud.port_num = port;
	wr.wr.ud.pkey_index = wire_pkey_ix;
	wr.wr.ud.remote_qkey = qkey;
	wr.wr.ud.remote_qpn = remote_qpn;
	wr.next = NULL;
	wr.wr_id = ((u64) wire_tx_ix) | MLX4_TUN_SET_WRID_QPN(src_qpnum);
	wr.sg_list = &list;
	wr.num_sge = 1;
	wr.opcode = IB_WR_SEND;
	wr.send_flags = IB_SEND_SIGNALED;

	ret = ib_post_send(send_qp, &wr, &bad_wr);
out:
	if (ret)
		ib_destroy_ah(ah);
	return ret;
}