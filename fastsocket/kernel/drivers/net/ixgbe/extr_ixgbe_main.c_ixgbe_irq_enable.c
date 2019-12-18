#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int type; } ;
struct TYPE_5__ {TYPE_1__ mac; } ;
struct ixgbe_adapter {int flags; int flags2; TYPE_2__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_EIMS ; 
 int IXGBE_EIMS_ECC ; 
 int IXGBE_EIMS_ENABLE_MASK ; 
 int IXGBE_EIMS_FLOW_DIR ; 
 int IXGBE_EIMS_GPI_SDP0 ; 
 int IXGBE_EIMS_GPI_SDP1 ; 
 int IXGBE_EIMS_GPI_SDP2 ; 
 int IXGBE_EIMS_LSC ; 
 int IXGBE_EIMS_MAILBOX ; 
 int IXGBE_EIMS_RTX_QUEUE ; 
 int IXGBE_EIMS_TIMESYNC ; 
 int IXGBE_EIMS_TS ; 
 int IXGBE_FLAG2_FDIR_REQUIRES_REINIT ; 
 int IXGBE_FLAG2_TEMP_SENSOR_CAPABLE ; 
 int IXGBE_FLAG_FAN_FAIL_CAPABLE ; 
 int IXGBE_FLAG_FDIR_HASH_CAPABLE ; 
 int IXGBE_FLAG_NEED_LINK_UPDATE ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (TYPE_2__*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixgbe_irq_enable_queues (struct ixgbe_adapter*,int /*<<< orphan*/ ) ; 
#define  ixgbe_mac_82599EB 129 
#define  ixgbe_mac_X540 128 

__attribute__((used)) static inline void ixgbe_irq_enable(struct ixgbe_adapter *adapter, bool queues,
				    bool flush)
{
	u32 mask = (IXGBE_EIMS_ENABLE_MASK & ~IXGBE_EIMS_RTX_QUEUE);

	/* don't reenable LSC while waiting for link */
	if (adapter->flags & IXGBE_FLAG_NEED_LINK_UPDATE)
		mask &= ~IXGBE_EIMS_LSC;

	if (adapter->flags2 & IXGBE_FLAG2_TEMP_SENSOR_CAPABLE)
		switch (adapter->hw.mac.type) {
		case ixgbe_mac_82599EB:
			mask |= IXGBE_EIMS_GPI_SDP0;
			break;
		case ixgbe_mac_X540:
			mask |= IXGBE_EIMS_TS;
			break;
		default:
			break;
		}
	if (adapter->flags & IXGBE_FLAG_FAN_FAIL_CAPABLE)
		mask |= IXGBE_EIMS_GPI_SDP1;
	switch (adapter->hw.mac.type) {
	case ixgbe_mac_82599EB:
		mask |= IXGBE_EIMS_GPI_SDP1;
		mask |= IXGBE_EIMS_GPI_SDP2;
	case ixgbe_mac_X540:
		mask |= IXGBE_EIMS_ECC;
		mask |= IXGBE_EIMS_MAILBOX;
		break;
	default:
		break;
	}

#ifdef CONFIG_IXGBE_PTP
	if (adapter->hw.mac.type == ixgbe_mac_X540)
		mask |= IXGBE_EIMS_TIMESYNC;
#endif

	if ((adapter->flags & IXGBE_FLAG_FDIR_HASH_CAPABLE) &&
	    !(adapter->flags2 & IXGBE_FLAG2_FDIR_REQUIRES_REINIT))
		mask |= IXGBE_EIMS_FLOW_DIR;

	IXGBE_WRITE_REG(&adapter->hw, IXGBE_EIMS, mask);
	if (queues)
		ixgbe_irq_enable_queues(adapter, ~0);
	if (flush)
		IXGBE_WRITE_FLUSH(&adapter->hw);
}