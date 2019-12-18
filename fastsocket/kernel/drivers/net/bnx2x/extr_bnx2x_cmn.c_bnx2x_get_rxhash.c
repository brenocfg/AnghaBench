#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct eth_fast_path_rx_cqe {int status_flags; int /*<<< orphan*/  rss_hash_result; } ;
struct bnx2x {TYPE_1__* dev; } ;
struct TYPE_2__ {int features; } ;

/* Variables and functions */
 int ETH_FAST_PATH_RX_CQE_RSS_HASH_FLG ; 
 int NETIF_F_RXHASH ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 bnx2x_get_rxhash(const struct bnx2x *bp,
			    const struct eth_fast_path_rx_cqe *cqe)
{
	/* Get Toeplitz hash from CQE */
	if ((bp->dev->features & NETIF_F_RXHASH) &&
	    (cqe->status_flags & ETH_FAST_PATH_RX_CQE_RSS_HASH_FLG))
		return le32_to_cpu(cqe->rss_hash_result);
	return 0;
}