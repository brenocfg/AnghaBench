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
struct hci_dev {int /*<<< orphan*/  owner; int /*<<< orphan*/  ioctl; int /*<<< orphan*/  destruct; int /*<<< orphan*/  send; int /*<<< orphan*/  flush; int /*<<< orphan*/  close; int /*<<< orphan*/  open; int /*<<< orphan*/  type; struct btmrvl_private* driver_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  task; int /*<<< orphan*/  wait_q; struct btmrvl_private* priv; } ;
struct TYPE_3__ {int tx_dnld_rdy; void* card; struct hci_dev* hcidev; } ;
struct btmrvl_private {TYPE_2__ main_thread; TYPE_1__ btmrvl_dev; int /*<<< orphan*/  driver_lock; void* adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HCI_SDIO ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  btmrvl_close ; 
 int /*<<< orphan*/  btmrvl_debugfs_init (struct hci_dev*) ; 
 int /*<<< orphan*/  btmrvl_destruct ; 
 int /*<<< orphan*/  btmrvl_flush ; 
 int /*<<< orphan*/  btmrvl_free_adapter (struct btmrvl_private*) ; 
 int /*<<< orphan*/  btmrvl_init_adapter (struct btmrvl_private*) ; 
 int /*<<< orphan*/  btmrvl_ioctl ; 
 int /*<<< orphan*/  btmrvl_open ; 
 int /*<<< orphan*/  btmrvl_send_frame ; 
 int /*<<< orphan*/  btmrvl_service_main_thread ; 
 struct hci_dev* hci_alloc_dev () ; 
 int /*<<< orphan*/  hci_free_dev (struct hci_dev*) ; 
 int hci_register_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct btmrvl_private*) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,TYPE_2__*,char*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct btmrvl_private *btmrvl_add_card(void *card)
{
	struct hci_dev *hdev = NULL;
	struct btmrvl_private *priv;
	int ret;

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv) {
		BT_ERR("Can not allocate priv");
		goto err_priv;
	}

	priv->adapter = kzalloc(sizeof(*priv->adapter), GFP_KERNEL);
	if (!priv->adapter) {
		BT_ERR("Allocate buffer for btmrvl_adapter failed!");
		goto err_adapter;
	}

	btmrvl_init_adapter(priv);

	hdev = hci_alloc_dev();
	if (!hdev) {
		BT_ERR("Can not allocate HCI device");
		goto err_hdev;
	}

	BT_DBG("Starting kthread...");
	priv->main_thread.priv = priv;
	spin_lock_init(&priv->driver_lock);

	init_waitqueue_head(&priv->main_thread.wait_q);
	priv->main_thread.task = kthread_run(btmrvl_service_main_thread,
				&priv->main_thread, "btmrvl_main_service");

	priv->btmrvl_dev.hcidev = hdev;
	priv->btmrvl_dev.card = card;

	hdev->driver_data = priv;

	priv->btmrvl_dev.tx_dnld_rdy = true;

	hdev->type = HCI_SDIO;
	hdev->open = btmrvl_open;
	hdev->close = btmrvl_close;
	hdev->flush = btmrvl_flush;
	hdev->send = btmrvl_send_frame;
	hdev->destruct = btmrvl_destruct;
	hdev->ioctl = btmrvl_ioctl;
	hdev->owner = THIS_MODULE;

	ret = hci_register_dev(hdev);
	if (ret < 0) {
		BT_ERR("Can not register HCI device");
		goto err_hci_register_dev;
	}

#ifdef CONFIG_DEBUG_FS
	btmrvl_debugfs_init(hdev);
#endif

	return priv;

err_hci_register_dev:
	/* Stop the thread servicing the interrupts */
	kthread_stop(priv->main_thread.task);

	hci_free_dev(hdev);

err_hdev:
	btmrvl_free_adapter(priv);

err_adapter:
	kfree(priv);

err_priv:
	return NULL;
}