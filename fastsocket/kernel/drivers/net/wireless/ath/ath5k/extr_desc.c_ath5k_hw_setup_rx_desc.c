#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ath5k_hw_rx_ctl {int rx_control_1; } ;
struct ath5k_hw_all_rx_desc {int dummy; } ;
struct ath5k_hw {int dummy; } ;
struct TYPE_4__ {struct ath5k_hw_rx_ctl rx_ctl; } ;
struct TYPE_3__ {TYPE_2__ ds_rx; } ;
struct ath5k_desc {TYPE_1__ ud; } ;

/* Variables and functions */
 int AR5K_DESC_RX_CTL1_BUF_LEN ; 
 int AR5K_DESC_RX_CTL1_INTREQ ; 
 unsigned int AR5K_RXDESC_INTREQ ; 
 int EINVAL ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

int
ath5k_hw_setup_rx_desc(struct ath5k_hw *ah,
			struct ath5k_desc *desc,
			u32 size, unsigned int flags)
{
	struct ath5k_hw_rx_ctl *rx_ctl;

	rx_ctl = &desc->ud.ds_rx.rx_ctl;

	/*
	 * Clear the descriptor
	 * If we don't clean the status descriptor,
	 * while scanning we get too many results,
	 * most of them virtual, after some secs
	 * of scanning system hangs. M.F.
	*/
	memset(&desc->ud.ds_rx, 0, sizeof(struct ath5k_hw_all_rx_desc));

	if (unlikely(size & ~AR5K_DESC_RX_CTL1_BUF_LEN))
		return -EINVAL;

	/* Setup descriptor */
	rx_ctl->rx_control_1 = size & AR5K_DESC_RX_CTL1_BUF_LEN;

	if (flags & AR5K_RXDESC_INTREQ)
		rx_ctl->rx_control_1 |= AR5K_DESC_RX_CTL1_INTREQ;

	return 0;
}