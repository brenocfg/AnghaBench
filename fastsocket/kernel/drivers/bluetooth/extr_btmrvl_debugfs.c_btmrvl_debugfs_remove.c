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
struct hci_dev {struct btmrvl_private* driver_data; } ;
struct btmrvl_private {struct btmrvl_debugfs_data* debugfs_data; } ;
struct btmrvl_debugfs_data {int /*<<< orphan*/  root_dir; int /*<<< orphan*/  status_dir; int /*<<< orphan*/  txdnldready; int /*<<< orphan*/  hsstate; int /*<<< orphan*/  psstate; int /*<<< orphan*/  curpsmode; int /*<<< orphan*/  config_dir; int /*<<< orphan*/  hscfgcmd; int /*<<< orphan*/  hscmd; int /*<<< orphan*/  hsmode; int /*<<< orphan*/  gpiogap; int /*<<< orphan*/  pscmd; int /*<<< orphan*/  psmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct btmrvl_debugfs_data*) ; 

void btmrvl_debugfs_remove(struct hci_dev *hdev)
{
	struct btmrvl_private *priv = hdev->driver_data;
	struct btmrvl_debugfs_data *dbg = priv->debugfs_data;

	if (!dbg)
		return;

	debugfs_remove(dbg->psmode);
	debugfs_remove(dbg->pscmd);
	debugfs_remove(dbg->gpiogap);
	debugfs_remove(dbg->hsmode);
	debugfs_remove(dbg->hscmd);
	debugfs_remove(dbg->hscfgcmd);
	debugfs_remove(dbg->config_dir);

	debugfs_remove(dbg->curpsmode);
	debugfs_remove(dbg->psstate);
	debugfs_remove(dbg->hsstate);
	debugfs_remove(dbg->txdnldready);
	debugfs_remove(dbg->status_dir);

	debugfs_remove(dbg->root_dir);

	kfree(dbg);
}