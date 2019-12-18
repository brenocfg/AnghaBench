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
struct hci_dev {int dummy; } ;
struct TYPE_6__ {struct hci_dev* hcidev; } ;
struct TYPE_5__ {int /*<<< orphan*/  task; } ;
struct btmrvl_private {TYPE_3__ btmrvl_dev; TYPE_2__ main_thread; TYPE_1__* adapter; } ;
struct TYPE_4__ {int /*<<< orphan*/  cmd_wait_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  btmrvl_debugfs_remove (struct hci_dev*) ; 
 int /*<<< orphan*/  btmrvl_free_adapter (struct btmrvl_private*) ; 
 int /*<<< orphan*/  hci_free_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_unregister_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  kfree (struct btmrvl_private*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

int btmrvl_remove_card(struct btmrvl_private *priv)
{
	struct hci_dev *hdev;

	hdev = priv->btmrvl_dev.hcidev;

	wake_up_interruptible(&priv->adapter->cmd_wait_q);

	kthread_stop(priv->main_thread.task);

#ifdef CONFIG_DEBUG_FS
	btmrvl_debugfs_remove(hdev);
#endif

	hci_unregister_dev(hdev);

	hci_free_dev(hdev);

	priv->btmrvl_dev.hcidev = NULL;

	btmrvl_free_adapter(priv);

	kfree(priv);

	return 0;
}