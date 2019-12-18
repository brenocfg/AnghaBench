#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_24__ {void* length; void* remote_to; void* remote_stag; void* local_to; void* local_stag; } ;
struct TYPE_21__ {void* sge_len; int /*<<< orphan*/  data; void* remote_to; void* remote_stag; } ;
struct TYPE_20__ {void* sge_len; int /*<<< orphan*/  data; void* remote_stag; } ;
struct TYPE_16__ {int /*<<< orphan*/  context; } ;
struct TYPE_17__ {TYPE_1__ hdr; } ;
struct TYPE_18__ {TYPE_2__ user_hdr; } ;
struct TYPE_13__ {TYPE_9__ rdma_read; TYPE_6__ rdma_write; TYPE_5__ send; TYPE_3__ sq_hdr; } ;
union c2wr {TYPE_10__ sqwr; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_22__ {int rkey; int /*<<< orphan*/  remote_addr; } ;
struct TYPE_23__ {TYPE_7__ rdma; } ;
struct TYPE_19__ {int invalidate_rkey; } ;
struct ib_send_wr {int send_flags; int opcode; int num_sge; struct ib_send_wr* next; TYPE_12__* sg_list; TYPE_8__ wr; TYPE_4__ ex; int /*<<< orphan*/  wr_id; } ;
struct ib_qp {int /*<<< orphan*/  device; } ;
struct c2wr_send_req {int dummy; } ;
struct c2wr_rdma_write_req {int dummy; } ;
struct c2wr_rdma_read_req {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  hint_count; int /*<<< orphan*/  index; } ;
struct c2_qp {scalar_t__ state; int send_sgl_depth; int rdma_write_sgl_depth; int /*<<< orphan*/  lock; TYPE_11__ sq_mq; } ;
struct c2_dev {int dummy; } ;
struct c2_data_addr {int dummy; } ;
struct TYPE_15__ {int lkey; int length; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  C2_WR_TYPE_RDMA_READ ; 
 int /*<<< orphan*/  C2_WR_TYPE_RDMA_WRITE ; 
 int /*<<< orphan*/  C2_WR_TYPE_SEND ; 
 int /*<<< orphan*/  C2_WR_TYPE_SEND_INV ; 
 int /*<<< orphan*/  C2_WR_TYPE_SEND_SE ; 
 int /*<<< orphan*/  C2_WR_TYPE_SEND_SE_INV ; 
 int EINVAL ; 
 scalar_t__ IB_QPS_RTS ; 
 int IB_SEND_FENCE ; 
 int IB_SEND_SIGNALED ; 
 int IB_SEND_SOLICITED ; 
#define  IB_WR_RDMA_READ 131 
#define  IB_WR_RDMA_WRITE 130 
#define  IB_WR_SEND 129 
#define  IB_WR_SEND_WITH_INV 128 
 int SQ_READ_FENCE ; 
 int SQ_SIGNALED ; 
 int /*<<< orphan*/  c2_activity (struct c2_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c2_wr_set_flags (union c2wr*,int) ; 
 int /*<<< orphan*/  c2_wr_set_id (union c2wr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c2_wr_set_sge_count (union c2wr*,int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int move_sgl (struct c2_data_addr*,TYPE_12__*,int,int*,int /*<<< orphan*/ *) ; 
 int qp_wr_post (TYPE_11__*,union c2wr*,struct c2_qp*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct c2_dev* to_c2dev (int /*<<< orphan*/ ) ; 
 struct c2_qp* to_c2qp (struct ib_qp*) ; 

int c2_post_send(struct ib_qp *ibqp, struct ib_send_wr *ib_wr,
		 struct ib_send_wr **bad_wr)
{
	struct c2_dev *c2dev = to_c2dev(ibqp->device);
	struct c2_qp *qp = to_c2qp(ibqp);
	union c2wr wr;
	unsigned long lock_flags;
	int err = 0;

	u32 flags;
	u32 tot_len;
	u8 actual_sge_count;
	u32 msg_size;

	if (qp->state > IB_QPS_RTS) {
		err = -EINVAL;
		goto out;
	}

	while (ib_wr) {

		flags = 0;
		wr.sqwr.sq_hdr.user_hdr.hdr.context = ib_wr->wr_id;
		if (ib_wr->send_flags & IB_SEND_SIGNALED) {
			flags |= SQ_SIGNALED;
		}

		switch (ib_wr->opcode) {
		case IB_WR_SEND:
		case IB_WR_SEND_WITH_INV:
			if (ib_wr->opcode == IB_WR_SEND) {
				if (ib_wr->send_flags & IB_SEND_SOLICITED)
					c2_wr_set_id(&wr, C2_WR_TYPE_SEND_SE);
				else
					c2_wr_set_id(&wr, C2_WR_TYPE_SEND);
				wr.sqwr.send.remote_stag = 0;
			} else {
				if (ib_wr->send_flags & IB_SEND_SOLICITED)
					c2_wr_set_id(&wr, C2_WR_TYPE_SEND_SE_INV);
				else
					c2_wr_set_id(&wr, C2_WR_TYPE_SEND_INV);
				wr.sqwr.send.remote_stag =
					cpu_to_be32(ib_wr->ex.invalidate_rkey);
			}

			msg_size = sizeof(struct c2wr_send_req) +
				sizeof(struct c2_data_addr) * ib_wr->num_sge;
			if (ib_wr->num_sge > qp->send_sgl_depth) {
				err = -EINVAL;
				break;
			}
			if (ib_wr->send_flags & IB_SEND_FENCE) {
				flags |= SQ_READ_FENCE;
			}
			err = move_sgl((struct c2_data_addr *) & (wr.sqwr.send.data),
				       ib_wr->sg_list,
				       ib_wr->num_sge,
				       &tot_len, &actual_sge_count);
			wr.sqwr.send.sge_len = cpu_to_be32(tot_len);
			c2_wr_set_sge_count(&wr, actual_sge_count);
			break;
		case IB_WR_RDMA_WRITE:
			c2_wr_set_id(&wr, C2_WR_TYPE_RDMA_WRITE);
			msg_size = sizeof(struct c2wr_rdma_write_req) +
			    (sizeof(struct c2_data_addr) * ib_wr->num_sge);
			if (ib_wr->num_sge > qp->rdma_write_sgl_depth) {
				err = -EINVAL;
				break;
			}
			if (ib_wr->send_flags & IB_SEND_FENCE) {
				flags |= SQ_READ_FENCE;
			}
			wr.sqwr.rdma_write.remote_stag =
			    cpu_to_be32(ib_wr->wr.rdma.rkey);
			wr.sqwr.rdma_write.remote_to =
			    cpu_to_be64(ib_wr->wr.rdma.remote_addr);
			err = move_sgl((struct c2_data_addr *)
				       & (wr.sqwr.rdma_write.data),
				       ib_wr->sg_list,
				       ib_wr->num_sge,
				       &tot_len, &actual_sge_count);
			wr.sqwr.rdma_write.sge_len = cpu_to_be32(tot_len);
			c2_wr_set_sge_count(&wr, actual_sge_count);
			break;
		case IB_WR_RDMA_READ:
			c2_wr_set_id(&wr, C2_WR_TYPE_RDMA_READ);
			msg_size = sizeof(struct c2wr_rdma_read_req);

			/* IWarp only suppots 1 sge for RDMA reads */
			if (ib_wr->num_sge > 1) {
				err = -EINVAL;
				break;
			}

			/*
			 * Move the local and remote stag/to/len into the WR.
			 */
			wr.sqwr.rdma_read.local_stag =
			    cpu_to_be32(ib_wr->sg_list->lkey);
			wr.sqwr.rdma_read.local_to =
			    cpu_to_be64(ib_wr->sg_list->addr);
			wr.sqwr.rdma_read.remote_stag =
			    cpu_to_be32(ib_wr->wr.rdma.rkey);
			wr.sqwr.rdma_read.remote_to =
			    cpu_to_be64(ib_wr->wr.rdma.remote_addr);
			wr.sqwr.rdma_read.length =
			    cpu_to_be32(ib_wr->sg_list->length);
			break;
		default:
			/* error */
			msg_size = 0;
			err = -EINVAL;
			break;
		}

		/*
		 * If we had an error on the last wr build, then
		 * break out.  Possible errors include bogus WR
		 * type, and a bogus SGL length...
		 */
		if (err) {
			break;
		}

		/*
		 * Store flags
		 */
		c2_wr_set_flags(&wr, flags);

		/*
		 * Post the puppy!
		 */
		spin_lock_irqsave(&qp->lock, lock_flags);
		err = qp_wr_post(&qp->sq_mq, &wr, qp, msg_size);
		if (err) {
			spin_unlock_irqrestore(&qp->lock, lock_flags);
			break;
		}

		/*
		 * Enqueue mq index to activity FIFO.
		 */
		c2_activity(c2dev, qp->sq_mq.index, qp->sq_mq.hint_count);
		spin_unlock_irqrestore(&qp->lock, lock_flags);

		ib_wr = ib_wr->next;
	}

out:
	if (err)
		*bad_wr = ib_wr;
	return err;
}