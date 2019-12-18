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
struct jsm_channel {int ch_flags; int /*<<< orphan*/  ch_lock; TYPE_2__* ch_bd; TYPE_1__* ch_neo_uart; } ;
struct TYPE_4__ {int /*<<< orphan*/  pci_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  lcr; } ;

/* Variables and functions */
 int CH_BREAK_SENDING ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  IOCTL ; 
 int UART_LCR_SBC ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  jsm_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neo_pci_posting_flush (TYPE_2__*) ; 
 int readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void neo_clear_break(struct jsm_channel *ch, int force)
{
	unsigned long lock_flags;

	spin_lock_irqsave(&ch->ch_lock, lock_flags);

	/* Turn break off, and unset some variables */
	if (ch->ch_flags & CH_BREAK_SENDING) {
		u8 temp = readb(&ch->ch_neo_uart->lcr);
		writeb((temp & ~UART_LCR_SBC), &ch->ch_neo_uart->lcr);

		ch->ch_flags &= ~(CH_BREAK_SENDING);
		jsm_printk(IOCTL, INFO, &ch->ch_bd->pci_dev,
				"clear break Finishing UART_LCR_SBC! finished: %lx\n", jiffies);

		/* flush write operation */
		neo_pci_posting_flush(ch->ch_bd);
	}
	spin_unlock_irqrestore(&ch->ch_lock, lock_flags);
}