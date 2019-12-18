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
typedef  int u8 ;
typedef  int /*<<< orphan*/  tries_buf ;
struct ata_taskfile {size_t protocol; int command; int feature; int /*<<< orphan*/  device; int /*<<< orphan*/  hob_lbah; int /*<<< orphan*/  hob_lbam; int /*<<< orphan*/  hob_lbal; int /*<<< orphan*/  hob_nsect; int /*<<< orphan*/  hob_feature; int /*<<< orphan*/  lbah; int /*<<< orphan*/  lbam; int /*<<< orphan*/  lbal; int /*<<< orphan*/  nsect; } ;
struct ata_queued_cmd {int flags; scalar_t__ err_mask; int* cdb; scalar_t__ dma_dir; int nbytes; int /*<<< orphan*/  dev; int /*<<< orphan*/  tag; scalar_t__ scsicmd; struct ata_taskfile tf; struct ata_taskfile result_tf; } ;
struct ata_port {int pflags; scalar_t__ eh_tries; } ;
struct TYPE_2__ {int flags; char* desc; int serror; int /*<<< orphan*/  action; int /*<<< orphan*/  err_mask; scalar_t__ dev; } ;
struct ata_eh_context {TYPE_1__ i; } ;
struct ata_link {int /*<<< orphan*/  sactive; struct ata_eh_context eh_context; struct ata_port* ap; } ;
typedef  int /*<<< orphan*/  data_buf ;
typedef  int /*<<< orphan*/  cdb_buf ;

/* Variables and functions */
 scalar_t__ AC_ERR_DEV ; 
 int AC_ERR_NCQ ; 
#define  ATAPI_PROT_DMA 135 
#define  ATAPI_PROT_PIO 134 
 int ATA_ABORTED ; 
 int ATA_BUSY ; 
 int ATA_CMD_PACKET ; 
 int ATA_DF ; 
 int ATA_DRDY ; 
 int ATA_DRQ ; 
 int ATA_EHI_QUIET ; 
 scalar_t__ ATA_EH_MAX_TRIES ; 
 int ATA_ERR ; 
 int ATA_ICRC ; 
 int ATA_IDNF ; 
 int ATA_MAX_QUEUE ; 
 int ATA_PFLAG_FROZEN ; 
#define  ATA_PROT_DMA 133 
#define  ATA_PROT_NCQ 132 
#define  ATA_PROT_PIO 131 
 int ATA_QCFLAG_FAILED ; 
 int ATA_QCFLAG_QUIET ; 
 int ATA_QCFLAG_SENSE_VALID ; 
 int ATA_UNC ; 
#define  DMA_BIDIRECTIONAL 130 
#define  DMA_FROM_DEVICE 129 
 scalar_t__ DMA_NONE ; 
#define  DMA_TO_DEVICE 128 
 int /*<<< orphan*/  KERN_ERR ; 
 int SERR_10B_8B_ERR ; 
 int SERR_COMM_RECOVERED ; 
 int SERR_COMM_WAKE ; 
 int SERR_CRC ; 
 int SERR_DATA ; 
 int SERR_DATA_RECOVERED ; 
 int SERR_DEV_XCHG ; 
 int SERR_DISPARITY ; 
 int SERR_HANDSHAKE ; 
 int SERR_INTERNAL ; 
 int SERR_LINK_SEQ_ERR ; 
 int SERR_PERSISTENT ; 
 int SERR_PHYRDY_CHG ; 
 int SERR_PHY_INT_ERR ; 
 int SERR_PROTOCOL ; 
 int SERR_TRANS_ST_ERROR ; 
 int SERR_UNRECOG_FIS ; 
 struct ata_queued_cmd* __ata_qc_from_tag (struct ata_port*,int) ; 
 struct ata_link* ata_dev_phys_link (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ata_err_string (scalar_t__) ; 
 char* ata_get_cmd_descript (int) ; 
 scalar_t__ ata_is_atapi (size_t) ; 
 int /*<<< orphan*/  ata_link_printk (struct ata_link*,int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_print_command (scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static void ata_eh_link_report(struct ata_link *link)
{
	struct ata_port *ap = link->ap;
	struct ata_eh_context *ehc = &link->eh_context;
	const char *frozen, *desc;
	char tries_buf[6];
	int tag, nr_failed = 0;

	if (ehc->i.flags & ATA_EHI_QUIET)
		return;

	desc = NULL;
	if (ehc->i.desc[0] != '\0')
		desc = ehc->i.desc;

	for (tag = 0; tag < ATA_MAX_QUEUE; tag++) {
		struct ata_queued_cmd *qc = __ata_qc_from_tag(ap, tag);

		if (!(qc->flags & ATA_QCFLAG_FAILED) ||
		    ata_dev_phys_link(qc->dev) != link ||
		    ((qc->flags & ATA_QCFLAG_QUIET) &&
		     qc->err_mask == AC_ERR_DEV))
			continue;
		if (qc->flags & ATA_QCFLAG_SENSE_VALID && !qc->err_mask)
			continue;

		nr_failed++;
	}

	if (!nr_failed && !ehc->i.err_mask)
		return;

	frozen = "";
	if (ap->pflags & ATA_PFLAG_FROZEN)
		frozen = " frozen";

	memset(tries_buf, 0, sizeof(tries_buf));
	if (ap->eh_tries < ATA_EH_MAX_TRIES)
		snprintf(tries_buf, sizeof(tries_buf) - 1, " t%d",
			 ap->eh_tries);

	if (ehc->i.dev) {
		ata_dev_printk(ehc->i.dev, KERN_ERR, "exception Emask 0x%x "
			       "SAct 0x%x SErr 0x%x action 0x%x%s%s\n",
			       ehc->i.err_mask, link->sactive, ehc->i.serror,
			       ehc->i.action, frozen, tries_buf);
		if (desc)
			ata_dev_printk(ehc->i.dev, KERN_ERR, "%s\n", desc);
	} else {
		ata_link_printk(link, KERN_ERR, "exception Emask 0x%x "
				"SAct 0x%x SErr 0x%x action 0x%x%s%s\n",
				ehc->i.err_mask, link->sactive, ehc->i.serror,
				ehc->i.action, frozen, tries_buf);
		if (desc)
			ata_link_printk(link, KERN_ERR, "%s\n", desc);
	}

#ifdef CONFIG_ATA_VERBOSE_ERROR
	if (ehc->i.serror)
		ata_link_printk(link, KERN_ERR,
		  "SError: { %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s}\n",
		  ehc->i.serror & SERR_DATA_RECOVERED ? "RecovData " : "",
		  ehc->i.serror & SERR_COMM_RECOVERED ? "RecovComm " : "",
		  ehc->i.serror & SERR_DATA ? "UnrecovData " : "",
		  ehc->i.serror & SERR_PERSISTENT ? "Persist " : "",
		  ehc->i.serror & SERR_PROTOCOL ? "Proto " : "",
		  ehc->i.serror & SERR_INTERNAL ? "HostInt " : "",
		  ehc->i.serror & SERR_PHYRDY_CHG ? "PHYRdyChg " : "",
		  ehc->i.serror & SERR_PHY_INT_ERR ? "PHYInt " : "",
		  ehc->i.serror & SERR_COMM_WAKE ? "CommWake " : "",
		  ehc->i.serror & SERR_10B_8B_ERR ? "10B8B " : "",
		  ehc->i.serror & SERR_DISPARITY ? "Dispar " : "",
		  ehc->i.serror & SERR_CRC ? "BadCRC " : "",
		  ehc->i.serror & SERR_HANDSHAKE ? "Handshk " : "",
		  ehc->i.serror & SERR_LINK_SEQ_ERR ? "LinkSeq " : "",
		  ehc->i.serror & SERR_TRANS_ST_ERROR ? "TrStaTrns " : "",
		  ehc->i.serror & SERR_UNRECOG_FIS ? "UnrecFIS " : "",
		  ehc->i.serror & SERR_DEV_XCHG ? "DevExch " : "");
#endif

	for (tag = 0; tag < ATA_MAX_QUEUE; tag++) {
		struct ata_queued_cmd *qc = __ata_qc_from_tag(ap, tag);
		struct ata_taskfile *cmd = &qc->tf, *res = &qc->result_tf;
		const u8 *cdb = qc->cdb;
		char data_buf[20] = "";
		char cdb_buf[70] = "";

		if (!(qc->flags & ATA_QCFLAG_FAILED) ||
		    ata_dev_phys_link(qc->dev) != link || !qc->err_mask)
			continue;

		if (qc->dma_dir != DMA_NONE) {
			static const char *dma_str[] = {
				[DMA_BIDIRECTIONAL]	= "bidi",
				[DMA_TO_DEVICE]		= "out",
				[DMA_FROM_DEVICE]	= "in",
			};
			static const char *prot_str[] = {
				[ATA_PROT_PIO]		= "pio",
				[ATA_PROT_DMA]		= "dma",
				[ATA_PROT_NCQ]		= "ncq",
				[ATAPI_PROT_PIO]	= "pio",
				[ATAPI_PROT_DMA]	= "dma",
			};

			snprintf(data_buf, sizeof(data_buf), " %s %u %s",
				 prot_str[qc->tf.protocol], qc->nbytes,
				 dma_str[qc->dma_dir]);
		}

		if (ata_is_atapi(qc->tf.protocol)) {
			if (qc->scsicmd)
				scsi_print_command(qc->scsicmd);
			else
				snprintf(cdb_buf, sizeof(cdb_buf),
				 "cdb %02x %02x %02x %02x %02x %02x %02x %02x  "
				 "%02x %02x %02x %02x %02x %02x %02x %02x\n         ",
				 cdb[0], cdb[1], cdb[2], cdb[3],
				 cdb[4], cdb[5], cdb[6], cdb[7],
				 cdb[8], cdb[9], cdb[10], cdb[11],
				 cdb[12], cdb[13], cdb[14], cdb[15]);
		} else {
			const char *descr = ata_get_cmd_descript(cmd->command);
			if (descr)
				ata_dev_printk(qc->dev, KERN_ERR,
					"failed command: %s\n", descr);
		}

		ata_dev_printk(qc->dev, KERN_ERR,
			"cmd %02x/%02x:%02x:%02x:%02x:%02x/%02x:%02x:%02x:%02x:%02x/%02x "
			"tag %d%s\n         %s"
			"res %02x/%02x:%02x:%02x:%02x:%02x/%02x:%02x:%02x:%02x:%02x/%02x "
			"Emask 0x%x (%s)%s\n",
			cmd->command, cmd->feature, cmd->nsect,
			cmd->lbal, cmd->lbam, cmd->lbah,
			cmd->hob_feature, cmd->hob_nsect,
			cmd->hob_lbal, cmd->hob_lbam, cmd->hob_lbah,
			cmd->device, qc->tag, data_buf, cdb_buf,
			res->command, res->feature, res->nsect,
			res->lbal, res->lbam, res->lbah,
			res->hob_feature, res->hob_nsect,
			res->hob_lbal, res->hob_lbam, res->hob_lbah,
			res->device, qc->err_mask, ata_err_string(qc->err_mask),
			qc->err_mask & AC_ERR_NCQ ? " <F>" : "");

#ifdef CONFIG_ATA_VERBOSE_ERROR
		if (res->command & (ATA_BUSY | ATA_DRDY | ATA_DF | ATA_DRQ |
				    ATA_ERR)) {
			if (res->command & ATA_BUSY)
				ata_dev_printk(qc->dev, KERN_ERR,
				  "status: { Busy }\n");
			else
				ata_dev_printk(qc->dev, KERN_ERR,
				  "status: { %s%s%s%s}\n",
				  res->command & ATA_DRDY ? "DRDY " : "",
				  res->command & ATA_DF ? "DF " : "",
				  res->command & ATA_DRQ ? "DRQ " : "",
				  res->command & ATA_ERR ? "ERR " : "");
		}

		if (cmd->command != ATA_CMD_PACKET &&
		    (res->feature & (ATA_ICRC | ATA_UNC | ATA_IDNF |
				     ATA_ABORTED)))
			ata_dev_printk(qc->dev, KERN_ERR,
			  "error: { %s%s%s%s}\n",
			  res->feature & ATA_ICRC ? "ICRC " : "",
			  res->feature & ATA_UNC ? "UNC " : "",
			  res->feature & ATA_IDNF ? "IDNF " : "",
			  res->feature & ATA_ABORTED ? "ABRT " : "");
#endif
	}
}