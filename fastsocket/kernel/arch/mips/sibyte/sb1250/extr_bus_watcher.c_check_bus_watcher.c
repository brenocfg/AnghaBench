#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int status; int l2_err; int memio_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_BUS_L2_ERRORS ; 
 int /*<<< orphan*/  A_BUS_MEM_IO_ERRORS ; 
 int /*<<< orphan*/  A_SCD_BUS_ERR_STATUS ; 
 int /*<<< orphan*/  A_SCD_BUS_ERR_STATUS_DEBUG ; 
 int /*<<< orphan*/  IOADDR (int /*<<< orphan*/ ) ; 
 TYPE_1__ bw_stats ; 
 int csr_in32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_summary (int,int,int) ; 
 int /*<<< orphan*/  printk (char*) ; 

void check_bus_watcher(void)
{
	u32 status, l2_err, memio_err;

#ifdef CONFIG_SB1_PASS_1_WORKAROUNDS
	/* Destructive read, clears register and interrupt */
	status = csr_in32(IOADDR(A_SCD_BUS_ERR_STATUS));
#else
	/* Use non-destructive register */
	status = csr_in32(IOADDR(A_SCD_BUS_ERR_STATUS_DEBUG));
#endif
	if (!(status & 0x7fffffff)) {
		printk("Using last values reaped by bus watcher driver\n");
		status = bw_stats.status;
		l2_err = bw_stats.l2_err;
		memio_err = bw_stats.memio_err;
	} else {
		l2_err = csr_in32(IOADDR(A_BUS_L2_ERRORS));
		memio_err = csr_in32(IOADDR(A_BUS_MEM_IO_ERRORS));
	}
	if (status & ~(1UL << 31))
		print_summary(status, l2_err, memio_err);
	else
		printk("Bus watcher indicates no error\n");
}