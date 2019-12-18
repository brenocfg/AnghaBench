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
struct scsi_qla_host {int dummy; } ;
struct ql4_tuple_ddb {int dummy; } ;
struct dev_db_entry {int dummy; } ;
struct ddb_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int MAX_DDB_ENTRIES ; 
 int QLA_ERROR ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  ql4_printk (int /*<<< orphan*/ ,struct scsi_qla_host*,char*) ; 
 int /*<<< orphan*/  qla4xxx_compare_tuple_ddb (struct scsi_qla_host*,struct ql4_tuple_ddb*,struct ql4_tuple_ddb*,int) ; 
 int /*<<< orphan*/  qla4xxx_convert_param_ddb (struct dev_db_entry*,struct ql4_tuple_ddb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla4xxx_get_param_ddb (struct ddb_entry*,struct ql4_tuple_ddb*) ; 
 struct ddb_entry* qla4xxx_lookup_ddb_by_fw_index (struct scsi_qla_host*,int) ; 
 int /*<<< orphan*/  vfree (struct ql4_tuple_ddb*) ; 
 struct ql4_tuple_ddb* vzalloc (int) ; 

__attribute__((used)) static int qla4xxx_is_session_exists(struct scsi_qla_host *ha,
				     struct dev_db_entry *fw_ddb_entry)
{
	struct ddb_entry *ddb_entry;
	struct ql4_tuple_ddb *fw_tddb = NULL;
	struct ql4_tuple_ddb *tmp_tddb = NULL;
	int idx;
	int ret = QLA_ERROR;

	fw_tddb = vzalloc(sizeof(*fw_tddb));
	if (!fw_tddb) {
		DEBUG2(ql4_printk(KERN_WARNING, ha,
				  "Memory Allocation failed.\n"));
		ret = QLA_SUCCESS;
		goto exit_check;
	}

	tmp_tddb = vzalloc(sizeof(*tmp_tddb));
	if (!tmp_tddb) {
		DEBUG2(ql4_printk(KERN_WARNING, ha,
				  "Memory Allocation failed.\n"));
		ret = QLA_SUCCESS;
		goto exit_check;
	}

	qla4xxx_convert_param_ddb(fw_ddb_entry, fw_tddb, NULL);

	for (idx = 0; idx < MAX_DDB_ENTRIES; idx++) {
		ddb_entry = qla4xxx_lookup_ddb_by_fw_index(ha, idx);
		if (ddb_entry == NULL)
			continue;

		qla4xxx_get_param_ddb(ddb_entry, tmp_tddb);
		if (!qla4xxx_compare_tuple_ddb(ha, fw_tddb, tmp_tddb, false)) {
			ret = QLA_SUCCESS; /* found */
			goto exit_check;
		}
	}

exit_check:
	if (fw_tddb)
		vfree(fw_tddb);
	if (tmp_tddb)
		vfree(tmp_tddb);
	return ret;
}