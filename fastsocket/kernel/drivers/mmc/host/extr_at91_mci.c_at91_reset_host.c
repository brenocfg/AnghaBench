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
typedef  int u32 ;
struct at91mci_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_MCI_CR ; 
 int /*<<< orphan*/  AT91_MCI_DTOR ; 
 int /*<<< orphan*/  AT91_MCI_IDR ; 
 int /*<<< orphan*/  AT91_MCI_IER ; 
 int /*<<< orphan*/  AT91_MCI_IMR ; 
 int AT91_MCI_MCIDIS ; 
 int AT91_MCI_MCIEN ; 
 int /*<<< orphan*/  AT91_MCI_MR ; 
 int /*<<< orphan*/  AT91_MCI_SDCR ; 
 int /*<<< orphan*/  AT91_MCI_SR ; 
 int AT91_MCI_SWRST ; 
 int at91_mci_read (struct at91mci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_mci_write (struct at91mci_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static void at91_reset_host(struct at91mci_host *host)
{
	unsigned long flags;
	u32 mr;
	u32 sdcr;
	u32 dtor;
	u32 imr;

	local_irq_save(flags);
	imr = at91_mci_read(host, AT91_MCI_IMR);

	at91_mci_write(host, AT91_MCI_IDR, 0xffffffff);

	/* save current state */
	mr = at91_mci_read(host, AT91_MCI_MR) & 0x7fff;
	sdcr = at91_mci_read(host, AT91_MCI_SDCR);
	dtor = at91_mci_read(host, AT91_MCI_DTOR);

	/* reset the controller */
	at91_mci_write(host, AT91_MCI_CR, AT91_MCI_MCIDIS | AT91_MCI_SWRST);

	/* restore state */
	at91_mci_write(host, AT91_MCI_CR, AT91_MCI_MCIEN);
	at91_mci_write(host, AT91_MCI_MR, mr);
	at91_mci_write(host, AT91_MCI_SDCR, sdcr);
	at91_mci_write(host, AT91_MCI_DTOR, dtor);
	at91_mci_write(host, AT91_MCI_IER, imr);

	/* make sure sdio interrupts will fire */
	at91_mci_read(host, AT91_MCI_SR);

	local_irq_restore(flags);
}