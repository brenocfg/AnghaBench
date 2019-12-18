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
struct hci_dev {int /*<<< orphan*/  flags; int /*<<< orphan*/  name; struct btsdio_data* driver_data; } ;
struct btsdio_data {int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_RUNNING ; 
 int /*<<< orphan*/  REG_EN_INTRD ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_disable_func (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_release_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_writeb (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btsdio_close(struct hci_dev *hdev)
{
	struct btsdio_data *data = hdev->driver_data;

	BT_DBG("%s", hdev->name);

	if (!test_and_clear_bit(HCI_RUNNING, &hdev->flags))
		return 0;

	sdio_claim_host(data->func);

	sdio_writeb(data->func, 0x00, REG_EN_INTRD, NULL);

	sdio_release_irq(data->func);
	sdio_disable_func(data->func);

	sdio_release_host(data->func);

	return 0;
}