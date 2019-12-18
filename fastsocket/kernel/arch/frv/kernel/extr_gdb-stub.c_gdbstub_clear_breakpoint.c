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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int dcr; int /*<<< orphan*/ ** dbdr; int /*<<< orphan*/ ** dbmr; int /*<<< orphan*/ * dbar; int /*<<< orphan*/ * ibar; } ;
struct TYPE_3__ {unsigned long addr; unsigned long len; int /*<<< orphan*/ * originsns; } ;

/* Variables and functions */
 unsigned long DCR_DRBE0 ; 
 unsigned long DCR_DRBE1 ; 
 unsigned long DCR_DWBE0 ; 
 unsigned long DCR_DWBE1 ; 
 int DCR_IBE0 ; 
 int DCR_IBE1 ; 
 int DCR_IBE2 ; 
 int DCR_IBE3 ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOSPC ; 
 TYPE_2__* __debug_regs ; 
 unsigned long __get_dbar (int) ; 
 unsigned long __get_dbmr0 (int) ; 
 unsigned long __get_dbmr1 (int) ; 
 unsigned long __get_ibar (int) ; 
 TYPE_1__* gdbstub_bkpts ; 
 int /*<<< orphan*/  gdbstub_write_dword (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

int gdbstub_clear_breakpoint(unsigned long type, unsigned long addr, unsigned long len)
{
	unsigned long tmp;
	int bkpt, loop;

	union {
		struct {
			unsigned long mask0, mask1;
		};
		uint8_t bytes[8];
	} dbmr;

	//gdbstub_printk("clearbkpt(%ld,%08lx,%ld)\n", type, addr, len);

	switch (type) {
		/* clear software breakpoint */
	case 0:
		for (bkpt = 255; bkpt >= 0; bkpt--)
			if (gdbstub_bkpts[bkpt].addr == addr && gdbstub_bkpts[bkpt].len == len)
				break;
		if (bkpt < 0)
			return -ENOENT;

		gdbstub_bkpts[bkpt].addr = 0;

		for (loop = 0; loop < len/4; loop++)
			if (!gdbstub_write_dword(&((uint32_t *) addr)[loop],
						 gdbstub_bkpts[bkpt].originsns[loop]))
				return -EFAULT;
		return 0;

		/* clear hardware breakpoint */
	case 1:
		if (addr & 3 || len != 4)
			return -EINVAL;

#define __get_ibar(X) ({ unsigned long x; asm volatile("movsg ibar"#X",%0" : "=r"(x)); x; })

		if (__debug_regs->dcr & DCR_IBE0 && __get_ibar(0) == addr) {
			//gdbstub_printk("clear h/w break 0: %08lx\n", addr);
			__debug_regs->dcr &= ~DCR_IBE0;
			__debug_regs->ibar[0] = 0;
			asm volatile("movgs gr0,ibar0");
			return 0;
		}

		if (__debug_regs->dcr & DCR_IBE1 && __get_ibar(1) == addr) {
			//gdbstub_printk("clear h/w break 1: %08lx\n", addr);
			__debug_regs->dcr &= ~DCR_IBE1;
			__debug_regs->ibar[1] = 0;
			asm volatile("movgs gr0,ibar1");
			return 0;
		}

		if (__debug_regs->dcr & DCR_IBE2 && __get_ibar(2) == addr) {
			//gdbstub_printk("clear h/w break 2: %08lx\n", addr);
			__debug_regs->dcr &= ~DCR_IBE2;
			__debug_regs->ibar[2] = 0;
			asm volatile("movgs gr0,ibar2");
			return 0;
		}

		if (__debug_regs->dcr & DCR_IBE3 && __get_ibar(3) == addr) {
			//gdbstub_printk("clear h/w break 3: %08lx\n", addr);
			__debug_regs->dcr &= ~DCR_IBE3;
			__debug_regs->ibar[3] = 0;
			asm volatile("movgs gr0,ibar3");
			return 0;
		}

		return -EINVAL;

		/* clear data read/write/access watchpoint */
	case 2:
	case 3:
	case 4:
		if ((addr & ~7) != ((addr + len - 1) & ~7))
			return -EINVAL;

		tmp = addr & 7;

		memset(dbmr.bytes, 0xff, sizeof(dbmr.bytes));
		for (loop = 0; loop < len; loop++)
			dbmr.bytes[tmp + loop] = 0;

		addr &= ~7;

#define __get_dbar(X) ({ unsigned long x; asm volatile("movsg dbar"#X",%0" : "=r"(x)); x; })
#define __get_dbmr0(X) ({ unsigned long x; asm volatile("movsg dbmr"#X"0,%0" : "=r"(x)); x; })
#define __get_dbmr1(X) ({ unsigned long x; asm volatile("movsg dbmr"#X"1,%0" : "=r"(x)); x; })

		/* consider DBAR 0 */
		tmp = type==2 ? DCR_DWBE0 : type==3 ? DCR_DRBE0 : DCR_DRBE0|DCR_DWBE0;

		if ((__debug_regs->dcr & (DCR_DRBE0|DCR_DWBE0)) != tmp ||
		    __get_dbar(0) != addr ||
		    __get_dbmr0(0) != dbmr.mask0 ||
		    __get_dbmr1(0) != dbmr.mask1)
			goto skip_dbar0;

		//gdbstub_printk("clear h/w watchpoint 0 type %ld: %08lx\n", type, addr);
		__debug_regs->dcr &= ~(DCR_DRBE0|DCR_DWBE0);
		__debug_regs->dbar[0] = 0;
		__debug_regs->dbmr[0][0] = 0;
		__debug_regs->dbmr[0][1] = 0;
		__debug_regs->dbdr[0][0] = 0;
		__debug_regs->dbdr[0][1] = 0;

		asm volatile("	movgs	gr0,dbar0	\n"
			     "	movgs	gr0,dbmr00	\n"
			     "	movgs	gr0,dbmr01	\n"
			     "	movgs	gr0,dbdr00	\n"
			     "	movgs	gr0,dbdr01	\n");
		return 0;

	skip_dbar0:
		/* consider DBAR 0 */
		tmp = type==2 ? DCR_DWBE1 : type==3 ? DCR_DRBE1 : DCR_DRBE1|DCR_DWBE1;

		if ((__debug_regs->dcr & (DCR_DRBE1|DCR_DWBE1)) != tmp ||
		    __get_dbar(1) != addr ||
		    __get_dbmr0(1) != dbmr.mask0 ||
		    __get_dbmr1(1) != dbmr.mask1)
			goto skip_dbar1;

		//gdbstub_printk("clear h/w watchpoint 1 type %ld: %08lx\n", type, addr);
		__debug_regs->dcr &= ~(DCR_DRBE1|DCR_DWBE1);
		__debug_regs->dbar[1] = 0;
		__debug_regs->dbmr[1][0] = 0;
		__debug_regs->dbmr[1][1] = 0;
		__debug_regs->dbdr[1][0] = 0;
		__debug_regs->dbdr[1][1] = 0;

		asm volatile("	movgs	gr0,dbar1	\n"
			     "	movgs	gr0,dbmr10	\n"
			     "	movgs	gr0,dbmr11	\n"
			     "	movgs	gr0,dbdr10	\n"
			     "	movgs	gr0,dbdr11	\n");
		return 0;

	skip_dbar1:
		return -ENOSPC;

	default:
		return -EINVAL;
	}
}