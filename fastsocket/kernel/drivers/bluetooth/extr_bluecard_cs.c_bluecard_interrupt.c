#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_8__ {int ctrl_reg; int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_state; TYPE_2__* p_dev; int /*<<< orphan*/  hw_state; int /*<<< orphan*/  hdev; } ;
typedef  TYPE_3__ bluecard_info_t ;
struct TYPE_6__ {unsigned int BasePort1; } ;
struct TYPE_7__ {TYPE_1__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CARD_READY ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ REG_COMMAND ; 
 int REG_COMMAND_RX_BUF_ONE ; 
 int REG_COMMAND_RX_BUF_TWO ; 
 scalar_t__ REG_CONTROL ; 
 int REG_CONTROL_INTERRUPT ; 
 scalar_t__ REG_INTERRUPT ; 
 int /*<<< orphan*/  XMIT_BUF_ONE_READY ; 
 int /*<<< orphan*/  XMIT_BUF_TWO_READY ; 
 int /*<<< orphan*/  bluecard_receive (TYPE_3__*,int) ; 
 int /*<<< orphan*/  bluecard_write_wakeup (TYPE_3__*) ; 
 unsigned char inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t bluecard_interrupt(int irq, void *dev_inst)
{
	bluecard_info_t *info = dev_inst;
	unsigned int iobase;
	unsigned char reg;

	BUG_ON(!info->hdev);

	if (!test_bit(CARD_READY, &(info->hw_state)))
		return IRQ_HANDLED;

	iobase = info->p_dev->io.BasePort1;

	spin_lock(&(info->lock));

	/* Disable interrupt */
	info->ctrl_reg &= ~REG_CONTROL_INTERRUPT;
	outb(info->ctrl_reg, iobase + REG_CONTROL);

	reg = inb(iobase + REG_INTERRUPT);

	if ((reg != 0x00) && (reg != 0xff)) {

		if (reg & 0x04) {
			bluecard_receive(info, 0x00);
			outb(0x04, iobase + REG_INTERRUPT);
			outb(REG_COMMAND_RX_BUF_ONE, iobase + REG_COMMAND);
		}

		if (reg & 0x08) {
			bluecard_receive(info, 0x10);
			outb(0x08, iobase + REG_INTERRUPT);
			outb(REG_COMMAND_RX_BUF_TWO, iobase + REG_COMMAND);
		}

		if (reg & 0x01) {
			set_bit(XMIT_BUF_ONE_READY, &(info->tx_state));
			outb(0x01, iobase + REG_INTERRUPT);
			bluecard_write_wakeup(info);
		}

		if (reg & 0x02) {
			set_bit(XMIT_BUF_TWO_READY, &(info->tx_state));
			outb(0x02, iobase + REG_INTERRUPT);
			bluecard_write_wakeup(info);
		}

	}

	/* Enable interrupt */
	info->ctrl_reg |= REG_CONTROL_INTERRUPT;
	outb(info->ctrl_reg, iobase + REG_CONTROL);

	spin_unlock(&(info->lock));

	return IRQ_HANDLED;
}