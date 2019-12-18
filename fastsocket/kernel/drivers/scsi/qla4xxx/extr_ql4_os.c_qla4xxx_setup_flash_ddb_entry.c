#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct scsi_qla_host {int pri_ddb_idx; int sec_ddb_idx; } ;
struct TYPE_2__ {int /*<<< orphan*/  iscsi_def_time2wait; int /*<<< orphan*/  def_timeout; } ;
struct ddb_entry {int default_relogin_timeout; int /*<<< orphan*/  flags; TYPE_1__ fw_ddb_entry; void* default_time2wait; int /*<<< orphan*/  relogin_retry_count; int /*<<< orphan*/  relogin_timer; int /*<<< orphan*/  retry_relogin_timer; int /*<<< orphan*/  ddb_change; int /*<<< orphan*/  unblock_sess; struct scsi_qla_host* ha; int /*<<< orphan*/  fw_ddb_device_state; int /*<<< orphan*/  fw_ddb_index; int /*<<< orphan*/  ddb_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDB_DS_NO_CONNECTION_ACTIVE ; 
 int /*<<< orphan*/  DF_BOOT_TGT ; 
 int /*<<< orphan*/  FLASH_DDB ; 
 int /*<<< orphan*/  INVALID_ENTRY ; 
 int LOGIN_TOV ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ ql4xdisablesysfsboot ; 
 int /*<<< orphan*/  qla4xxx_flash_ddb_change ; 
 int /*<<< orphan*/  qla4xxx_unblock_flash_ddb ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qla4xxx_setup_flash_ddb_entry(struct scsi_qla_host *ha,
					  struct ddb_entry *ddb_entry,
					  uint16_t idx)
{
	uint16_t def_timeout;

	ddb_entry->ddb_type = FLASH_DDB;
	ddb_entry->fw_ddb_index = INVALID_ENTRY;
	ddb_entry->fw_ddb_device_state = DDB_DS_NO_CONNECTION_ACTIVE;
	ddb_entry->ha = ha;
	ddb_entry->unblock_sess = qla4xxx_unblock_flash_ddb;
	ddb_entry->ddb_change = qla4xxx_flash_ddb_change;

	atomic_set(&ddb_entry->retry_relogin_timer, INVALID_ENTRY);
	atomic_set(&ddb_entry->relogin_timer, 0);
	atomic_set(&ddb_entry->relogin_retry_count, 0);
	def_timeout = le16_to_cpu(ddb_entry->fw_ddb_entry.def_timeout);
	ddb_entry->default_relogin_timeout =
		(def_timeout > LOGIN_TOV) && (def_timeout < LOGIN_TOV * 10) ?
		def_timeout : LOGIN_TOV;
	ddb_entry->default_time2wait =
		le16_to_cpu(ddb_entry->fw_ddb_entry.iscsi_def_time2wait);

	if (ql4xdisablesysfsboot &&
	    (idx == ha->pri_ddb_idx || idx == ha->sec_ddb_idx))
		set_bit(DF_BOOT_TGT, &ddb_entry->flags);
}