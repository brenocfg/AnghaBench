#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct cx25821_dev {int dummy; } ;
struct TYPE_3__ {struct cx25821_dev* dev; } ;
typedef  TYPE_1__ snd_cx25821_card_t ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUD_A_GPCNT ; 
 int /*<<< orphan*/  AUD_A_INT_MSK ; 
 int /*<<< orphan*/  AUD_A_INT_STAT ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  PCI_INT_STAT ; 
 int /*<<< orphan*/  cx25821_aud_irq (TYPE_1__*,int,int) ; 
 int cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t cx25821_irq(int irq, void *dev_id)
{
	snd_cx25821_card_t *chip = dev_id;
	struct cx25821_dev *dev = chip->dev;
	u32 status, pci_status;
	u32 audint_status, audint_mask;
	int loop, handled = 0;
	int audint_count = 0;

	audint_status = cx_read(AUD_A_INT_STAT);
	audint_mask = cx_read(AUD_A_INT_MSK);
	audint_count = cx_read(AUD_A_GPCNT);
	status = cx_read(PCI_INT_STAT);

	for (loop = 0; loop < 1; loop++) {
		status = cx_read(PCI_INT_STAT);
		if (0 == status) {
			status = cx_read(PCI_INT_STAT);
			audint_status = cx_read(AUD_A_INT_STAT);
			audint_mask = cx_read(AUD_A_INT_MSK);

			if (status) {
				handled = 1;
				cx_write(PCI_INT_STAT, status);

				cx25821_aud_irq(chip, audint_status,
						audint_mask);
				break;
			} else
				goto out;
		}

		handled = 1;
		cx_write(PCI_INT_STAT, status);

		cx25821_aud_irq(chip, audint_status, audint_mask);
	}

	pci_status = cx_read(PCI_INT_STAT);

	if (handled)
		cx_write(PCI_INT_STAT, pci_status);

      out:
	return IRQ_RETVAL(handled);
}