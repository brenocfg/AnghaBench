#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ctlr_info {TYPE_1__* pdev; } ;
struct ReportLUNdata {int dummy; } ;
struct ErrorInfo {scalar_t__ CommandStatus; } ;
struct TYPE_4__ {int* CDB; } ;
struct CommandList {struct ErrorInfo* err_info; TYPE_2__ Request; } ;
typedef  int /*<<< orphan*/  scsi3addr ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CMD_DATA_UNDERRUN ; 
 int /*<<< orphan*/  HPSA_REPORT_LOG ; 
 int /*<<< orphan*/  HPSA_REPORT_PHYS ; 
 int IO_OK ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  TYPE_CMD ; 
 struct CommandList* cmd_special_alloc (struct ctlr_info*) ; 
 int /*<<< orphan*/  cmd_special_free (struct ctlr_info*,struct CommandList*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fill_cmd (struct CommandList*,int /*<<< orphan*/ ,struct ctlr_info*,struct ReportLUNdata*,int,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpsa_scsi_do_simple_cmd_with_retry (struct ctlr_info*,struct CommandList*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpsa_scsi_interpret_error (struct CommandList*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hpsa_scsi_do_report_luns(struct ctlr_info *h, int logical,
		struct ReportLUNdata *buf, int bufsize,
		int extended_response)
{
	int rc = IO_OK;
	struct CommandList *c;
	unsigned char scsi3addr[8];
	struct ErrorInfo *ei;

	c = cmd_special_alloc(h);
	if (c == NULL) {			/* trouble... */
		dev_err(&h->pdev->dev, "cmd_special_alloc returned NULL!\n");
		return -1;
	}
	/* address the controller */
	memset(scsi3addr, 0, sizeof(scsi3addr));
	fill_cmd(c, logical ? HPSA_REPORT_LOG : HPSA_REPORT_PHYS, h,
		buf, bufsize, 0, scsi3addr, TYPE_CMD);
	if (extended_response)
		c->Request.CDB[1] = extended_response;
	hpsa_scsi_do_simple_cmd_with_retry(h, c, PCI_DMA_FROMDEVICE);
	ei = c->err_info;
	if (ei->CommandStatus != 0 &&
	    ei->CommandStatus != CMD_DATA_UNDERRUN) {
		hpsa_scsi_interpret_error(c);
		rc = -1;
	}
	cmd_special_free(h, c);
	return rc;
}