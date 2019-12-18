#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {scalar_t__ pmf; } ;
struct TYPE_4__ {scalar_t__* ind_table; } ;
struct bnx2x {TYPE_3__ port; TYPE_2__* fp; TYPE_1__ rss_conf_obj; } ;
struct TYPE_5__ {scalar_t__ cl_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_NUM_ETH_QUEUES (struct bnx2x*) ; 
 int /*<<< orphan*/  CHIP_IS_E1x (struct bnx2x*) ; 
 int bnx2x_config_rss_eth (struct bnx2x*,int) ; 
 scalar_t__ ethtool_rxfh_indir_default (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnx2x_init_rss_pf(struct bnx2x *bp)
{
	int i;
	u8 num_eth_queues = BNX2X_NUM_ETH_QUEUES(bp);

	/* Prepare the initial contents for the indirection table if RSS is
	 * enabled
	 */
	for (i = 0; i < sizeof(bp->rss_conf_obj.ind_table); i++)
		bp->rss_conf_obj.ind_table[i] =
			bp->fp->cl_id +
			ethtool_rxfh_indir_default(i, num_eth_queues);

	/*
	 * For 57710 and 57711 SEARCHER configuration (rss_keys) is
	 * per-port, so if explicit configuration is needed , do it only
	 * for a PMF.
	 *
	 * For 57712 and newer on the other hand it's a per-function
	 * configuration.
	 */
	return bnx2x_config_rss_eth(bp, bp->port.pmf || !CHIP_IS_E1x(bp));
}