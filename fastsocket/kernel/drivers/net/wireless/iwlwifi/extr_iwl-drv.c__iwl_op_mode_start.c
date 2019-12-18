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
struct iwlwifi_opmode_table {int /*<<< orphan*/  name; struct iwl_op_mode_ops* ops; } ;
struct iwl_op_mode_ops {struct iwl_op_mode* (* start ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dentry*) ;} ;
struct iwl_op_mode {int dummy; } ;
struct iwl_drv {struct dentry* dbgfs_op_mode; int /*<<< orphan*/  fw; int /*<<< orphan*/  cfg; int /*<<< orphan*/  trans; int /*<<< orphan*/  dbgfs_drv; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_ERR (struct iwl_drv*,char*) ; 
 struct dentry* debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (struct dentry*) ; 
 struct iwl_op_mode* stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dentry*) ; 

__attribute__((used)) static struct iwl_op_mode *
_iwl_op_mode_start(struct iwl_drv *drv, struct iwlwifi_opmode_table *op)
{
	const struct iwl_op_mode_ops *ops = op->ops;
	struct dentry *dbgfs_dir = NULL;
	struct iwl_op_mode *op_mode = NULL;

#ifdef CONFIG_IWLWIFI_DEBUGFS
	drv->dbgfs_op_mode = debugfs_create_dir(op->name,
						drv->dbgfs_drv);
	if (!drv->dbgfs_op_mode) {
		IWL_ERR(drv,
			"failed to create opmode debugfs directory\n");
		return op_mode;
	}
	dbgfs_dir = drv->dbgfs_op_mode;
#endif

	op_mode = ops->start(drv->trans, drv->cfg, &drv->fw, dbgfs_dir);

#ifdef CONFIG_IWLWIFI_DEBUGFS
	if (!op_mode) {
		debugfs_remove_recursive(drv->dbgfs_op_mode);
		drv->dbgfs_op_mode = NULL;
	}
#endif

	return op_mode;
}