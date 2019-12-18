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
struct TYPE_2__ {int status_flags; int type_error_flags; } ;
union eth_rx_cqe {TYPE_1__ fast_path_cqe; } ;
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;
struct bnx2x_fastpath {int dummy; } ;
struct bnx2x_eth_q_stats {int /*<<< orphan*/  hw_csum_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int ETH_FAST_PATH_RX_CQE_IP_BAD_XSUM_FLG ; 
 int ETH_FAST_PATH_RX_CQE_L4_BAD_XSUM_FLG ; 
 int ETH_FAST_PATH_RX_CQE_L4_XSUM_NO_VALIDATION_FLG ; 

__attribute__((used)) static
void bnx2x_csum_validate(struct sk_buff *skb, union eth_rx_cqe *cqe,
				 struct bnx2x_fastpath *fp,
				 struct bnx2x_eth_q_stats *qstats)
{
	/* Do nothing if no L4 csum validation was done.
	 * We do not check whether IP csum was validated. For IPv4 we assume
	 * that if the card got as far as validating the L4 csum, it also
	 * validated the IP csum. IPv6 has no IP csum.
	 */
	if (cqe->fast_path_cqe.status_flags &
	    ETH_FAST_PATH_RX_CQE_L4_XSUM_NO_VALIDATION_FLG)
		return;

	/* If L4 validation was done, check if an error was found. */

	if (cqe->fast_path_cqe.type_error_flags &
	    (ETH_FAST_PATH_RX_CQE_IP_BAD_XSUM_FLG |
	     ETH_FAST_PATH_RX_CQE_L4_BAD_XSUM_FLG))
		qstats->hw_csum_err++;
	else
		skb->ip_summed = CHECKSUM_UNNECESSARY;
}