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
struct scsi_cmnd {unsigned int cmd_len; unsigned int cmnd; } ;
struct iscsi_task {int /*<<< orphan*/  hdr_len; TYPE_1__* conn; struct scsi_cmnd* sc; } ;
struct iscsi_ecdb_ahdr {int /*<<< orphan*/ * ecdb; scalar_t__ reserved; int /*<<< orphan*/  ahstype; int /*<<< orphan*/  ahslength; } ;
struct TYPE_2__ {int /*<<< orphan*/  session; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ISCSI_AHSTYPE_CDB ; 
 unsigned int ISCSI_CDB_SIZE ; 
 int /*<<< orphan*/  ISCSI_DBG_SESSION (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,unsigned int,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (unsigned short) ; 
 int iscsi_add_hdr (struct iscsi_task*,int) ; 
 struct iscsi_ecdb_ahdr* iscsi_next_hdr (struct iscsi_task*) ; 
 unsigned int iscsi_padding (unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int iscsi_prep_ecdb_ahs(struct iscsi_task *task)
{
	struct scsi_cmnd *cmd = task->sc;
	unsigned rlen, pad_len;
	unsigned short ahslength;
	struct iscsi_ecdb_ahdr *ecdb_ahdr;
	int rc;

	ecdb_ahdr = iscsi_next_hdr(task);
	rlen = cmd->cmd_len - ISCSI_CDB_SIZE;

	BUG_ON(rlen > sizeof(ecdb_ahdr->ecdb));
	ahslength = rlen + sizeof(ecdb_ahdr->reserved);

	pad_len = iscsi_padding(rlen);

	rc = iscsi_add_hdr(task, sizeof(ecdb_ahdr->ahslength) +
	                   sizeof(ecdb_ahdr->ahstype) + ahslength + pad_len);
	if (rc)
		return rc;

	if (pad_len)
		memset(&ecdb_ahdr->ecdb[rlen], 0, pad_len);

	ecdb_ahdr->ahslength = cpu_to_be16(ahslength);
	ecdb_ahdr->ahstype = ISCSI_AHSTYPE_CDB;
	ecdb_ahdr->reserved = 0;
	memcpy(ecdb_ahdr->ecdb, cmd->cmnd + ISCSI_CDB_SIZE, rlen);

	ISCSI_DBG_SESSION(task->conn->session,
			  "iscsi_prep_ecdb_ahs: varlen_cdb_len %d "
		          "rlen %d pad_len %d ahs_length %d iscsi_headers_size "
		          "%u\n", cmd->cmd_len, rlen, pad_len, ahslength,
		          task->hdr_len);
	return 0;
}