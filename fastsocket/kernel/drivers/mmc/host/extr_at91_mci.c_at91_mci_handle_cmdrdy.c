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
struct at91mci_host {int flags; TYPE_2__* cmd; } ;
struct TYPE_4__ {TYPE_1__* data; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int AT91_MCI_BLKE ; 
 int /*<<< orphan*/  AT91_MCI_IER ; 
 int AT91_MCI_NOTBUSY ; 
 int AT91_MCI_TXBUFE ; 
 int /*<<< orphan*/  ATMEL_PDC_PTCR ; 
 int ATMEL_PDC_TXTEN ; 
 int FL_SENT_STOP ; 
 int MMC_DATA_WRITE ; 
 int /*<<< orphan*/  at91_mci_write (struct at91mci_host*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int at91_mci_handle_cmdrdy(struct at91mci_host *host)
{
	if (!host->cmd)
		return 1;
	else if (!host->cmd->data) {
		if (host->flags & FL_SENT_STOP) {
			/*After multi block write, we must wait for NOTBUSY*/
			at91_mci_write(host, AT91_MCI_IER, AT91_MCI_NOTBUSY);
		} else return 1;
	} else if (host->cmd->data->flags & MMC_DATA_WRITE) {
		/*After sendding multi-block-write command, start DMA transfer*/
		at91_mci_write(host, AT91_MCI_IER, AT91_MCI_TXBUFE | AT91_MCI_BLKE);
		at91_mci_write(host, ATMEL_PDC_PTCR, ATMEL_PDC_TXTEN);
	}

	/* command not completed, have to wait */
	return 0;
}