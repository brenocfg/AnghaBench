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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int IADDR2DTEST (void const*) ; 
 scalar_t__ L1_CODE_LENGTH ; 
 scalar_t__ L1_CODE_START ; 
 int /*<<< orphan*/  __builtin_bfin_csync () ; 
 int /*<<< orphan*/  bfin_write_DTEST_COMMAND (int) ; 
 int /*<<< orphan*/  bfin_write_DTEST_DATA0 (int) ; 
 int /*<<< orphan*/  bfin_write_DTEST_DATA1 (int) ; 
 int /*<<< orphan*/  dtest_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void isram_write(const void *addr, uint64_t data)
{
	uint32_t cmd;
	unsigned long flags;

	if (addr >= (void *)(L1_CODE_START + L1_CODE_LENGTH))
		return;

	cmd = IADDR2DTEST(addr) | 2;             /* write */

	/*
	 * Writes to DTEST_DATA[0:1] need to be atomic with write to DTEST_COMMAND
	 * While in exception context - atomicity is guaranteed or double fault
	 */
	spin_lock_irqsave(&dtest_lock, flags);

	bfin_write_DTEST_DATA0(data & 0xFFFFFFFF);
	bfin_write_DTEST_DATA1(data >> 32);

	/* use the builtin, since interrupts are already turned off */
	__builtin_bfin_csync();
	bfin_write_DTEST_COMMAND(cmd);
	__builtin_bfin_csync();

	bfin_write_DTEST_COMMAND(0);
	__builtin_bfin_csync();

	spin_unlock_irqrestore(&dtest_lock, flags);
}