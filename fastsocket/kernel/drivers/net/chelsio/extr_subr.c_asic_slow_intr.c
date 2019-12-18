#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int slow_intr_mask; scalar_t__ regs; int /*<<< orphan*/  espi; int /*<<< orphan*/  tp; int /*<<< orphan*/  sge; } ;
typedef  TYPE_1__ adapter_t ;

/* Variables and functions */
 scalar_t__ A_PL_CAUSE ; 
 int F_PL_INTR_ESPI ; 
 int F_PL_INTR_EXT ; 
 int F_PL_INTR_PCIX ; 
 int F_PL_INTR_SGE_ERR ; 
 int F_PL_INTR_TP ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  t1_elmer0_ext_intr (TYPE_1__*) ; 
 int /*<<< orphan*/  t1_espi_intr_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t1_pci_intr_handler (TYPE_1__*) ; 
 int /*<<< orphan*/  t1_sge_intr_error_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t1_tp_intr_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int asic_slow_intr(adapter_t *adapter)
{
	u32 cause = readl(adapter->regs + A_PL_CAUSE);

	cause &= adapter->slow_intr_mask;
	if (!cause)
		return 0;
	if (cause & F_PL_INTR_SGE_ERR)
		t1_sge_intr_error_handler(adapter->sge);
	if (cause & F_PL_INTR_TP)
		t1_tp_intr_handler(adapter->tp);
	if (cause & F_PL_INTR_ESPI)
		t1_espi_intr_handler(adapter->espi);
	if (cause & F_PL_INTR_PCIX)
		t1_pci_intr_handler(adapter);
	if (cause & F_PL_INTR_EXT)
		t1_elmer0_ext_intr(adapter);

	/* Clear the interrupts just processed. */
	writel(cause, adapter->regs + A_PL_CAUSE);
	readl(adapter->regs + A_PL_CAUSE); /* flush writes */
	return 1;
}