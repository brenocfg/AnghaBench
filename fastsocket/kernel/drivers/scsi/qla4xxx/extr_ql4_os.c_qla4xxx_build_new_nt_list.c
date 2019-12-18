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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct scsi_qla_host {int /*<<< orphan*/  fw_ddb_dma_pool; } ;
struct qla_ddb_index {int fw_ddb_idx; int /*<<< orphan*/  list; } ;
struct list_head {int dummy; } ;
struct dev_db_entry {scalar_t__ iscsi_name; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int DDB_DS_NO_CONNECTION_ACTIVE ; 
 int /*<<< orphan*/  DEBUG2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int MAX_DEV_DB_ENTRIES ; 
 int MAX_DEV_DB_ENTRIES_40XX ; 
 int QLA_ERROR ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  RESET_ADAPTER ; 
 struct dev_db_entry* dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,struct dev_db_entry*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_qla40XX (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  ql4_printk (int /*<<< orphan*/ ,struct scsi_qla_host*,char*,...) ; 
 int qla4xxx_get_fwddb_entry (struct scsi_qla_host*,int,struct dev_db_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int qla4xxx_is_session_exists (struct scsi_qla_host*,struct dev_db_entry*) ; 
 int qla4xxx_sess_conn_setup (struct scsi_qla_host*,struct dev_db_entry*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  vfree (struct qla_ddb_index*) ; 
 struct qla_ddb_index* vmalloc (int) ; 

__attribute__((used)) static void qla4xxx_build_new_nt_list(struct scsi_qla_host *ha,
				      struct list_head *list_nt)
{
	struct dev_db_entry *fw_ddb_entry;
	dma_addr_t fw_ddb_dma;
	int max_ddbs;
	int fw_idx_size;
	int ret;
	uint32_t idx = 0, next_idx = 0;
	uint32_t state = 0, conn_err = 0;
	uint16_t conn_id = 0;
	struct qla_ddb_index  *nt_ddb_idx;

	fw_ddb_entry = dma_pool_alloc(ha->fw_ddb_dma_pool, GFP_KERNEL,
				      &fw_ddb_dma);
	if (fw_ddb_entry == NULL) {
		DEBUG2(ql4_printk(KERN_ERR, ha, "Out of memory\n"));
		goto exit_new_nt_list;
	}
	max_ddbs =  is_qla40XX(ha) ? MAX_DEV_DB_ENTRIES_40XX :
				     MAX_DEV_DB_ENTRIES;
	fw_idx_size = sizeof(struct qla_ddb_index);

	for (idx = 0; idx < max_ddbs; idx = next_idx) {
		ret = qla4xxx_get_fwddb_entry(ha, idx, fw_ddb_entry, fw_ddb_dma,
					      NULL, &next_idx, &state,
					      &conn_err, NULL, &conn_id);
		if (ret == QLA_ERROR)
			break;

		/* Check if NT, then add it to list */
		if (strlen((char *)fw_ddb_entry->iscsi_name) == 0)
			goto continue_next_new_nt;

		if (!(state == DDB_DS_NO_CONNECTION_ACTIVE))
			goto continue_next_new_nt;

		DEBUG2(ql4_printk(KERN_INFO, ha,
				  "Adding  DDB to session = 0x%x\n", idx));

		nt_ddb_idx = vmalloc(fw_idx_size);
		if (!nt_ddb_idx)
			break;

		nt_ddb_idx->fw_ddb_idx = idx;

		ret = qla4xxx_is_session_exists(ha, fw_ddb_entry);
		if (ret == QLA_SUCCESS) {
			/* free nt_ddb_idx and do not add to list_nt */
			vfree(nt_ddb_idx);
			goto continue_next_new_nt;
		}

		list_add_tail(&nt_ddb_idx->list, list_nt);

		ret = qla4xxx_sess_conn_setup(ha, fw_ddb_entry, RESET_ADAPTER,
					      idx);
		if (ret == QLA_ERROR)
			goto exit_new_nt_list;

continue_next_new_nt:
		if (next_idx == 0)
			break;
	}

exit_new_nt_list:
	if (fw_ddb_entry)
		dma_pool_free(ha->fw_ddb_dma_pool, fw_ddb_entry, fw_ddb_dma);
}