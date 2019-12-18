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
typedef  int u16 ;

/* Variables and functions */
 scalar_t__ CKSEG1ADDR (scalar_t__) ; 
 scalar_t__ KN01_CSR ; 
 int KN01_CSR_MEMERR ; 
 scalar_t__ KN01_SLOT_BASE ; 
 int cached_kn01_csr ; 
 int /*<<< orphan*/  iob () ; 
 int /*<<< orphan*/  kn01_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void dec_kn01_be_ack(void)
{
	volatile u16 *csr = (void *)CKSEG1ADDR(KN01_SLOT_BASE + KN01_CSR);
	unsigned long flags;

	spin_lock_irqsave(&kn01_lock, flags);

	*csr = cached_kn01_csr | KN01_CSR_MEMERR;	/* Clear bus IRQ. */
	iob();

	spin_unlock_irqrestore(&kn01_lock, flags);
}