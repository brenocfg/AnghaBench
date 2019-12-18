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

/* Variables and functions */
 int /*<<< orphan*/  DART_CNTL ; 
 unsigned int DART_CNTL_U3_FLUSHTLB ; 
 unsigned int DART_CNTL_U4_FLUSHTLB ; 
 unsigned int DART_IN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DART_OUT (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  DBG (char*) ; 
 scalar_t__ dart_is_u4 ; 
 int /*<<< orphan*/  invalidate_lock ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void dart_tlb_invalidate_all(void)
{
	unsigned long l = 0;
	unsigned int reg, inv_bit;
	unsigned long limit;
	unsigned long flags;

	spin_lock_irqsave(&invalidate_lock, flags);

	DBG("dart: flush\n");

	/* To invalidate the DART, set the DARTCNTL_FLUSHTLB bit in the
	 * control register and wait for it to clear.
	 *
	 * Gotcha: Sometimes, the DART won't detect that the bit gets
	 * set. If so, clear it and set it again.
	 */

	limit = 0;

	inv_bit = dart_is_u4 ? DART_CNTL_U4_FLUSHTLB : DART_CNTL_U3_FLUSHTLB;
retry:
	l = 0;
	reg = DART_IN(DART_CNTL);
	reg |= inv_bit;
	DART_OUT(DART_CNTL, reg);

	while ((DART_IN(DART_CNTL) & inv_bit) && l < (1L << limit))
		l++;
	if (l == (1L << limit)) {
		if (limit < 4) {
			limit++;
			reg = DART_IN(DART_CNTL);
			reg &= ~inv_bit;
			DART_OUT(DART_CNTL, reg);
			goto retry;
		} else
			panic("DART: TLB did not flush after waiting a long "
			      "time. Buggy U3 ?");
	}

	spin_unlock_irqrestore(&invalidate_lock, flags);
}