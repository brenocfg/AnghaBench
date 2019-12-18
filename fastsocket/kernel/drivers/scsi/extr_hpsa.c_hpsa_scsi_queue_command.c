#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int result; void (* scsi_done ) (struct scsi_cmnd*) ;unsigned char* host_scribble; int cmd_len; unsigned char* cmnd; int sc_data_direction; TYPE_7__* device; } ;
struct hpsa_scsi_dev_t {unsigned char* scsi3addr; } ;
struct ctlr_info {TYPE_6__* pdev; int /*<<< orphan*/  lock; int /*<<< orphan*/  lockup_detected; } ;
struct TYPE_11__ {int /*<<< orphan*/  Direction; int /*<<< orphan*/  Attribute; int /*<<< orphan*/  Type; } ;
struct TYPE_12__ {unsigned char* CDB; int CDBLen; TYPE_4__ Type; scalar_t__ Timeout; } ;
struct TYPE_9__ {int lower; } ;
struct TYPE_8__ {unsigned char* LunAddrBytes; } ;
struct TYPE_10__ {TYPE_2__ Tag; TYPE_1__ LUN; scalar_t__ ReplyQueue; } ;
struct CommandList {int cmdindex; TYPE_5__ Request; TYPE_3__ Header; struct scsi_cmnd* scsi_cmd; int /*<<< orphan*/  cmd_type; } ;
typedef  int /*<<< orphan*/  scsi3addr ;
struct TYPE_14__ {struct hpsa_scsi_dev_t* hostdata; } ;
struct TYPE_13__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_SIMPLE ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CMD_SCSI ; 
 int DID_ERROR ; 
 int DID_NO_CONNECT ; 
 int DIRECT_LOOKUP_BIT ; 
 int DIRECT_LOOKUP_SHIFT ; 
#define  DMA_BIDIRECTIONAL 131 
#define  DMA_FROM_DEVICE 130 
#define  DMA_NONE 129 
#define  DMA_TO_DEVICE 128 
 int SCSI_MLQUEUE_HOST_BUSY ; 
 int /*<<< orphan*/  TYPE_CMD ; 
 int /*<<< orphan*/  XFER_NONE ; 
 int /*<<< orphan*/  XFER_READ ; 
 int /*<<< orphan*/  XFER_RSVD ; 
 int /*<<< orphan*/  XFER_WRITE ; 
 struct CommandList* cmd_alloc (struct ctlr_info*) ; 
 int /*<<< orphan*/  cmd_free (struct ctlr_info*,struct CommandList*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  enqueue_cmd_and_start_io (struct ctlr_info*,struct CommandList*) ; 
 scalar_t__ hpsa_scatter_gather (struct ctlr_info*,struct CommandList*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 struct ctlr_info* sdev_to_hba (TYPE_7__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpsa_scsi_queue_command(struct scsi_cmnd *cmd,
	void (*done)(struct scsi_cmnd *))
{
	struct ctlr_info *h;
	struct hpsa_scsi_dev_t *dev;
	unsigned char scsi3addr[8];
	struct CommandList *c;
	unsigned long flags;

	/* Get the ptr to our adapter structure out of cmd->host. */
	h = sdev_to_hba(cmd->device);
	dev = cmd->device->hostdata;
	if (!dev) {
		cmd->result = DID_NO_CONNECT << 16;
		done(cmd);
		return 0;
	}
	memcpy(scsi3addr, dev->scsi3addr, sizeof(scsi3addr));

	spin_lock_irqsave(&h->lock, flags);
	if (unlikely(h->lockup_detected)) {
		spin_unlock_irqrestore(&h->lock, flags);
		cmd->result = DID_ERROR << 16;
		done(cmd);
		return 0;
	}
	spin_unlock_irqrestore(&h->lock, flags);
	c = cmd_alloc(h);
	if (c == NULL) {			/* trouble... */
		dev_err(&h->pdev->dev, "cmd_alloc returned NULL!\n");
		return SCSI_MLQUEUE_HOST_BUSY;
	}

	/* Fill in the command list header */

	cmd->scsi_done = done;    /* save this for use by completion code */

	/* save c in case we have to abort it  */
	cmd->host_scribble = (unsigned char *) c;

	c->cmd_type = CMD_SCSI;
	c->scsi_cmd = cmd;
	c->Header.ReplyQueue = 0;  /* unused in simple mode */
	memcpy(&c->Header.LUN.LunAddrBytes[0], &scsi3addr[0], 8);
	c->Header.Tag.lower = (c->cmdindex << DIRECT_LOOKUP_SHIFT);
	c->Header.Tag.lower |= DIRECT_LOOKUP_BIT;

	/* Fill in the request block... */

	c->Request.Timeout = 0;
	memset(c->Request.CDB, 0, sizeof(c->Request.CDB));
	BUG_ON(cmd->cmd_len > sizeof(c->Request.CDB));
	c->Request.CDBLen = cmd->cmd_len;
	memcpy(c->Request.CDB, cmd->cmnd, cmd->cmd_len);
	c->Request.Type.Type = TYPE_CMD;
	c->Request.Type.Attribute = ATTR_SIMPLE;
	switch (cmd->sc_data_direction) {
	case DMA_TO_DEVICE:
		c->Request.Type.Direction = XFER_WRITE;
		break;
	case DMA_FROM_DEVICE:
		c->Request.Type.Direction = XFER_READ;
		break;
	case DMA_NONE:
		c->Request.Type.Direction = XFER_NONE;
		break;
	case DMA_BIDIRECTIONAL:
		/* This can happen if a buggy application does a scsi passthru
		 * and sets both inlen and outlen to non-zero. ( see
		 * ../scsi/scsi_ioctl.c:scsi_ioctl_send_command() )
		 */

		c->Request.Type.Direction = XFER_RSVD;
		/* This is technically wrong, and hpsa controllers should
		 * reject it with CMD_INVALID, which is the most correct
		 * response, but non-fibre backends appear to let it
		 * slide by, and give the same results as if this field
		 * were set correctly.  Either way is acceptable for
		 * our purposes here.
		 */

		break;

	default:
		dev_err(&h->pdev->dev, "unknown data direction: %d\n",
			cmd->sc_data_direction);
		BUG();
		break;
	}

	if (hpsa_scatter_gather(h, c, cmd) < 0) { /* Fill SG list */
		cmd_free(h, c);
		return SCSI_MLQUEUE_HOST_BUSY;
	}
	enqueue_cmd_and_start_io(h, c);
	/* the cmd'll come back via intr handler in complete_scsi_command()  */
	return 0;
}