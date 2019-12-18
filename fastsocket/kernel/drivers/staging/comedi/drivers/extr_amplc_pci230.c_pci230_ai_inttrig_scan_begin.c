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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ai_stop_spinlock; scalar_t__ iobase1; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  AI_CMD_STARTED ; 
 int EINVAL ; 
 unsigned char GAT_CONFIG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GAT_GND ; 
 int /*<<< orphan*/  GAT_VCC ; 
 scalar_t__ PCI230_ZGAT_SCE ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pci230_ai_inttrig_scan_begin(struct comedi_device *dev,
					struct comedi_subdevice *s,
					unsigned int trig_num)
{
	unsigned long irqflags;
	unsigned char zgat;

	if (trig_num != 0)
		return -EINVAL;

	spin_lock_irqsave(&devpriv->ai_stop_spinlock, irqflags);
	if (test_bit(AI_CMD_STARTED, &devpriv->state)) {
		/* Trigger scan by waggling CT0 gate source. */
		zgat = GAT_CONFIG(0, GAT_GND);
		outb(zgat, devpriv->iobase1 + PCI230_ZGAT_SCE);
		zgat = GAT_CONFIG(0, GAT_VCC);
		outb(zgat, devpriv->iobase1 + PCI230_ZGAT_SCE);
	}
	spin_unlock_irqrestore(&devpriv->ai_stop_spinlock, irqflags);

	return 1;
}