#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct ipr_resource_entry {TYPE_11__* sata_port; int /*<<< orphan*/  res_handle; } ;
struct ipr_ioasa_gata {int dummy; } ;
struct ipr_ioarcb_ata_regs {int /*<<< orphan*/  flags; } ;
struct TYPE_22__ {struct ipr_ioarcb_ata_regs regs; } ;
struct TYPE_23__ {TYPE_3__ u; } ;
struct TYPE_24__ {TYPE_4__ add_data; } ;
struct ipr_cmd_pkt {int /*<<< orphan*/ * cdb; int /*<<< orphan*/  request_type; } ;
struct ipr_ioarcb {void* add_cmd_parms_len; int /*<<< orphan*/  res_handle; TYPE_5__ u; void* add_cmd_parms_offset; struct ipr_cmd_pkt cmd_pkt; } ;
struct ipr_ioa_cfg {int dummy; } ;
struct TYPE_17__ {int /*<<< orphan*/  gata; } ;
struct TYPE_25__ {int /*<<< orphan*/  ioasc; } ;
struct TYPE_18__ {TYPE_12__ u; TYPE_6__ hdr; } ;
struct TYPE_28__ {int /*<<< orphan*/  gata; } ;
struct TYPE_15__ {TYPE_9__ u; } ;
struct TYPE_19__ {TYPE_13__ ioasa; TYPE_10__ ioasa64; } ;
struct TYPE_20__ {struct ipr_ioarcb_ata_regs regs; } ;
struct TYPE_21__ {TYPE_1__ ata_ioadl; } ;
struct ipr_cmnd {TYPE_14__ s; TYPE_8__* ioa_cfg; TYPE_7__* hrrq; int /*<<< orphan*/  queue; TYPE_2__ i; struct ipr_ioarcb ioarcb; } ;
struct TYPE_27__ {scalar_t__ sis64; } ;
struct TYPE_26__ {int /*<<< orphan*/  hrrq_free_q; } ;
struct TYPE_16__ {int /*<<< orphan*/  ioasa; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ENTER ; 
 int /*<<< orphan*/  IPR_ATA_FLAG_STATUS_ON_GOOD_COMPLETION ; 
 int /*<<< orphan*/  IPR_ATA_PHY_RESET ; 
 int /*<<< orphan*/  IPR_DEVICE_RESET_TIMEOUT ; 
 scalar_t__ IPR_IOASC_IOA_WAS_RESET ; 
 scalar_t__ IPR_IOASC_SENSE_KEY (scalar_t__) ; 
 int /*<<< orphan*/  IPR_RESET_DEVICE ; 
 int /*<<< orphan*/  IPR_RQTYPE_IOACMD ; 
 int /*<<< orphan*/  LEAVE ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be16 (int) ; 
 struct ipr_cmnd* ipr_get_free_ipr_cmnd (struct ipr_ioa_cfg*) ; 
 scalar_t__ ipr_is_gata (struct ipr_resource_entry*) ; 
 int /*<<< orphan*/  ipr_send_blocking_cmd (struct ipr_cmnd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipr_timeout ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ipr_device_reset(struct ipr_ioa_cfg *ioa_cfg,
			    struct ipr_resource_entry *res)
{
	struct ipr_cmnd *ipr_cmd;
	struct ipr_ioarcb *ioarcb;
	struct ipr_cmd_pkt *cmd_pkt;
	struct ipr_ioarcb_ata_regs *regs;
	u32 ioasc;

	ENTER;
	ipr_cmd = ipr_get_free_ipr_cmnd(ioa_cfg);
	ioarcb = &ipr_cmd->ioarcb;
	cmd_pkt = &ioarcb->cmd_pkt;

	if (ipr_cmd->ioa_cfg->sis64) {
		regs = &ipr_cmd->i.ata_ioadl.regs;
		ioarcb->add_cmd_parms_offset = cpu_to_be16(sizeof(*ioarcb));
	} else
		regs = &ioarcb->u.add_data.u.regs;

	ioarcb->res_handle = res->res_handle;
	cmd_pkt->request_type = IPR_RQTYPE_IOACMD;
	cmd_pkt->cdb[0] = IPR_RESET_DEVICE;
	if (ipr_is_gata(res)) {
		cmd_pkt->cdb[2] = IPR_ATA_PHY_RESET;
		ioarcb->add_cmd_parms_len = cpu_to_be16(sizeof(regs->flags));
		regs->flags |= IPR_ATA_FLAG_STATUS_ON_GOOD_COMPLETION;
	}

	ipr_send_blocking_cmd(ipr_cmd, ipr_timeout, IPR_DEVICE_RESET_TIMEOUT);
	ioasc = be32_to_cpu(ipr_cmd->s.ioasa.hdr.ioasc);
	list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_free_q);
	if (ipr_is_gata(res) && res->sata_port && ioasc != IPR_IOASC_IOA_WAS_RESET) {
		if (ipr_cmd->ioa_cfg->sis64)
			memcpy(&res->sata_port->ioasa, &ipr_cmd->s.ioasa64.u.gata,
			       sizeof(struct ipr_ioasa_gata));
		else
			memcpy(&res->sata_port->ioasa, &ipr_cmd->s.ioasa.u.gata,
			       sizeof(struct ipr_ioasa_gata));
	}

	LEAVE;
	return (IPR_IOASC_SENSE_KEY(ioasc) ? -EIO : 0);
}