#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_10__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_state; TYPE_3__* hdev; TYPE_2__* p_dev; } ;
typedef  TYPE_4__ bt3c_info_t ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {unsigned int BasePort1; } ;
struct TYPE_8__ {TYPE_1__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*,int) ; 
 int /*<<< orphan*/  BT_INFO (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CONTROL ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  XMIT_SENDING ; 
 int /*<<< orphan*/  bt3c_io_write (unsigned int,int,int) ; 
 int bt3c_read (unsigned int,int) ; 
 int /*<<< orphan*/  bt3c_receive (TYPE_4__*) ; 
 int /*<<< orphan*/  bt3c_write_wakeup (TYPE_4__*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t bt3c_interrupt(int irq, void *dev_inst)
{
	bt3c_info_t *info = dev_inst;
	unsigned int iobase;
	int iir;
	irqreturn_t r = IRQ_NONE;

	BUG_ON(!info->hdev);

	iobase = info->p_dev->io.BasePort1;

	spin_lock(&(info->lock));

	iir = inb(iobase + CONTROL);
	if (iir & 0x80) {
		int stat = bt3c_read(iobase, 0x7001);

		if ((stat & 0xff) == 0x7f) {
			BT_ERR("Very strange (stat=0x%04x)", stat);
		} else if ((stat & 0xff) != 0xff) {
			if (stat & 0x0020) {
				int status = bt3c_read(iobase, 0x7002) & 0x10;
				BT_INFO("%s: Antenna %s", info->hdev->name,
							status ? "out" : "in");
			}
			if (stat & 0x0001)
				bt3c_receive(info);
			if (stat & 0x0002) {
				//BT_ERR("Ack (stat=0x%04x)", stat);
				clear_bit(XMIT_SENDING, &(info->tx_state));
				bt3c_write_wakeup(info);
			}

			bt3c_io_write(iobase, 0x7001, 0x0000);

			outb(iir, iobase + CONTROL);
		}
		r = IRQ_HANDLED;
	}

	spin_unlock(&(info->lock));

	return r;
}