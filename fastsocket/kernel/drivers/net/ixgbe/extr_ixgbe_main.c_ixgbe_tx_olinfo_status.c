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
struct TYPE_2__ {int /*<<< orphan*/  olinfo_status; } ;
union ixgbe_adv_tx_desc {TYPE_1__ read; } ;
typedef  unsigned int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_ADVTXD_CC ; 
 unsigned int IXGBE_ADVTXD_PAYLEN_SHIFT ; 
 int /*<<< orphan*/  IXGBE_ADVTXD_POPTS_IXSM ; 
 int /*<<< orphan*/  IXGBE_ADVTXD_POPTS_TXSM ; 
 unsigned int IXGBE_SET_FLAG (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_TX_FLAGS_CC ; 
 int /*<<< orphan*/  IXGBE_TX_FLAGS_CSUM ; 
 int /*<<< orphan*/  IXGBE_TX_FLAGS_IPV4 ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 

__attribute__((used)) static void ixgbe_tx_olinfo_status(union ixgbe_adv_tx_desc *tx_desc,
				   u32 tx_flags, unsigned int paylen)
{
	u32 olinfo_status = paylen << IXGBE_ADVTXD_PAYLEN_SHIFT;

	/* enable L4 checksum for TSO and TX checksum offload */
	olinfo_status |= IXGBE_SET_FLAG(tx_flags,
					IXGBE_TX_FLAGS_CSUM,
					IXGBE_ADVTXD_POPTS_TXSM);

	/* enble IPv4 checksum for TSO */
	olinfo_status |= IXGBE_SET_FLAG(tx_flags,
					IXGBE_TX_FLAGS_IPV4,
					IXGBE_ADVTXD_POPTS_IXSM);

	/*
	 * Check Context must be set if Tx switch is enabled, which it
	 * always is for case where virtual functions are running
	 */
	olinfo_status |= IXGBE_SET_FLAG(tx_flags,
					IXGBE_TX_FLAGS_CC,
					IXGBE_ADVTXD_CC);

	tx_desc->read.olinfo_status = cpu_to_le32(olinfo_status);
}