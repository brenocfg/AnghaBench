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
struct enic {int /*<<< orphan*/ * intr; int /*<<< orphan*/ * rq; int /*<<< orphan*/ * cq; struct napi_struct* napi; } ;

/* Variables and functions */
 unsigned int enic_cq_rq (struct enic*,unsigned int) ; 
 unsigned int enic_msix_rq_intr (struct enic*,unsigned int) ; 
 int /*<<< orphan*/  enic_rq_alloc_buf ; 
 int /*<<< orphan*/  enic_rq_service ; 
 int /*<<< orphan*/  napi_complete (struct napi_struct*) ; 
 struct enic* netdev_priv (struct net_device*) ; 
 unsigned int vnic_cq_service (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_intr_return_credits (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnic_intr_unmask (int /*<<< orphan*/ *) ; 
 int vnic_rq_fill (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enic_poll_msix(struct napi_struct *napi, int budget)
{
	struct net_device *netdev = napi->dev;
	struct enic *enic = netdev_priv(netdev);
	unsigned int rq = (napi - &enic->napi[0]);
	unsigned int cq = enic_cq_rq(enic, rq);
	unsigned int intr = enic_msix_rq_intr(enic, rq);
	unsigned int work_to_do = budget;
	unsigned int work_done;
	int err;

	/* Service RQ
	 */

	work_done = vnic_cq_service(&enic->cq[cq],
		work_to_do, enic_rq_service, NULL);

	/* Return intr event credits for this polling
	 * cycle.  An intr event is the completion of a
	 * RQ packet.
	 */

	if (work_done > 0)
		vnic_intr_return_credits(&enic->intr[intr],
			work_done,
			0 /* don't unmask intr */,
			0 /* don't reset intr timer */);

	err = vnic_rq_fill(&enic->rq[rq], enic_rq_alloc_buf);

	/* Buffer allocation failed. Stay in polling mode
	 * so we can try to fill the ring again.
	 */

	if (err)
		work_done = work_to_do;

	if (work_done < work_to_do) {

		/* Some work done, but not enough to stay in polling,
		 * exit polling
		 */

		napi_complete(napi);
		vnic_intr_unmask(&enic->intr[intr]);
	}

	return work_done;
}