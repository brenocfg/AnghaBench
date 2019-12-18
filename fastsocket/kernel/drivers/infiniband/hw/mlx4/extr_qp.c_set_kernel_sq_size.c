#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mlx4_wqe_inline_seg {int dummy; } ;
struct mlx4_wqe_data_seg {int dummy; } ;
struct TYPE_6__ {unsigned int wqe_shift; int wqe_cnt; int max_gs; int offset; int max_post; } ;
struct TYPE_5__ {int wqe_cnt; int wqe_shift; int offset; } ;
struct mlx4_ib_qp {int sq_max_wqes_per_wr; int sq_spare_wqes; int buf_size; TYPE_2__ sq; TYPE_1__ rq; int /*<<< orphan*/  flags; scalar_t__ sq_signal_bits; } ;
struct mlx4_ib_dev {TYPE_4__* dev; } ;
struct ib_qp_cap {int max_send_wr; int max_send_sge; int max_inline_data; } ;
typedef  enum mlx4_ib_qp_type { ____Placeholder_mlx4_ib_qp_type } mlx4_ib_qp_type ;
struct TYPE_7__ {int max_wqes; int max_sq_sg; int max_rq_sg; int max_sq_desc_sz; scalar_t__ fw_ver; } ;
struct TYPE_8__ {TYPE_3__ caps; } ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 int DIV_ROUND_UP (int,unsigned int) ; 
 int EINVAL ; 
 scalar_t__ MLX4_FW_VER_WQE_CTRL_NEC ; 
 int MLX4_IB_QPT_GSI ; 
 int MLX4_IB_QPT_PROXY_GSI ; 
 int MLX4_IB_QPT_PROXY_SMI ; 
 int MLX4_IB_QPT_PROXY_SMI_OWNER ; 
 int MLX4_IB_QPT_SMI ; 
 int MLX4_IB_QPT_TUN_SMI_OWNER ; 
 int MLX4_IB_SQ_MAX_SPARE ; 
 void* ilog2 (int) ; 
 int max (int,int) ; 
 int min (int,int) ; 
 int roundup_pow_of_two (int) ; 
 int send_wqe_overhead (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_kernel_sq_size(struct mlx4_ib_dev *dev, struct ib_qp_cap *cap,
			      enum mlx4_ib_qp_type type, struct mlx4_ib_qp *qp)
{
	int s;

	/* Sanity check SQ size before proceeding */
	if (cap->max_send_wr  > (dev->dev->caps.max_wqes - MLX4_IB_SQ_MAX_SPARE) ||
	    cap->max_send_sge > min(dev->dev->caps.max_sq_sg, dev->dev->caps.max_rq_sg) ||
	    cap->max_inline_data + send_wqe_overhead(type, qp->flags) +
	    sizeof (struct mlx4_wqe_inline_seg) > dev->dev->caps.max_sq_desc_sz)
		return -EINVAL;

	/*
	 * For MLX transport we need 2 extra S/G entries:
	 * one for the header and one for the checksum at the end
	 */
	if ((type == MLX4_IB_QPT_SMI || type == MLX4_IB_QPT_GSI ||
	     type & (MLX4_IB_QPT_PROXY_SMI_OWNER | MLX4_IB_QPT_TUN_SMI_OWNER)) &&
	    cap->max_send_sge + 2 > dev->dev->caps.max_sq_sg)
		return -EINVAL;

	s = max(cap->max_send_sge * sizeof (struct mlx4_wqe_data_seg),
		cap->max_inline_data + sizeof (struct mlx4_wqe_inline_seg)) +
		send_wqe_overhead(type, qp->flags);

	if (s > dev->dev->caps.max_sq_desc_sz)
		return -EINVAL;

	/*
	 * Hermon supports shrinking WQEs, such that a single work
	 * request can include multiple units of 1 << wqe_shift.  This
	 * way, work requests can differ in size, and do not have to
	 * be a power of 2 in size, saving memory and speeding up send
	 * WR posting.  Unfortunately, if we do this then the
	 * wqe_index field in CQEs can't be used to look up the WR ID
	 * anymore, so we do this only if selective signaling is off.
	 *
	 * Further, on 32-bit platforms, we can't use vmap() to make
	 * the QP buffer virtually contigious.  Thus we have to use
	 * constant-sized WRs to make sure a WR is always fully within
	 * a single page-sized chunk.
	 *
	 * Finally, we use NOP work requests to pad the end of the
	 * work queue, to avoid wrap-around in the middle of WR.  We
	 * set NEC bit to avoid getting completions with error for
	 * these NOP WRs, but since NEC is only supported starting
	 * with firmware 2.2.232, we use constant-sized WRs for older
	 * firmware.
	 *
	 * And, since MLX QPs only support SEND, we use constant-sized
	 * WRs in this case.
	 *
	 * We look for the smallest value of wqe_shift such that the
	 * resulting number of wqes does not exceed device
	 * capabilities.
	 *
	 * We set WQE size to at least 64 bytes, this way stamping
	 * invalidates each WQE.
	 */
	if (dev->dev->caps.fw_ver >= MLX4_FW_VER_WQE_CTRL_NEC &&
	    qp->sq_signal_bits && BITS_PER_LONG == 64 &&
	    type != MLX4_IB_QPT_SMI && type != MLX4_IB_QPT_GSI &&
	    !(type & (MLX4_IB_QPT_PROXY_SMI_OWNER | MLX4_IB_QPT_PROXY_SMI |
		      MLX4_IB_QPT_PROXY_GSI | MLX4_IB_QPT_TUN_SMI_OWNER)))
		qp->sq.wqe_shift = ilog2(64);
	else
		qp->sq.wqe_shift = ilog2(roundup_pow_of_two(s));

	for (;;) {
		qp->sq_max_wqes_per_wr = DIV_ROUND_UP(s, 1U << qp->sq.wqe_shift);

		/*
		 * We need to leave 2 KB + 1 WR of headroom in the SQ to
		 * allow HW to prefetch.
		 */
		qp->sq_spare_wqes = (2048 >> qp->sq.wqe_shift) + qp->sq_max_wqes_per_wr;
		qp->sq.wqe_cnt = roundup_pow_of_two(cap->max_send_wr *
						    qp->sq_max_wqes_per_wr +
						    qp->sq_spare_wqes);

		if (qp->sq.wqe_cnt <= dev->dev->caps.max_wqes)
			break;

		if (qp->sq_max_wqes_per_wr <= 1)
			return -EINVAL;

		++qp->sq.wqe_shift;
	}

	qp->sq.max_gs = (min(dev->dev->caps.max_sq_desc_sz,
			     (qp->sq_max_wqes_per_wr << qp->sq.wqe_shift)) -
			 send_wqe_overhead(type, qp->flags)) /
		sizeof (struct mlx4_wqe_data_seg);

	qp->buf_size = (qp->rq.wqe_cnt << qp->rq.wqe_shift) +
		(qp->sq.wqe_cnt << qp->sq.wqe_shift);
	if (qp->rq.wqe_shift > qp->sq.wqe_shift) {
		qp->rq.offset = 0;
		qp->sq.offset = qp->rq.wqe_cnt << qp->rq.wqe_shift;
	} else {
		qp->rq.offset = qp->sq.wqe_cnt << qp->sq.wqe_shift;
		qp->sq.offset = 0;
	}

	cap->max_send_wr  = qp->sq.max_post =
		(qp->sq.wqe_cnt - qp->sq_spare_wqes) / qp->sq_max_wqes_per_wr;
	cap->max_send_sge = min(qp->sq.max_gs,
				min(dev->dev->caps.max_sq_sg,
				    dev->dev->caps.max_rq_sg));
	/* We don't support inline sends for kernel QPs (yet) */
	cap->max_inline_data = 0;

	return 0;
}