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
typedef  int u64 ;

/* Variables and functions */
 int EXTRACT (int,int /*<<< orphan*/ ) ; 
 int MCHK_DISPOSITION_DISMISS ; 
 int MCHK_DISPOSITION_REPORT ; 
 int MCHK_DISPOSITION_UNKNOWN_ERROR ; 
 int /*<<< orphan*/  TITAN__PCHIP_PERROR__ADDR ; 
 int TITAN__PCHIP_PERROR__APE ; 
 int /*<<< orphan*/  TITAN__PCHIP_PERROR__CMD ; 
 int TITAN__PCHIP_PERROR__DAC ; 
 int TITAN__PCHIP_PERROR__DCRTO ; 
 int TITAN__PCHIP_PERROR__DPE ; 
 int TITAN__PCHIP_PERROR__ERRMASK ; 
 int TITAN__PCHIP_PERROR__IPTPR ; 
 int TITAN__PCHIP_PERROR__IPTPW ; 
 int TITAN__PCHIP_PERROR__LOST ; 
 int TITAN__PCHIP_PERROR__MWIN ; 
 int TITAN__PCHIP_PERROR__NDS ; 
 int TITAN__PCHIP_PERROR__PERR ; 
 int TITAN__PCHIP_PERROR__SERR ; 
 int TITAN__PCHIP_PERROR__SGE ; 
 int TITAN__PCHIP_PERROR__TA ; 
 int /*<<< orphan*/  err_print_prefix ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int 
titan_parse_p_perror(int which, int port, u64 perror, int print)
{
	int cmd;
	unsigned long addr;
	int status = MCHK_DISPOSITION_REPORT;

#ifdef CONFIG_VERBOSE_MCHECK
	char *perror_cmd[] = { "Interrupt Acknowledge", "Special Cycle",
			       "I/O Read",	       	"I/O Write",
			       "Reserved",	       	"Reserved",
			       "Memory Read",		"Memory Write",
			       "Reserved",		"Reserved",
			       "Configuration Read",	"Configuration Write",
			       "Memory Read Multiple",	"Dual Address Cycle",
			       "Memory Read Line","Memory Write and Invalidate"
	};
#endif /* CONFIG_VERBOSE_MCHECK */

#define TITAN__PCHIP_PERROR__LOST	(1UL << 0)
#define TITAN__PCHIP_PERROR__SERR	(1UL << 1)
#define TITAN__PCHIP_PERROR__PERR	(1UL << 2)
#define TITAN__PCHIP_PERROR__DCRTO	(1UL << 3)
#define TITAN__PCHIP_PERROR__SGE	(1UL << 4)
#define TITAN__PCHIP_PERROR__APE	(1UL << 5)
#define TITAN__PCHIP_PERROR__TA		(1UL << 6)
#define TITAN__PCHIP_PERROR__DPE	(1UL << 7)
#define TITAN__PCHIP_PERROR__NDS	(1UL << 8)
#define TITAN__PCHIP_PERROR__IPTPR	(1UL << 9)
#define TITAN__PCHIP_PERROR__IPTPW	(1UL << 10)
#define TITAN__PCHIP_PERROR__ERRMASK	(TITAN__PCHIP_PERROR__LOST |	\
					 TITAN__PCHIP_PERROR__SERR |	\
					 TITAN__PCHIP_PERROR__PERR |	\
					 TITAN__PCHIP_PERROR__DCRTO |	\
					 TITAN__PCHIP_PERROR__SGE |	\
					 TITAN__PCHIP_PERROR__APE |	\
					 TITAN__PCHIP_PERROR__TA |	\
					 TITAN__PCHIP_PERROR__DPE |	\
					 TITAN__PCHIP_PERROR__NDS |	\
					 TITAN__PCHIP_PERROR__IPTPR |	\
					 TITAN__PCHIP_PERROR__IPTPW)
#define TITAN__PCHIP_PERROR__DAC	(1UL << 47)
#define TITAN__PCHIP_PERROR__MWIN	(1UL << 48)
#define TITAN__PCHIP_PERROR__CMD__S	(52)
#define TITAN__PCHIP_PERROR__CMD__M	(0x0f)
#define TITAN__PCHIP_PERROR__ADDR__S	(14)
#define TITAN__PCHIP_PERROR__ADDR__M	(0x1fffffffful)

	if (!(perror & TITAN__PCHIP_PERROR__ERRMASK))
		return MCHK_DISPOSITION_UNKNOWN_ERROR;

	cmd = EXTRACT(perror, TITAN__PCHIP_PERROR__CMD);
	addr = EXTRACT(perror, TITAN__PCHIP_PERROR__ADDR) << 2;

	/*
	 * Initializing the BIOS on a video card on a bus without
	 * a south bridge (subtractive decode agent) can result in 
	 * master aborts as the BIOS probes the capabilities of the
	 * card. XFree86 does such initialization. If the error
	 * is a master abort (No DevSel as PCI Master) and the command
	 * is an I/O read or write below the address where we start
	 * assigning PCI I/O spaces (SRM uses 0x1000), then mark the
	 * error as dismissable so starting XFree86 doesn't result
	 * in a series of uncorrectable errors being reported. Also
	 * dismiss master aborts to VGA frame buffer space
	 * (0xA0000 - 0xC0000) and legacy BIOS space (0xC0000 - 0x100000)
	 * for the same reason.
	 *
	 * Also mark the error dismissible if it looks like the right
	 * error but only the Lost bit is set. Since the BIOS initialization
	 * can cause multiple master aborts and the error interrupt can
	 * be handled on a different CPU than the BIOS code is run on,
	 * it is possible for a second master abort to occur between the
	 * time the PALcode reads PERROR and the time it writes PERROR
	 * to acknowledge the error. If this timing happens, a second
	 * error will be signalled after the first, and if no additional
	 * errors occur, will look like a Lost error with no additional 
	 * errors on the same transaction as the previous error.
	 */
	if (((perror & TITAN__PCHIP_PERROR__NDS) || 
	     ((perror & TITAN__PCHIP_PERROR__ERRMASK) == 
	      TITAN__PCHIP_PERROR__LOST)) &&
	    ((((cmd & 0xE) == 2) && (addr < 0x1000)) ||
	     (((cmd & 0xE) == 6) && (addr >= 0xA0000) && (addr < 0x100000)))) {
		status = MCHK_DISPOSITION_DISMISS;
	}

#ifdef CONFIG_VERBOSE_MCHECK
	if (!print) 
		return status;

	printk("%s  PChip %d %cPERROR: %016llx\n",
	       err_print_prefix, which, 
	       port ? 'A' : 'G', perror);
	if (perror & TITAN__PCHIP_PERROR__IPTPW)
		printk("%s    Invalid Peer-to-Peer Write\n", err_print_prefix);
	if (perror & TITAN__PCHIP_PERROR__IPTPR)
		printk("%s    Invalid Peer-to-Peer Read\n", err_print_prefix);
	if (perror & TITAN__PCHIP_PERROR__NDS)
		printk("%s    No DEVSEL as PCI Master [Master Abort]\n",
		       err_print_prefix);
	if (perror & TITAN__PCHIP_PERROR__DPE)
		printk("%s    Data Parity Error\n", err_print_prefix);
	if (perror & TITAN__PCHIP_PERROR__TA)
		printk("%s    Target Abort\n", err_print_prefix);
	if (perror & TITAN__PCHIP_PERROR__APE)
		printk("%s    Address Parity Error\n", err_print_prefix);
	if (perror & TITAN__PCHIP_PERROR__SGE)
		printk("%s    Scatter-Gather Error, Invalid PTE\n", 
		       err_print_prefix);
	if (perror & TITAN__PCHIP_PERROR__DCRTO)
		printk("%s    Delayed-Completion Retry Timeout\n", 
		       err_print_prefix);
	if (perror & TITAN__PCHIP_PERROR__PERR)
		printk("%s    PERR Asserted\n", err_print_prefix);
	if (perror & TITAN__PCHIP_PERROR__SERR)
		printk("%s    SERR Asserted\n", err_print_prefix);
	if (perror & TITAN__PCHIP_PERROR__LOST)
		printk("%s    Lost Error\n", err_print_prefix);
	printk("%s      Command: 0x%x - %s\n"
		 "      Address: 0x%lx\n",
	       err_print_prefix,
	       cmd, perror_cmd[cmd],
	       addr);
	if (perror & TITAN__PCHIP_PERROR__DAC)
		printk("%s      Dual Address Cycle\n", err_print_prefix);
	if (perror & TITAN__PCHIP_PERROR__MWIN)
		printk("%s      Hit in Monster Window\n", err_print_prefix);
#endif /* CONFIG_VERBOSE_MCHECK */

	return status;
}