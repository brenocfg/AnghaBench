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

/* Variables and functions */
 int /*<<< orphan*/  AP ; 
 int /*<<< orphan*/  ASID ; 
 int /*<<< orphan*/  B ; 
 int /*<<< orphan*/  DRP ; 
 int /*<<< orphan*/  G ; 
 int /*<<< orphan*/  MMUCR ; 
 int /*<<< orphan*/  PFN ; 
 int SYSREG_BFEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSREG_BFINS (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ ; 
 int /*<<< orphan*/  TLBEHI ; 
 int /*<<< orphan*/  TLBEHI_V ; 
 int /*<<< orphan*/  TLBELO ; 
 int /*<<< orphan*/  TLBELO_C ; 
 int /*<<< orphan*/  TLBELO_D ; 
 int /*<<< orphan*/  VPN ; 
 int /*<<< orphan*/  W ; 
 int /*<<< orphan*/  __builtin_tlbr () ; 
 int /*<<< orphan*/  cpu_sync_pipeline () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  printk (char*,unsigned int,char,char,int,int,int,int,int,char,char,char,char) ; 
 int /*<<< orphan*/  sysreg_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysreg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void show_dtlb_entry(unsigned int index)
{
	u32 tlbehi, tlbehi_save, tlbelo, mmucr, mmucr_save;
	unsigned long flags;

	local_irq_save(flags);
	mmucr_save = sysreg_read(MMUCR);
	tlbehi_save = sysreg_read(TLBEHI);
	mmucr = SYSREG_BFINS(DRP, index, mmucr_save);
	sysreg_write(MMUCR, mmucr);

	__builtin_tlbr();
	cpu_sync_pipeline();

	tlbehi = sysreg_read(TLBEHI);
	tlbelo = sysreg_read(TLBELO);

	printk("%2u: %c %c %02x   %05x %05x %o  %o  %c %c %c %c\n",
	       index,
	       SYSREG_BFEXT(TLBEHI_V, tlbehi) ? '1' : '0',
	       SYSREG_BFEXT(G, tlbelo) ? '1' : '0',
	       SYSREG_BFEXT(ASID, tlbehi),
	       SYSREG_BFEXT(VPN, tlbehi) >> 2,
	       SYSREG_BFEXT(PFN, tlbelo) >> 2,
	       SYSREG_BFEXT(AP, tlbelo),
	       SYSREG_BFEXT(SZ, tlbelo),
	       SYSREG_BFEXT(TLBELO_C, tlbelo) ? 'C' : ' ',
	       SYSREG_BFEXT(B, tlbelo) ? 'B' : ' ',
	       SYSREG_BFEXT(W, tlbelo) ? 'W' : ' ',
	       SYSREG_BFEXT(TLBELO_D, tlbelo) ? 'D' : ' ');

	sysreg_write(MMUCR, mmucr_save);
	sysreg_write(TLBEHI, tlbehi_save);
	cpu_sync_pipeline();
	local_irq_restore(flags);
}