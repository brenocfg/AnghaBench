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
typedef  int u8 ;
struct jsm_channel {int ch_c_iflag; int ch_t_tlevel; int ch_r_tlevel; TYPE_2__* ch_neo_uart; scalar_t__ ch_r_watermark; TYPE_1__* ch_bd; } ;
struct TYPE_4__ {int /*<<< orphan*/  ier; int /*<<< orphan*/  rfifo; int /*<<< orphan*/  tfifo; int /*<<< orphan*/  fctr; int /*<<< orphan*/  efr; } ;
struct TYPE_3__ {int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFO ; 
 int IXON ; 
 int /*<<< orphan*/  PARAM ; 
 int UART_17158_EFR_ECB ; 
 int UART_17158_EFR_IXOFF ; 
 int UART_17158_EFR_RTSDTR ; 
 int UART_17158_FCTR_RTS_8DELAY ; 
 int UART_17158_FCTR_TRGD ; 
 int UART_17158_IER_RTSDTR ; 
 int UART_17158_IER_XOFF ; 
 int /*<<< orphan*/  jsm_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void neo_set_no_input_flow_control(struct jsm_channel *ch)
{
	u8 ier, efr;
	ier = readb(&ch->ch_neo_uart->ier);
	efr = readb(&ch->ch_neo_uart->efr);

	jsm_printk(PARAM, INFO, &ch->ch_bd->pci_dev, "Unsetting Input FLOW\n");

	/* Turn off auto RTS flow control */
	ier &= ~(UART_17158_IER_RTSDTR);
	efr &= ~(UART_17158_EFR_RTSDTR);

	/* Turn off auto Xoff flow control */
	ier &= ~(UART_17158_IER_XOFF);
	if (ch->ch_c_iflag & IXON)
		efr &= ~(UART_17158_EFR_IXOFF);
	else
		efr &= ~(UART_17158_EFR_ECB | UART_17158_EFR_IXOFF);

	/* Why? Becuz Exar's spec says we have to zero it out before setting it */
	writeb(0, &ch->ch_neo_uart->efr);

	/* Turn on UART enhanced bits */
	writeb(efr, &ch->ch_neo_uart->efr);

	/* Turn on table D, with 8 char hi/low watermarks */
	writeb((UART_17158_FCTR_TRGD | UART_17158_FCTR_RTS_8DELAY), &ch->ch_neo_uart->fctr);

	ch->ch_r_watermark = 0;

	writeb(16, &ch->ch_neo_uart->tfifo);
	ch->ch_t_tlevel = 16;

	writeb(16, &ch->ch_neo_uart->rfifo);
	ch->ch_r_tlevel = 16;

	writeb(ier, &ch->ch_neo_uart->ier);
}