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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  filter_flags; } ;
struct il_priv {int /*<<< orphan*/  mutex; TYPE_1__ staging; } ;
struct ieee80211_hw {struct il_priv* priv; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  CHK (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D_MAC80211 (char*,unsigned int,unsigned int) ; 
 unsigned int FIF_ALLMULTI ; 
 unsigned int FIF_BCN_PRBRESP_PROMISC ; 
 unsigned int FIF_CONTROL ; 
 unsigned int FIF_OTHER_BSS ; 
 unsigned int FIF_PROMISC_IN_BSS ; 
 int /*<<< orphan*/  RXON_FILTER_BCON_AWARE_MSK ; 
 int /*<<< orphan*/  RXON_FILTER_CTL2HOST_MSK ; 
 int /*<<< orphan*/  RXON_FILTER_PROMISC_MSK ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
il3945_configure_filter(struct ieee80211_hw *hw, unsigned int changed_flags,
			unsigned int *total_flags, u64 multicast)
{
	struct il_priv *il = hw->priv;
	__le32 filter_or = 0, filter_nand = 0;

#define CHK(test, flag)	do { \
	if (*total_flags & (test))		\
		filter_or |= (flag);		\
	else					\
		filter_nand |= (flag);		\
	} while (0)

	D_MAC80211("Enter: changed: 0x%x, total: 0x%x\n", changed_flags,
		   *total_flags);

	CHK(FIF_OTHER_BSS | FIF_PROMISC_IN_BSS, RXON_FILTER_PROMISC_MSK);
	CHK(FIF_CONTROL, RXON_FILTER_CTL2HOST_MSK);
	CHK(FIF_BCN_PRBRESP_PROMISC, RXON_FILTER_BCON_AWARE_MSK);

#undef CHK

	mutex_lock(&il->mutex);

	il->staging.filter_flags &= ~filter_nand;
	il->staging.filter_flags |= filter_or;

	/*
	 * Not committing directly because hardware can perform a scan,
	 * but even if hw is ready, committing here breaks for some reason,
	 * we'll eventually commit the filter flags change anyway.
	 */

	mutex_unlock(&il->mutex);

	/*
	 * Receiving all multicast frames is always enabled by the
	 * default flags setup in il_connection_init_rx_config()
	 * since we currently do not support programming multicast
	 * filters into the device.
	 */
	*total_flags &=
	    FIF_OTHER_BSS | FIF_ALLMULTI | FIF_PROMISC_IN_BSS |
	    FIF_BCN_PRBRESP_PROMISC | FIF_CONTROL;
}