#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int syndrome; int /*<<< orphan*/  cqn; } ;
struct TYPE_12__ {int /*<<< orphan*/  port; } ;
struct TYPE_11__ {int /*<<< orphan*/  out_param; int /*<<< orphan*/  status; int /*<<< orphan*/  token; } ;
struct TYPE_10__ {int /*<<< orphan*/  qpn; } ;
struct TYPE_9__ {int /*<<< orphan*/  srqn; } ;
struct TYPE_8__ {int /*<<< orphan*/  cqn; } ;
struct TYPE_14__ {TYPE_6__ cq_err; TYPE_5__ port_change; TYPE_4__ cmd; TYPE_3__ qp; TYPE_2__ srq; TYPE_1__ comp; } ;
struct mthca_eqe {int type; int subtype; TYPE_7__ event; } ;
struct mthca_eq {int /*<<< orphan*/  cons_index; int /*<<< orphan*/  eqn; } ;
struct mthca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_EVENT_COMM_EST ; 
 int /*<<< orphan*/  IB_EVENT_CQ_ERR ; 
 int /*<<< orphan*/  IB_EVENT_PATH_MIG ; 
 int /*<<< orphan*/  IB_EVENT_PATH_MIG_ERR ; 
 int /*<<< orphan*/  IB_EVENT_QP_ACCESS_ERR ; 
 int /*<<< orphan*/  IB_EVENT_QP_FATAL ; 
 int /*<<< orphan*/  IB_EVENT_QP_LAST_WQE_REACHED ; 
 int /*<<< orphan*/  IB_EVENT_QP_REQ_ERR ; 
 int /*<<< orphan*/  IB_EVENT_SQ_DRAINED ; 
 int /*<<< orphan*/  IB_EVENT_SRQ_LIMIT_REACHED ; 
#define  MTHCA_EVENT_TYPE_CMD 145 
#define  MTHCA_EVENT_TYPE_COMM_EST 144 
#define  MTHCA_EVENT_TYPE_COMP 143 
#define  MTHCA_EVENT_TYPE_CQ_ERROR 142 
#define  MTHCA_EVENT_TYPE_ECC_DETECT 141 
#define  MTHCA_EVENT_TYPE_EEC_CATAS_ERROR 140 
#define  MTHCA_EVENT_TYPE_EQ_OVERFLOW 139 
#define  MTHCA_EVENT_TYPE_LOCAL_CATAS_ERROR 138 
#define  MTHCA_EVENT_TYPE_PATH_MIG 137 
#define  MTHCA_EVENT_TYPE_PATH_MIG_FAILED 136 
#define  MTHCA_EVENT_TYPE_PORT_CHANGE 135 
#define  MTHCA_EVENT_TYPE_SQ_DRAINED 134 
#define  MTHCA_EVENT_TYPE_SRQ_CATAS_ERROR 133 
#define  MTHCA_EVENT_TYPE_SRQ_LIMIT 132 
#define  MTHCA_EVENT_TYPE_SRQ_QP_LAST_WQE 131 
#define  MTHCA_EVENT_TYPE_WQ_ACCESS_ERROR 130 
#define  MTHCA_EVENT_TYPE_WQ_CATAS_ERROR 129 
#define  MTHCA_EVENT_TYPE_WQ_INVAL_REQ_ERROR 128 
 int MTHCA_NUM_SPARE_EQE ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disarm_cq (struct mthca_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mthca_cmd_event (struct mthca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_cq_completion (struct mthca_dev*,int) ; 
 int /*<<< orphan*/  mthca_cq_event (struct mthca_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_qp_event (struct mthca_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_srq_event (struct mthca_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_warn (struct mthca_dev*,char*,...) ; 
 struct mthca_eqe* next_eqe_sw (struct mthca_eq*) ; 
 int /*<<< orphan*/  port_change (struct mthca_dev*,int,int) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  set_eq_ci (struct mthca_dev*,struct mthca_eq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_eqe_hw (struct mthca_eqe*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mthca_eq_int(struct mthca_dev *dev, struct mthca_eq *eq)
{
	struct mthca_eqe *eqe;
	int disarm_cqn;
	int eqes_found = 0;
	int set_ci = 0;

	while ((eqe = next_eqe_sw(eq))) {
		/*
		 * Make sure we read EQ entry contents after we've
		 * checked the ownership bit.
		 */
		rmb();

		switch (eqe->type) {
		case MTHCA_EVENT_TYPE_COMP:
			disarm_cqn = be32_to_cpu(eqe->event.comp.cqn) & 0xffffff;
			disarm_cq(dev, eq->eqn, disarm_cqn);
			mthca_cq_completion(dev, disarm_cqn);
			break;

		case MTHCA_EVENT_TYPE_PATH_MIG:
			mthca_qp_event(dev, be32_to_cpu(eqe->event.qp.qpn) & 0xffffff,
				       IB_EVENT_PATH_MIG);
			break;

		case MTHCA_EVENT_TYPE_COMM_EST:
			mthca_qp_event(dev, be32_to_cpu(eqe->event.qp.qpn) & 0xffffff,
				       IB_EVENT_COMM_EST);
			break;

		case MTHCA_EVENT_TYPE_SQ_DRAINED:
			mthca_qp_event(dev, be32_to_cpu(eqe->event.qp.qpn) & 0xffffff,
				       IB_EVENT_SQ_DRAINED);
			break;

		case MTHCA_EVENT_TYPE_SRQ_QP_LAST_WQE:
			mthca_qp_event(dev, be32_to_cpu(eqe->event.qp.qpn) & 0xffffff,
				       IB_EVENT_QP_LAST_WQE_REACHED);
			break;

		case MTHCA_EVENT_TYPE_SRQ_LIMIT:
			mthca_srq_event(dev, be32_to_cpu(eqe->event.srq.srqn) & 0xffffff,
					IB_EVENT_SRQ_LIMIT_REACHED);
			break;

		case MTHCA_EVENT_TYPE_WQ_CATAS_ERROR:
			mthca_qp_event(dev, be32_to_cpu(eqe->event.qp.qpn) & 0xffffff,
				       IB_EVENT_QP_FATAL);
			break;

		case MTHCA_EVENT_TYPE_PATH_MIG_FAILED:
			mthca_qp_event(dev, be32_to_cpu(eqe->event.qp.qpn) & 0xffffff,
				       IB_EVENT_PATH_MIG_ERR);
			break;

		case MTHCA_EVENT_TYPE_WQ_INVAL_REQ_ERROR:
			mthca_qp_event(dev, be32_to_cpu(eqe->event.qp.qpn) & 0xffffff,
				       IB_EVENT_QP_REQ_ERR);
			break;

		case MTHCA_EVENT_TYPE_WQ_ACCESS_ERROR:
			mthca_qp_event(dev, be32_to_cpu(eqe->event.qp.qpn) & 0xffffff,
				       IB_EVENT_QP_ACCESS_ERR);
			break;

		case MTHCA_EVENT_TYPE_CMD:
			mthca_cmd_event(dev,
					be16_to_cpu(eqe->event.cmd.token),
					eqe->event.cmd.status,
					be64_to_cpu(eqe->event.cmd.out_param));
			break;

		case MTHCA_EVENT_TYPE_PORT_CHANGE:
			port_change(dev,
				    (be32_to_cpu(eqe->event.port_change.port) >> 28) & 3,
				    eqe->subtype == 0x4);
			break;

		case MTHCA_EVENT_TYPE_CQ_ERROR:
			mthca_warn(dev, "CQ %s on CQN %06x\n",
				   eqe->event.cq_err.syndrome == 1 ?
				   "overrun" : "access violation",
				   be32_to_cpu(eqe->event.cq_err.cqn) & 0xffffff);
			mthca_cq_event(dev, be32_to_cpu(eqe->event.cq_err.cqn),
				       IB_EVENT_CQ_ERR);
			break;

		case MTHCA_EVENT_TYPE_EQ_OVERFLOW:
			mthca_warn(dev, "EQ overrun on EQN %d\n", eq->eqn);
			break;

		case MTHCA_EVENT_TYPE_EEC_CATAS_ERROR:
		case MTHCA_EVENT_TYPE_SRQ_CATAS_ERROR:
		case MTHCA_EVENT_TYPE_LOCAL_CATAS_ERROR:
		case MTHCA_EVENT_TYPE_ECC_DETECT:
		default:
			mthca_warn(dev, "Unhandled event %02x(%02x) on EQ %d\n",
				   eqe->type, eqe->subtype, eq->eqn);
			break;
		};

		set_eqe_hw(eqe);
		++eq->cons_index;
		eqes_found = 1;
		++set_ci;

		/*
		 * The HCA will think the queue has overflowed if we
		 * don't tell it we've been processing events.  We
		 * create our EQs with MTHCA_NUM_SPARE_EQE extra
		 * entries, so we must update our consumer index at
		 * least that often.
		 */
		if (unlikely(set_ci >= MTHCA_NUM_SPARE_EQE)) {
			/*
			 * Conditional on hca_type is OK here because
			 * this is a rare case, not the fast path.
			 */
			set_eq_ci(dev, eq, eq->cons_index);
			set_ci = 0;
		}
	}

	/*
	 * Rely on caller to set consumer index so that we don't have
	 * to test hca_type in our interrupt handling fast path.
	 */
	return eqes_found;
}