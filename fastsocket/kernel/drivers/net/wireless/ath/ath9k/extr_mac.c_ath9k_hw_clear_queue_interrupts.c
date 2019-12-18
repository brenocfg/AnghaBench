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
typedef  int u32 ;
struct ath_hw {int txok_interrupt_mask; int txerr_interrupt_mask; int txdesc_interrupt_mask; int txeol_interrupt_mask; int txurn_interrupt_mask; } ;

/* Variables and functions */

__attribute__((used)) static void ath9k_hw_clear_queue_interrupts(struct ath_hw *ah, u32 q)
{
	ah->txok_interrupt_mask &= ~(1 << q);
	ah->txerr_interrupt_mask &= ~(1 << q);
	ah->txdesc_interrupt_mask &= ~(1 << q);
	ah->txeol_interrupt_mask &= ~(1 << q);
	ah->txurn_interrupt_mask &= ~(1 << q);
}