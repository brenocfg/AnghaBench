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
struct sdio_func_tuple {struct sdio_func_tuple* next; int /*<<< orphan*/  size; int /*<<< orphan*/  code; } ;
struct sdio_func {int /*<<< orphan*/  dev; int /*<<< orphan*/  class; struct sdio_func_tuple* tuples; } ;
struct sdio_device_id {int dummy; } ;
struct hci_dev {int /*<<< orphan*/  owner; int /*<<< orphan*/  destruct; int /*<<< orphan*/  send; int /*<<< orphan*/  flush; int /*<<< orphan*/  close; int /*<<< orphan*/  open; struct btsdio_data* driver_data; int /*<<< orphan*/  type; } ;
struct btsdio_data {struct hci_dev* hdev; int /*<<< orphan*/  txq; int /*<<< orphan*/  work; struct sdio_func* func; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct sdio_func*,int /*<<< orphan*/ ,...) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HCI_SDIO ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_HCIDEV_DEV (struct hci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  btsdio_close ; 
 int /*<<< orphan*/  btsdio_destruct ; 
 int /*<<< orphan*/  btsdio_flush ; 
 int /*<<< orphan*/  btsdio_open ; 
 int /*<<< orphan*/  btsdio_send_frame ; 
 int /*<<< orphan*/  btsdio_work ; 
 struct hci_dev* hci_alloc_dev () ; 
 int /*<<< orphan*/  hci_free_dev (struct hci_dev*) ; 
 int hci_register_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  kfree (struct btsdio_data*) ; 
 struct btsdio_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_set_drvdata (struct sdio_func*,struct btsdio_data*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btsdio_probe(struct sdio_func *func,
				const struct sdio_device_id *id)
{
	struct btsdio_data *data;
	struct hci_dev *hdev;
	struct sdio_func_tuple *tuple = func->tuples;
	int err;

	BT_DBG("func %p id %p class 0x%04x", func, id, func->class);

	while (tuple) {
		BT_DBG("code 0x%x size %d", tuple->code, tuple->size);
		tuple = tuple->next;
	}

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->func = func;

	INIT_WORK(&data->work, btsdio_work);

	skb_queue_head_init(&data->txq);

	hdev = hci_alloc_dev();
	if (!hdev) {
		kfree(data);
		return -ENOMEM;
	}

	hdev->type = HCI_SDIO;
	hdev->driver_data = data;

	data->hdev = hdev;

	SET_HCIDEV_DEV(hdev, &func->dev);

	hdev->open     = btsdio_open;
	hdev->close    = btsdio_close;
	hdev->flush    = btsdio_flush;
	hdev->send     = btsdio_send_frame;
	hdev->destruct = btsdio_destruct;

	hdev->owner = THIS_MODULE;

	err = hci_register_dev(hdev);
	if (err < 0) {
		hci_free_dev(hdev);
		kfree(data);
		return err;
	}

	sdio_set_drvdata(func, data);

	return 0;
}