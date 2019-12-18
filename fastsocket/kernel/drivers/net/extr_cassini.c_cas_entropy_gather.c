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
typedef  int /*<<< orphan*/  uint64_t ;
struct cas {int cas_flags; scalar_t__ regs; } ;

/* Variables and functions */
 int CAS_FLAG_ENTROPY_DEV ; 
 scalar_t__ REG_ENTROPY_IV ; 
 int /*<<< orphan*/  batch_entropy_store (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static inline void cas_entropy_gather(struct cas *cp)
{
#ifdef USE_ENTROPY_DEV
	if ((cp->cas_flags & CAS_FLAG_ENTROPY_DEV) == 0)
		return;

	batch_entropy_store(readl(cp->regs + REG_ENTROPY_IV),
			    readl(cp->regs + REG_ENTROPY_IV),
			    sizeof(uint64_t)*8);
#endif
}