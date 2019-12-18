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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  mgid_index; } ;
struct TYPE_3__ {int /*<<< orphan*/  mgid_index; } ;
struct mlx4_qp_context {TYPE_2__ alt_path; TYPE_1__ pri_path; int /*<<< orphan*/  flags; } ;
struct mlx4_dev {int dummy; } ;
struct mlx4_cmd_mailbox {struct mlx4_qp_context* buf; } ;
typedef  enum qp_transition { ____Placeholder_qp_transition } qp_transition ;
typedef  enum mlx4_qp_optpar { ____Placeholder_mlx4_qp_optpar } mlx4_qp_optpar ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 int MLX4_QP_OPTPAR_ALT_ADDR_PATH ; 
 int MLX4_QP_OPTPAR_PRIMARY_ADDR_PATH ; 
#define  MLX4_QP_ST_RC 134 
#define  MLX4_QP_ST_UC 133 
#define  QP_TRANS_INIT2RTR 132 
#define  QP_TRANS_RTR2RTS 131 
#define  QP_TRANS_RTS2RTS 130 
#define  QP_TRANS_SQD2RTS 129 
#define  QP_TRANS_SQD2SQD 128 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_master_func_num (struct mlx4_dev*) ; 

__attribute__((used)) static int verify_qp_parameters(struct mlx4_dev *dev,
				struct mlx4_cmd_mailbox *inbox,
				enum qp_transition transition, u8 slave)
{
	u32			qp_type;
	struct mlx4_qp_context	*qp_ctx;
	enum mlx4_qp_optpar	optpar;

	qp_ctx  = inbox->buf + 8;
	qp_type	= (be32_to_cpu(qp_ctx->flags) >> 16) & 0xff;
	optpar	= be32_to_cpu(*(__be32 *) inbox->buf);

	switch (qp_type) {
	case MLX4_QP_ST_RC:
	case MLX4_QP_ST_UC:
		switch (transition) {
		case QP_TRANS_INIT2RTR:
		case QP_TRANS_RTR2RTS:
		case QP_TRANS_RTS2RTS:
		case QP_TRANS_SQD2SQD:
		case QP_TRANS_SQD2RTS:
			if (slave != mlx4_master_func_num(dev))
				/* slaves have only gid index 0 */
				if (optpar & MLX4_QP_OPTPAR_PRIMARY_ADDR_PATH)
					if (qp_ctx->pri_path.mgid_index)
						return -EINVAL;
				if (optpar & MLX4_QP_OPTPAR_ALT_ADDR_PATH)
					if (qp_ctx->alt_path.mgid_index)
						return -EINVAL;
			break;
		default:
			break;
		}

		break;
	default:
		break;
	}

	return 0;
}