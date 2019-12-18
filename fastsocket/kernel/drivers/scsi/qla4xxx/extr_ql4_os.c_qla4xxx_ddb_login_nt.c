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
typedef  int /*<<< orphan*/  uint16_t ;
struct scsi_qla_host {int dummy; } ;
struct dev_db_entry {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 int QLA_ERROR ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  RESET_ADAPTER ; 
 int qla4xxx_is_session_exists (struct scsi_qla_host*,struct dev_db_entry*) ; 
 int qla4xxx_sess_conn_setup (struct scsi_qla_host*,struct dev_db_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qla4xxx_ddb_login_nt(struct scsi_qla_host *ha,
				struct dev_db_entry *fw_ddb_entry,
				uint16_t idx)
{
	int ret = QLA_ERROR;

	ret = qla4xxx_is_session_exists(ha, fw_ddb_entry);
	if (ret != QLA_SUCCESS)
		ret = qla4xxx_sess_conn_setup(ha, fw_ddb_entry, RESET_ADAPTER,
					      idx);
	else
		ret = -EPERM;

	return ret;
}