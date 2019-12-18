#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct netdev_queue {int dummy; } ;
struct TYPE_5__ {struct sk_buff** arr; } ;
struct ehea_port_res {int sq_restart_flag; scalar_t__ swqe_refill_th; TYPE_2__* port; int /*<<< orphan*/  swqe_avail; TYPE_1__ sq_skba; struct ehea_cq* send_cq; } ;
struct ehea_cqe {scalar_t__ wr_id; int status; } ;
struct ehea_cq {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  swqe_avail_wq; struct ehea_port_res* port_res; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int EHEA_BMASK_GET (int /*<<< orphan*/ ,scalar_t__) ; 
 int EHEA_CQE_STAT_ERR_MASK ; 
 int EHEA_CQE_STAT_RESET_MASK ; 
 int EHEA_SWQE2_TYPE ; 
 int /*<<< orphan*/  EHEA_WR_ID_INDEX ; 
 int /*<<< orphan*/  EHEA_WR_ID_REFILL ; 
 int /*<<< orphan*/  EHEA_WR_ID_TYPE ; 
 scalar_t__ SWQE_RESTART_CHECK ; 
 int /*<<< orphan*/  __netif_tx_lock (struct netdev_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __netif_tx_unlock (struct netdev_queue*) ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ehea_dump (struct ehea_cqe*,int,char*) ; 
 int /*<<< orphan*/  ehea_error (char*,...) ; 
 int /*<<< orphan*/  ehea_inc_cq (struct ehea_cq*) ; 
 struct ehea_cqe* ehea_poll_cq (struct ehea_cq*) ; 
 int /*<<< orphan*/  ehea_schedule_port_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  ehea_update_feca (struct ehea_cq*,int) ; 
 scalar_t__ likely (int) ; 
 struct netdev_queue* netdev_get_tx_queue (int /*<<< orphan*/ ,int) ; 
 scalar_t__ netif_msg_tx_done (TYPE_2__*) ; 
 scalar_t__ netif_msg_tx_err (TYPE_2__*) ; 
 scalar_t__ netif_tx_queue_stopped (struct netdev_queue*) ; 
 int /*<<< orphan*/  netif_tx_wake_queue (struct netdev_queue*) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ehea_cqe *ehea_proc_cqes(struct ehea_port_res *pr, int my_quota)
{
	struct sk_buff *skb;
	struct ehea_cq *send_cq = pr->send_cq;
	struct ehea_cqe *cqe;
	int quota = my_quota;
	int cqe_counter = 0;
	int swqe_av = 0;
	int index;
	struct netdev_queue *txq = netdev_get_tx_queue(pr->port->netdev,
						pr - &pr->port->port_res[0]);

	cqe = ehea_poll_cq(send_cq);
	while (cqe && (quota > 0)) {
		ehea_inc_cq(send_cq);

		cqe_counter++;
		rmb();

		if (cqe->wr_id == SWQE_RESTART_CHECK) {
			pr->sq_restart_flag = 1;
			swqe_av++;
			break;
		}

		if (cqe->status & EHEA_CQE_STAT_ERR_MASK) {
			ehea_error("Bad send completion status=0x%04X",
				   cqe->status);

			if (netif_msg_tx_err(pr->port))
				ehea_dump(cqe, sizeof(*cqe), "Send CQE");

			if (cqe->status & EHEA_CQE_STAT_RESET_MASK) {
				ehea_error("Resetting port");
				ehea_schedule_port_reset(pr->port);
				break;
			}
		}

		if (netif_msg_tx_done(pr->port))
			ehea_dump(cqe, sizeof(*cqe), "CQE");

		if (likely(EHEA_BMASK_GET(EHEA_WR_ID_TYPE, cqe->wr_id)
			   == EHEA_SWQE2_TYPE)) {

			index = EHEA_BMASK_GET(EHEA_WR_ID_INDEX, cqe->wr_id);
			skb = pr->sq_skba.arr[index];
			dev_kfree_skb(skb);
			pr->sq_skba.arr[index] = NULL;
		}

		swqe_av += EHEA_BMASK_GET(EHEA_WR_ID_REFILL, cqe->wr_id);
		quota--;

		cqe = ehea_poll_cq(send_cq);
	};

	ehea_update_feca(send_cq, cqe_counter);
	atomic_add(swqe_av, &pr->swqe_avail);

	if (unlikely(netif_tx_queue_stopped(txq) &&
		     (atomic_read(&pr->swqe_avail) >= pr->swqe_refill_th))) {
		__netif_tx_lock(txq, smp_processor_id());
		if (netif_tx_queue_stopped(txq) &&
		    (atomic_read(&pr->swqe_avail) >= pr->swqe_refill_th))
			netif_tx_wake_queue(txq);
		__netif_tx_unlock(txq);
	}

	wake_up(&pr->port->swqe_avail_wq);

	return cqe;
}