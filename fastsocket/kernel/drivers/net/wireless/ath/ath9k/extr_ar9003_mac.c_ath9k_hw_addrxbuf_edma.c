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
typedef  int /*<<< orphan*/  u32 ;
struct ath_hw {int dummy; } ;
typedef  enum ath9k_rx_qtype { ____Placeholder_ath9k_rx_qtype } ath9k_rx_qtype ;

/* Variables and functions */
 int /*<<< orphan*/  AR_HP_RXDP ; 
 int /*<<< orphan*/  AR_LP_RXDP ; 
 int ATH9K_RX_QUEUE_HP ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ath9k_hw_addrxbuf_edma(struct ath_hw *ah, u32 rxdp,
			    enum ath9k_rx_qtype qtype)
{
	if (qtype == ATH9K_RX_QUEUE_HP)
		REG_WRITE(ah, AR_HP_RXDP, rxdp);
	else
		REG_WRITE(ah, AR_LP_RXDP, rxdp);
}