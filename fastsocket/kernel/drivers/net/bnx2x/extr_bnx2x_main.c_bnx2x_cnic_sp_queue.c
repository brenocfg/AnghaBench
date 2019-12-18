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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct kwqe_16 {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  lo; int /*<<< orphan*/  hi; } ;
struct TYPE_7__ {TYPE_2__ update_data_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  type; int /*<<< orphan*/  conn_and_cmd_data; } ;
struct eth_spe {TYPE_3__ data; TYPE_1__ hdr; } ;
struct TYPE_8__ {scalar_t__ max_kwqe_pending; } ;
struct bnx2x {scalar_t__ recovery_state; scalar_t__ cnic_spq_pending; TYPE_4__ cnic_eth_dev; int /*<<< orphan*/  spq_lock; struct eth_spe* cnic_kwq_prod; struct eth_spe* cnic_kwq; struct eth_spe* cnic_kwq_last; int /*<<< orphan*/  cnic_kwq_pending; int /*<<< orphan*/  panic; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 scalar_t__ BNX2X_RECOVERY_DONE ; 
 scalar_t__ BNX2X_RECOVERY_NIC_LOADING ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int EIO ; 
 int /*<<< orphan*/  MAX_SP_DESC_CNT ; 
 int /*<<< orphan*/  bnx2x_cnic_sp_post (struct bnx2x*,int /*<<< orphan*/ ) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnx2x_cnic_sp_queue(struct net_device *dev,
			       struct kwqe_16 *kwqes[], u32 count)
{
	struct bnx2x *bp = netdev_priv(dev);
	int i;

#ifdef BNX2X_STOP_ON_ERROR
	if (unlikely(bp->panic)) {
		BNX2X_ERR("Can't post to SP queue while panic\n");
		return -EIO;
	}
#endif

	if ((bp->recovery_state != BNX2X_RECOVERY_DONE) &&
	    (bp->recovery_state != BNX2X_RECOVERY_NIC_LOADING)) {
		BNX2X_ERR("Handling parity error recovery. Try again later\n");
		return -EAGAIN;
	}

	spin_lock_bh(&bp->spq_lock);

	for (i = 0; i < count; i++) {
		struct eth_spe *spe = (struct eth_spe *)kwqes[i];

		if (bp->cnic_kwq_pending == MAX_SP_DESC_CNT)
			break;

		*bp->cnic_kwq_prod = *spe;

		bp->cnic_kwq_pending++;

		DP(BNX2X_MSG_SP, "L5 SPQE %x %x %x:%x pos %d\n",
		   spe->hdr.conn_and_cmd_data, spe->hdr.type,
		   spe->data.update_data_addr.hi,
		   spe->data.update_data_addr.lo,
		   bp->cnic_kwq_pending);

		if (bp->cnic_kwq_prod == bp->cnic_kwq_last)
			bp->cnic_kwq_prod = bp->cnic_kwq;
		else
			bp->cnic_kwq_prod++;
	}

	spin_unlock_bh(&bp->spq_lock);

	if (bp->cnic_spq_pending < bp->cnic_eth_dev.max_kwqe_pending)
		bnx2x_cnic_sp_post(bp, 0);

	return i;
}