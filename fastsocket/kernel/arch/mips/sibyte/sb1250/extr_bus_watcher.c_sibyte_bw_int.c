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
struct bw_stats_struct {unsigned long l2_err; unsigned long memio_err; int /*<<< orphan*/  bus_error; int /*<<< orphan*/  mem_bad_d; int /*<<< orphan*/  mem_cor_d; int /*<<< orphan*/  l2_bad_t; int /*<<< orphan*/  l2_cor_t; int /*<<< orphan*/  l2_bad_d; int /*<<< orphan*/  l2_cor_d; scalar_t__ status_printed; void* status; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_BUS_L2_ERRORS ; 
 int /*<<< orphan*/  A_BUS_MEM_IO_ERRORS ; 
 int /*<<< orphan*/  A_SCD_BUS_ERR_STATUS ; 
 int /*<<< orphan*/  A_SCD_TRACE_CFG ; 
 int /*<<< orphan*/  A_SCD_TRACE_READ ; 
 scalar_t__ G_SCD_L2ECC_BAD_D (unsigned long) ; 
 scalar_t__ G_SCD_L2ECC_BAD_T (unsigned long) ; 
 scalar_t__ G_SCD_L2ECC_CORR_D (unsigned long) ; 
 scalar_t__ G_SCD_L2ECC_CORR_T (unsigned long) ; 
 scalar_t__ G_SCD_MEM_BUSERR (unsigned long) ; 
 scalar_t__ G_SCD_MEM_ECC_BAD (unsigned long) ; 
 scalar_t__ G_SCD_MEM_ECC_CORR (unsigned long) ; 
 int /*<<< orphan*/  IOADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  M_SCD_TRACE_CFG_FREEZE ; 
 int /*<<< orphan*/  M_SCD_TRACE_CFG_RESET ; 
 int /*<<< orphan*/  M_SCD_TRACE_CFG_START ; 
 int /*<<< orphan*/  M_SCD_TRACE_CFG_START_READ ; 
 scalar_t__ __raw_readq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bw_print_buffer (char*,struct bw_stats_struct*) ; 
 void* csr_in32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csr_out32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static irqreturn_t sibyte_bw_int(int irq, void *data)
{
	struct bw_stats_struct *stats = data;
	unsigned long cntr;
#ifdef CONFIG_SIBYTE_BW_TRACE
	int i;
#endif
#ifndef CONFIG_PROC_FS
	char bw_buf[1024];
#endif

#ifdef CONFIG_SIBYTE_BW_TRACE
	csr_out32(M_SCD_TRACE_CFG_FREEZE, IOADDR(A_SCD_TRACE_CFG));
	csr_out32(M_SCD_TRACE_CFG_START_READ, IOADDR(A_SCD_TRACE_CFG));

	for (i=0; i<256*6; i++)
		printk("%016llx\n",
		       (long long)__raw_readq(IOADDR(A_SCD_TRACE_READ)));

	csr_out32(M_SCD_TRACE_CFG_RESET, IOADDR(A_SCD_TRACE_CFG));
	csr_out32(M_SCD_TRACE_CFG_START, IOADDR(A_SCD_TRACE_CFG));
#endif

	/* Destructive read, clears register and interrupt */
	stats->status = csr_in32(IOADDR(A_SCD_BUS_ERR_STATUS));
	stats->status_printed = 0;

	stats->l2_err = cntr = csr_in32(IOADDR(A_BUS_L2_ERRORS));
	stats->l2_cor_d += G_SCD_L2ECC_CORR_D(cntr);
	stats->l2_bad_d += G_SCD_L2ECC_BAD_D(cntr);
	stats->l2_cor_t += G_SCD_L2ECC_CORR_T(cntr);
	stats->l2_bad_t += G_SCD_L2ECC_BAD_T(cntr);
	csr_out32(0, IOADDR(A_BUS_L2_ERRORS));

	stats->memio_err = cntr = csr_in32(IOADDR(A_BUS_MEM_IO_ERRORS));
	stats->mem_cor_d += G_SCD_MEM_ECC_CORR(cntr);
	stats->mem_bad_d += G_SCD_MEM_ECC_BAD(cntr);
	stats->bus_error += G_SCD_MEM_BUSERR(cntr);
	csr_out32(0, IOADDR(A_BUS_MEM_IO_ERRORS));

#ifndef CONFIG_PROC_FS
	bw_print_buffer(bw_buf, stats);
	printk(bw_buf);
#endif

	return IRQ_HANDLED;
}