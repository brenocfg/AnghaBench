#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct iwl_mvm {TYPE_6__* hw; struct dentry* debugfs_dir; } ;
struct dentry {TYPE_4__* d_parent; } ;
struct TYPE_12__ {TYPE_5__* wiphy; } ;
struct TYPE_11__ {int /*<<< orphan*/  debugfsdir; } ;
struct TYPE_9__ {char* name; } ;
struct TYPE_10__ {TYPE_3__ d_name; TYPE_2__* d_parent; } ;
struct TYPE_7__ {char* name; } ;
struct TYPE_8__ {TYPE_1__ d_name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  MVM_DEBUGFS_ADD_FILE (int /*<<< orphan*/ ,struct dentry*,int) ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  bt_notif ; 
 int /*<<< orphan*/  debugfs_create_symlink (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fw_restart ; 
 int /*<<< orphan*/  power_down_allow ; 
 int /*<<< orphan*/  power_down_d3_allow ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  sram ; 
 int /*<<< orphan*/  sta_drain ; 
 int /*<<< orphan*/  stations ; 
 int /*<<< orphan*/  tx_flush ; 

int iwl_mvm_dbgfs_register(struct iwl_mvm *mvm, struct dentry *dbgfs_dir)
{
	char buf[100];

	mvm->debugfs_dir = dbgfs_dir;

	MVM_DEBUGFS_ADD_FILE(tx_flush, mvm->debugfs_dir, S_IWUSR);
	MVM_DEBUGFS_ADD_FILE(sta_drain, mvm->debugfs_dir, S_IWUSR);
	MVM_DEBUGFS_ADD_FILE(sram, mvm->debugfs_dir, S_IWUSR | S_IRUSR);
	MVM_DEBUGFS_ADD_FILE(stations, dbgfs_dir, S_IRUSR);
	MVM_DEBUGFS_ADD_FILE(bt_notif, dbgfs_dir, S_IRUSR);
	MVM_DEBUGFS_ADD_FILE(power_down_allow, mvm->debugfs_dir, S_IWUSR);
	MVM_DEBUGFS_ADD_FILE(power_down_d3_allow, mvm->debugfs_dir, S_IWUSR);
	MVM_DEBUGFS_ADD_FILE(fw_restart, mvm->debugfs_dir, S_IWUSR);

	/*
	 * Create a symlink with mac80211. It will be removed when mac80211
	 * exists (before the opmode exists which removes the target.)
	 */
	snprintf(buf, 100, "../../%s/%s",
		 dbgfs_dir->d_parent->d_parent->d_name.name,
		 dbgfs_dir->d_parent->d_name.name);
	if (!debugfs_create_symlink("iwlwifi", mvm->hw->wiphy->debugfsdir, buf))
		goto err;

	return 0;
err:
	IWL_ERR(mvm, "Can't create the mvm debugfs directory\n");
	return -ENOMEM;
}