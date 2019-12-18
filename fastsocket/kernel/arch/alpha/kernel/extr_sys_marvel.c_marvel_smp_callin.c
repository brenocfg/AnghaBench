#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct io7 {TYPE_6__* csrs; } ;
struct TYPE_11__ {int /*<<< orphan*/  csr; } ;
struct TYPE_10__ {int /*<<< orphan*/  csr; } ;
struct TYPE_9__ {int /*<<< orphan*/  csr; } ;
struct TYPE_8__ {int /*<<< orphan*/  csr; } ;
struct TYPE_7__ {int /*<<< orphan*/  csr; } ;
struct TYPE_12__ {TYPE_5__ HEI_CTL; TYPE_4__ STV_CTL; TYPE_3__ CRD_CTL; TYPE_2__ HPI_CTL; TYPE_1__ HLT_CTL; } ;

/* Variables and functions */
 int hard_smp_processor_id () ; 
 int /*<<< orphan*/  io7_redirect_irq (struct io7*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  io7_redirect_one_lsi (struct io7*,int,int) ; 
 int /*<<< orphan*/  io7_redirect_one_msi (struct io7*,unsigned int,int) ; 
 struct io7* marvel_find_io7 (int) ; 
 int /*<<< orphan*/  printk (char*,int) ; 

__attribute__((used)) static void
marvel_smp_callin(void)
{
	int cpuid = hard_smp_processor_id();
	struct io7 *io7 = marvel_find_io7(cpuid);
	unsigned int i;

	if (!io7)
		return;

	/* 
	 * There is a local IO7 - redirect all of its interrupts here.
	 */
	printk("Redirecting IO7 interrupts to local CPU at PE %u\n", cpuid);

	/* Redirect the error IRQS here.  */
	io7_redirect_irq(io7, &io7->csrs->HLT_CTL.csr, cpuid);
	io7_redirect_irq(io7, &io7->csrs->HPI_CTL.csr, cpuid);
	io7_redirect_irq(io7, &io7->csrs->CRD_CTL.csr, cpuid);
	io7_redirect_irq(io7, &io7->csrs->STV_CTL.csr, cpuid);
	io7_redirect_irq(io7, &io7->csrs->HEI_CTL.csr, cpuid);

	/* Redirect the implemented LSIs here.  */
	for (i = 0; i < 0x60; ++i) 
		io7_redirect_one_lsi(io7, i, cpuid);

	io7_redirect_one_lsi(io7, 0x74, cpuid);
	io7_redirect_one_lsi(io7, 0x75, cpuid);

	/* Redirect the MSIs here.  */
	for (i = 0; i < 16; ++i)
		io7_redirect_one_msi(io7, i, cpuid);
}