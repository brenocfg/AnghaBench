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
struct at91mci_host {TYPE_1__* board; } ;
struct TYPE_2__ {unsigned int slot_b; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_MCI_CR ; 
 unsigned int AT91_MCI_DTOCYC ; 
 unsigned int AT91_MCI_DTOMUL_1M ; 
 int /*<<< orphan*/  AT91_MCI_DTOR ; 
 int /*<<< orphan*/  AT91_MCI_IDR ; 
 unsigned int AT91_MCI_MCIEN ; 
 int /*<<< orphan*/  AT91_MCI_MR ; 
 int AT91_MCI_PDCMODE ; 
 unsigned int AT91_MCI_RDPROOF ; 
 int /*<<< orphan*/  AT91_MCI_SDCR ; 
 unsigned int AT91_MCI_WRPROOF ; 
 int /*<<< orphan*/  at91_mci_write (struct at91mci_host*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ cpu_is_at91sam9260 () ; 
 scalar_t__ cpu_is_at91sam9263 () ; 

__attribute__((used)) static void at91_mci_enable(struct at91mci_host *host)
{
	unsigned int mr;

	at91_mci_write(host, AT91_MCI_CR, AT91_MCI_MCIEN);
	at91_mci_write(host, AT91_MCI_IDR, 0xffffffff);
	at91_mci_write(host, AT91_MCI_DTOR, AT91_MCI_DTOMUL_1M | AT91_MCI_DTOCYC);
	mr = AT91_MCI_PDCMODE | 0x34a;

	if (cpu_is_at91sam9260() || cpu_is_at91sam9263())
		mr |= AT91_MCI_RDPROOF | AT91_MCI_WRPROOF;

	at91_mci_write(host, AT91_MCI_MR, mr);

	/* use Slot A or B (only one at same time) */
	at91_mci_write(host, AT91_MCI_SDCR, host->board->slot_b);
}