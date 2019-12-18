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
struct scsi_qla_host {size_t devnum; int fwver1; int fwver2; int fwver3; } ;
struct qla_boards {char* name; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  int /*<<< orphan*/  qla1280_scsi_name_buffer ;

/* Variables and functions */
 char* QLA1280_VERSION ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 struct qla_boards* ql1280_board_tbl ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int,int,int,char*) ; 

__attribute__((used)) static const char *
qla1280_info(struct Scsi_Host *host)
{
	static char qla1280_scsi_name_buffer[125];
	char *bp;
	struct scsi_qla_host *ha;
	struct qla_boards *bdp;

	bp = &qla1280_scsi_name_buffer[0];
	ha = (struct scsi_qla_host *)host->hostdata;
	bdp = &ql1280_board_tbl[ha->devnum];
	memset(bp, 0, sizeof(qla1280_scsi_name_buffer));

	sprintf (bp,
		 "QLogic %s PCI to SCSI Host Adapter\n"
		 "       Firmware version: %2d.%02d.%02d, Driver version %s",
		 &bdp->name[0], ha->fwver1, ha->fwver2, ha->fwver3,
		 QLA1280_VERSION);
	return bp;
}