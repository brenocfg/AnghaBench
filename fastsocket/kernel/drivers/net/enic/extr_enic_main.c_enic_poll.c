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
struct net_device {int dummy; } ;
struct napi_struct {struct net_device* dev; } ;
struct enic {int /*<<< orphan*/ * intr; int /*<<< orphan*/ * rq; int /*<<< orphan*/ * cq; } ;

/* Variables and functions */
 unsigned int enic_cq_rq (struct enic*,int /*<<< orphan*/ ) ; 
 unsigned int enic_cq_wq (struct enic*,int /*<<< orphan*/ ) ; 
 unsigned int enic_legacy_io_intr () ; 
 int /*<<< orphan*/  enic_rq_alloc_buf ; 
 int /*<<< orphan*/  enic_rq_service ; 
 int /*<<< orphan*/  enic_wq_service ; 
 int /*<<< orphan*/  napi_complete (struct napi_struct*) ; 
 struct enic* netdev_priv (struct net_device*) ; 
 unsigned int vnic_cq_service (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_intr_return_credits (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnic_intr_unmask (int /*<<< orphan*/ *) ; 
 int vnic_rq_fill (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enic_poll(struct napi_struct *napi, int budget)
{
	struct net_device *netdev = napi->dev;
	struct enic *enic = netdev_priv(netdev);
	unsigned int cq_rq = enic_cq_rq(enic, 0);
	unsigned int cq_wq = enic_cq_wq(enic, 0);
	unsigned int intr = enic_legacy_io_intr();
	unsigned int rq_work_to_do = budget;
	unsigned int wq_work_to_do = -1; /* no limit */
	unsigned int  work_done, rq_work_done, wq_work_done;
	int err;

	/* Service RQ (first) and WQ
	 */

	rq_work_done = vnic_cq_service(&enic->cq[cq_rq],
		rq_work_to_do, enic_rq_service, NULL);

	wq_work_done = vnic_cq_service(&enic->cq[cq_wq],
		wq_work_to_do, enic_wq_service, NULL);

	/* Accumulate intr event credits for this polling
	 * cycle.  An intr event is the completion of a
	 * a WQ or RQ packet.
	 */

	work_done = rq_work_done + wq_work_done;

	if (work_done > 0)
		vnic_intr_return_credits(&enic->intr[intr],
			work_done,
			0 /* don't unmask intr */,
			0 /* don't reset intr timer */);

	err = vnic_rq_fill(&enic->rq[0], enic_rq_alloc_buf);

	/* Buffer allocation failed. Stay in polling
	 * mode so we can try to fill the ring again.
	 */

	if (err)
		rq_work_done = rq_work_to_do;

	if (rq_work_done < rq_work_to_do) {

		/* Some work done, but not enough to stay in polling,
		 * exit polling
		 */

		napi_complete(napi);
		vnic_intr_unmask(&enic->intr[intr]);
	}

	return rq_work_done;
}