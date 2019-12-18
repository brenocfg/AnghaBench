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
typedef  int /*<<< orphan*/  u32 ;
struct kwqe {int dummy; } ;
struct iscsi_kwqe_init1 {int num_tasks_per_conn; int num_ccells_per_conn; int rq_num_wqes; int rq_buffer_size; int cq_num_wqes; int /*<<< orphan*/  num_cqs; } ;
struct cnic_local {int num_iscsi_tasks; int num_ccells; int task_array_size; int r2tq_size; int hq_size; int /*<<< orphan*/  num_cqs; int /*<<< orphan*/  pfid; } ;
struct cnic_dev {int /*<<< orphan*/  max_iscsi_conn; int /*<<< orphan*/  netdev; struct cnic_local* cnic_priv; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAR_CSTRORM_INTMEM ; 
 scalar_t__ BAR_TSTRORM_INTMEM ; 
 scalar_t__ BAR_USTRORM_INTMEM ; 
 scalar_t__ BAR_XSTRORM_INTMEM ; 
 int BNX2X_ISCSI_HQ_BD_SIZE ; 
 int BNX2X_ISCSI_MAX_PENDING_R2TS ; 
 int BNX2X_ISCSI_R2TQE_SIZE ; 
 int BNX2X_ISCSI_TASK_CONTEXT_SIZE ; 
 int /*<<< orphan*/  CNIC_WR16 (struct cnic_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  CNIC_WR8 (struct cnic_dev*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ CSTORM_ISCSI_CQ_SIZE_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ CSTORM_ISCSI_HQ_SIZE_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ CSTORM_ISCSI_NUM_OF_TASKS_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ CSTORM_ISCSI_PAGE_SIZE_LOG_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ CSTORM_ISCSI_PAGE_SIZE_OFFSET (int /*<<< orphan*/ ) ; 
 int PAGE_ALIGN (int) ; 
 int /*<<< orphan*/  PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 scalar_t__ TSTORM_ISCSI_NUM_OF_TASKS_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ TSTORM_ISCSI_PAGE_SIZE_LOG_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ TSTORM_ISCSI_PAGE_SIZE_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ TSTORM_ISCSI_RQ_SIZE_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ USTORM_ISCSI_CQ_SIZE_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ USTORM_ISCSI_NUM_OF_TASKS_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ USTORM_ISCSI_PAGE_SIZE_LOG_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ USTORM_ISCSI_PAGE_SIZE_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ USTORM_ISCSI_R2TQ_SIZE_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ USTORM_ISCSI_RQ_BUFFER_SIZE_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ USTORM_ISCSI_RQ_SIZE_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ XSTORM_ISCSI_HQ_SIZE_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ XSTORM_ISCSI_NUM_OF_TASKS_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ XSTORM_ISCSI_PAGE_SIZE_LOG_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ XSTORM_ISCSI_PAGE_SIZE_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ XSTORM_ISCSI_R2TQ_SIZE_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ XSTORM_ISCSI_SQ_SIZE_OFFSET (int /*<<< orphan*/ ) ; 
 struct bnx2x* netdev_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cnic_bnx2x_iscsi_init1(struct cnic_dev *dev, struct kwqe *kwqe)
{
	struct cnic_local *cp = dev->cnic_priv;
	struct bnx2x *bp = netdev_priv(dev->netdev);
	struct iscsi_kwqe_init1 *req1 = (struct iscsi_kwqe_init1 *) kwqe;
	int hq_bds, pages;
	u32 pfid = cp->pfid;

	cp->num_iscsi_tasks = req1->num_tasks_per_conn;
	cp->num_ccells = req1->num_ccells_per_conn;
	cp->task_array_size = BNX2X_ISCSI_TASK_CONTEXT_SIZE *
			      cp->num_iscsi_tasks;
	cp->r2tq_size = cp->num_iscsi_tasks * BNX2X_ISCSI_MAX_PENDING_R2TS *
			BNX2X_ISCSI_R2TQE_SIZE;
	cp->hq_size = cp->num_ccells * BNX2X_ISCSI_HQ_BD_SIZE;
	pages = PAGE_ALIGN(cp->hq_size) / PAGE_SIZE;
	hq_bds = pages * (PAGE_SIZE / BNX2X_ISCSI_HQ_BD_SIZE);
	cp->num_cqs = req1->num_cqs;

	if (!dev->max_iscsi_conn)
		return 0;

	/* init Tstorm RAM */
	CNIC_WR16(dev, BAR_TSTRORM_INTMEM + TSTORM_ISCSI_RQ_SIZE_OFFSET(pfid),
		  req1->rq_num_wqes);
	CNIC_WR16(dev, BAR_TSTRORM_INTMEM + TSTORM_ISCSI_PAGE_SIZE_OFFSET(pfid),
		  PAGE_SIZE);
	CNIC_WR8(dev, BAR_TSTRORM_INTMEM +
		 TSTORM_ISCSI_PAGE_SIZE_LOG_OFFSET(pfid), PAGE_SHIFT);
	CNIC_WR16(dev, BAR_TSTRORM_INTMEM +
		  TSTORM_ISCSI_NUM_OF_TASKS_OFFSET(pfid),
		  req1->num_tasks_per_conn);

	/* init Ustorm RAM */
	CNIC_WR16(dev, BAR_USTRORM_INTMEM +
		  USTORM_ISCSI_RQ_BUFFER_SIZE_OFFSET(pfid),
		  req1->rq_buffer_size);
	CNIC_WR16(dev, BAR_USTRORM_INTMEM + USTORM_ISCSI_PAGE_SIZE_OFFSET(pfid),
		  PAGE_SIZE);
	CNIC_WR8(dev, BAR_USTRORM_INTMEM +
		 USTORM_ISCSI_PAGE_SIZE_LOG_OFFSET(pfid), PAGE_SHIFT);
	CNIC_WR16(dev, BAR_USTRORM_INTMEM +
		  USTORM_ISCSI_NUM_OF_TASKS_OFFSET(pfid),
		  req1->num_tasks_per_conn);
	CNIC_WR16(dev, BAR_USTRORM_INTMEM + USTORM_ISCSI_RQ_SIZE_OFFSET(pfid),
		  req1->rq_num_wqes);
	CNIC_WR16(dev, BAR_USTRORM_INTMEM + USTORM_ISCSI_CQ_SIZE_OFFSET(pfid),
		  req1->cq_num_wqes);
	CNIC_WR16(dev, BAR_USTRORM_INTMEM + USTORM_ISCSI_R2TQ_SIZE_OFFSET(pfid),
		  cp->num_iscsi_tasks * BNX2X_ISCSI_MAX_PENDING_R2TS);

	/* init Xstorm RAM */
	CNIC_WR16(dev, BAR_XSTRORM_INTMEM + XSTORM_ISCSI_PAGE_SIZE_OFFSET(pfid),
		  PAGE_SIZE);
	CNIC_WR8(dev, BAR_XSTRORM_INTMEM +
		 XSTORM_ISCSI_PAGE_SIZE_LOG_OFFSET(pfid), PAGE_SHIFT);
	CNIC_WR16(dev, BAR_XSTRORM_INTMEM +
		  XSTORM_ISCSI_NUM_OF_TASKS_OFFSET(pfid),
		  req1->num_tasks_per_conn);
	CNIC_WR16(dev, BAR_XSTRORM_INTMEM + XSTORM_ISCSI_HQ_SIZE_OFFSET(pfid),
		  hq_bds);
	CNIC_WR16(dev, BAR_XSTRORM_INTMEM + XSTORM_ISCSI_SQ_SIZE_OFFSET(pfid),
		  req1->num_tasks_per_conn);
	CNIC_WR16(dev, BAR_XSTRORM_INTMEM + XSTORM_ISCSI_R2TQ_SIZE_OFFSET(pfid),
		  cp->num_iscsi_tasks * BNX2X_ISCSI_MAX_PENDING_R2TS);

	/* init Cstorm RAM */
	CNIC_WR16(dev, BAR_CSTRORM_INTMEM + CSTORM_ISCSI_PAGE_SIZE_OFFSET(pfid),
		  PAGE_SIZE);
	CNIC_WR8(dev, BAR_CSTRORM_INTMEM +
		 CSTORM_ISCSI_PAGE_SIZE_LOG_OFFSET(pfid), PAGE_SHIFT);
	CNIC_WR16(dev, BAR_CSTRORM_INTMEM +
		  CSTORM_ISCSI_NUM_OF_TASKS_OFFSET(pfid),
		  req1->num_tasks_per_conn);
	CNIC_WR16(dev, BAR_CSTRORM_INTMEM + CSTORM_ISCSI_CQ_SIZE_OFFSET(pfid),
		  req1->cq_num_wqes);
	CNIC_WR16(dev, BAR_CSTRORM_INTMEM + CSTORM_ISCSI_HQ_SIZE_OFFSET(pfid),
		  hq_bds);

	return 0;
}