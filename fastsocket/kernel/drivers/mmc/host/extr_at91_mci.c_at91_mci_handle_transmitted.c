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
struct mmc_data {int blocks; } ;
struct mmc_command {struct mmc_data* data; } ;
struct at91mci_host {struct mmc_command* cmd; } ;

/* Variables and functions */
 int AT91_MCI_BLKE ; 
 int /*<<< orphan*/  AT91_MCI_IDR ; 
 int /*<<< orphan*/  AT91_MCI_IER ; 
 int AT91_MCI_NOTBUSY ; 
 int AT91_MCI_TXBUFE ; 
 int /*<<< orphan*/  ATMEL_PDC_PTCR ; 
 int ATMEL_PDC_RXTDIS ; 
 int ATMEL_PDC_TXTDIS ; 
 int /*<<< orphan*/  at91_mci_write (struct at91mci_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static void at91_mci_handle_transmitted(struct at91mci_host *host)
{
	struct mmc_command *cmd;
	struct mmc_data *data;

	pr_debug("Handling the transmit\n");

	/* Disable the transfer */
	at91_mci_write(host, ATMEL_PDC_PTCR, ATMEL_PDC_RXTDIS | ATMEL_PDC_TXTDIS);

	/* Now wait for cmd ready */
	at91_mci_write(host, AT91_MCI_IDR, AT91_MCI_TXBUFE);

	cmd = host->cmd;
	if (!cmd) return;

	data = cmd->data;
	if (!data) return;

	if (cmd->data->blocks > 1) {
		pr_debug("multiple write : wait for BLKE...\n");
		at91_mci_write(host, AT91_MCI_IER, AT91_MCI_BLKE);
	} else
		at91_mci_write(host, AT91_MCI_IER, AT91_MCI_NOTBUSY);
}