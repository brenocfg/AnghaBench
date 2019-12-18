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
typedef  int u8 ;
struct mce {int status; int addr; void* misc; } ;

/* Variables and functions */
 int MCI_MISC_ADDR_LSB (void*) ; 
 int MCI_STATUS_ADDRV ; 
 int MCI_STATUS_MISCV ; 
 int /*<<< orphan*/  MSR_IA32_MCx_ADDR (int) ; 
 int /*<<< orphan*/  MSR_IA32_MCx_MISC (int) ; 
 void* mce_rdmsrl (int /*<<< orphan*/ ) ; 
 scalar_t__ mce_ser ; 

__attribute__((used)) static void mce_read_aux(struct mce *m, int i)
{
	if (m->status & MCI_STATUS_MISCV)
		m->misc = mce_rdmsrl(MSR_IA32_MCx_MISC(i));
	if (m->status & MCI_STATUS_ADDRV) {
		m->addr = mce_rdmsrl(MSR_IA32_MCx_ADDR(i));

		/*
		 * Mask the reported address by the reported granularity.
		 */
		if (mce_ser && (m->status & MCI_STATUS_MISCV)) {
			u8 shift = MCI_MISC_ADDR_LSB(m->misc);
			m->addr >>= shift;
			m->addr <<= shift;
		}
	}
}