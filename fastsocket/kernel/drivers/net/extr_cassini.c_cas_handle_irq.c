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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct cas {int /*<<< orphan*/ * stat_lock; TYPE_1__* net_stats; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_dropped; } ;

/* Variables and functions */
 int const INTR_ERROR_MASK ; 
 int const INTR_RX_BUF_AE ; 
 int const INTR_RX_BUF_UNAVAIL ; 
 int const INTR_RX_COMP_AF ; 
 int const INTR_RX_COMP_FULL ; 
 scalar_t__ RX_AE_FREEN_VAL (int /*<<< orphan*/ ) ; 
 scalar_t__ RX_DESC_RINGN_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cas_abnormal_irq (struct net_device*,struct cas*,int const) ; 
 int /*<<< orphan*/  cas_post_rxcs_ringN (struct net_device*,struct cas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cas_post_rxds_ringN (struct cas*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void cas_handle_irq(struct net_device *dev,
				  struct cas *cp, const u32 status)
{
	/* housekeeping interrupts */
	if (status & INTR_ERROR_MASK)
		cas_abnormal_irq(dev, cp, status);

	if (status & INTR_RX_BUF_UNAVAIL) {
		/* Frame arrived, no free RX buffers available.
		 * NOTE: we can get this on a link transition.
		 */
		cas_post_rxds_ringN(cp, 0, 0);
		spin_lock(&cp->stat_lock[0]);
		cp->net_stats[0].rx_dropped++;
		spin_unlock(&cp->stat_lock[0]);
	} else if (status & INTR_RX_BUF_AE) {
		cas_post_rxds_ringN(cp, 0, RX_DESC_RINGN_SIZE(0) -
				    RX_AE_FREEN_VAL(0));
	}

	if (status & (INTR_RX_COMP_AF | INTR_RX_COMP_FULL))
		cas_post_rxcs_ringN(dev, cp, 0);
}