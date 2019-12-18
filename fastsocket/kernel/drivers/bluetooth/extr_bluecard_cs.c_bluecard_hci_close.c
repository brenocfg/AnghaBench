#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hci_dev {int /*<<< orphan*/  flags; scalar_t__ driver_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  hw_state; TYPE_2__* p_dev; } ;
typedef  TYPE_3__ bluecard_info_t ;
struct TYPE_4__ {unsigned int BasePort1; } ;
struct TYPE_5__ {TYPE_1__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_HAS_PCCARD_ID ; 
 int /*<<< orphan*/  HCI_RUNNING ; 
 int /*<<< orphan*/  bluecard_hci_flush (struct hci_dev*) ; 
 int /*<<< orphan*/  outb (int,unsigned int) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bluecard_hci_close(struct hci_dev *hdev)
{
	bluecard_info_t *info = (bluecard_info_t *)(hdev->driver_data);
	unsigned int iobase = info->p_dev->io.BasePort1;

	if (!test_and_clear_bit(HCI_RUNNING, &(hdev->flags)))
		return 0;

	bluecard_hci_flush(hdev);

	if (test_bit(CARD_HAS_PCCARD_ID, &(info->hw_state))) {
		/* Disable LED */
		outb(0x00, iobase + 0x30);
	}

	return 0;
}