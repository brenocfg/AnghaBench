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
struct scsi_lun {int dummy; } ;
struct scsi_cmnd {scalar_t__ sc_data_direction; TYPE_1__* device; int /*<<< orphan*/  cmd_len; int /*<<< orphan*/  cmnd; } ;
struct fcp_cmnd {int fc_dl; int /*<<< orphan*/  fc_cdb; int /*<<< orphan*/  fc_flags; int /*<<< orphan*/  fc_pri_ta; int /*<<< orphan*/  fc_lun; } ;
struct TYPE_2__ {int sector_size; int /*<<< orphan*/  lun; } ;

/* Variables and functions */
 scalar_t__ DMA_FROM_DEVICE ; 
 scalar_t__ DMA_TO_DEVICE ; 
 int /*<<< orphan*/  FCP_CFL_RDDATA ; 
 int /*<<< orphan*/  FCP_CFL_WRDATA ; 
 int /*<<< orphan*/  FCP_PTA_ORDERED ; 
 int /*<<< orphan*/  FCP_PTA_SIMPLE ; 
#define  MSG_ORDERED_TAG 129 
#define  MSG_SIMPLE_TAG 128 
 scalar_t__ SCSI_PROT_DIF_TYPE1 ; 
 int /*<<< orphan*/  int_to_scsilun (int /*<<< orphan*/ ,struct scsi_lun*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int scsi_bufflen (struct scsi_cmnd*) ; 
 scalar_t__ scsi_get_prot_type (struct scsi_cmnd*) ; 
 scalar_t__ scsi_populate_tag_msg (struct scsi_cmnd*,char*) ; 

__attribute__((used)) static inline
void zfcp_fc_scsi_to_fcp(struct fcp_cmnd *fcp, struct scsi_cmnd *scsi)
{
	char tag[2];

	int_to_scsilun(scsi->device->lun, (struct scsi_lun *) &fcp->fc_lun);

	if (scsi_populate_tag_msg(scsi, tag)) {
		switch (tag[0]) {
		case MSG_ORDERED_TAG:
			fcp->fc_pri_ta |= FCP_PTA_ORDERED;
			break;
		case MSG_SIMPLE_TAG:
			fcp->fc_pri_ta |= FCP_PTA_SIMPLE;
			break;
		};
	} else
		fcp->fc_pri_ta = FCP_PTA_SIMPLE;

	if (scsi->sc_data_direction == DMA_FROM_DEVICE)
		fcp->fc_flags |= FCP_CFL_RDDATA;
	if (scsi->sc_data_direction == DMA_TO_DEVICE)
		fcp->fc_flags |= FCP_CFL_WRDATA;

	memcpy(fcp->fc_cdb, scsi->cmnd, scsi->cmd_len);

	fcp->fc_dl = scsi_bufflen(scsi);

	if (scsi_get_prot_type(scsi) == SCSI_PROT_DIF_TYPE1)
		fcp->fc_dl += fcp->fc_dl / scsi->device->sector_size * 8;
}