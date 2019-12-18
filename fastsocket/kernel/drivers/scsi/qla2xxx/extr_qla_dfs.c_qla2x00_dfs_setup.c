#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct qla_hw_data {int /*<<< orphan*/  dfs_fce; void* dfs_dir; int /*<<< orphan*/  fce_mutex; int /*<<< orphan*/  fce; } ;
struct TYPE_5__ {int /*<<< orphan*/  host_str; struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_QLA25XX (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLA81XX (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLA83XX (struct qla_hw_data*) ; 
 int /*<<< orphan*/  QLA2XXX_DRIVER_NAME ; 
 int /*<<< orphan*/  S_IRUSR ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int /*<<< orphan*/ ,void*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dfs_fce_ops ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/ * qla2x00_dfs_root ; 
 int /*<<< orphan*/  qla2x00_dfs_root_count ; 

int
qla2x00_dfs_setup(scsi_qla_host_t *vha)
{
	struct qla_hw_data *ha = vha->hw;

	if (!IS_QLA25XX(ha) && !IS_QLA81XX(ha) && !IS_QLA83XX(ha))
		goto out;
	if (!ha->fce)
		goto out;

	if (qla2x00_dfs_root)
		goto create_dir;

	atomic_set(&qla2x00_dfs_root_count, 0);
	qla2x00_dfs_root = debugfs_create_dir(QLA2XXX_DRIVER_NAME, NULL);
	if (!qla2x00_dfs_root) {
		ql_log(ql_log_warn, vha, 0x00f7,
		    "Unable to create debugfs root directory.\n");
		goto out;
	}

create_dir:
	if (ha->dfs_dir)
		goto create_nodes;

	mutex_init(&ha->fce_mutex);
	ha->dfs_dir = debugfs_create_dir(vha->host_str, qla2x00_dfs_root);
	if (!ha->dfs_dir) {
		ql_log(ql_log_warn, vha, 0x00f8,
		    "Unable to create debugfs ha directory.\n");
		goto out;
	}

	atomic_inc(&qla2x00_dfs_root_count);

create_nodes:
	ha->dfs_fce = debugfs_create_file("fce", S_IRUSR, ha->dfs_dir, vha,
	    &dfs_fce_ops);
	if (!ha->dfs_fce) {
		ql_log(ql_log_warn, vha, 0x00f9,
		    "Unable to create debugfs fce node.\n");
		goto out;
	}
out:
	return 0;
}