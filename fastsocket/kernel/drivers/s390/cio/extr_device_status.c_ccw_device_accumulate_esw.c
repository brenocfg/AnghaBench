#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct sublog {int /*<<< orphan*/  ioerr; int /*<<< orphan*/  serr; int /*<<< orphan*/  devsc; int /*<<< orphan*/  seqc; int /*<<< orphan*/  termc; int /*<<< orphan*/  sacc; int /*<<< orphan*/  fvf; int /*<<< orphan*/  arep; int /*<<< orphan*/  esf; } ;
struct TYPE_14__ {int /*<<< orphan*/  scnt; scalar_t__ cons; scalar_t__ pvrf; int /*<<< orphan*/  auth; scalar_t__ scavf; int /*<<< orphan*/  fsaf; scalar_t__ fsavf; int /*<<< orphan*/  cpt; } ;
struct TYPE_15__ {TYPE_6__ erw; int /*<<< orphan*/  saddr; int /*<<< orphan*/  faddr; struct sublog sublog; } ;
struct TYPE_9__ {int /*<<< orphan*/  lpum; } ;
struct TYPE_16__ {TYPE_7__ esw0; TYPE_1__ esw1; } ;
struct TYPE_10__ {int cstat; scalar_t__ eswf; } ;
struct TYPE_11__ {TYPE_2__ cmd; } ;
struct irb {TYPE_8__ esw; TYPE_3__ scsw; } ;
struct ccw_device {TYPE_5__* private; } ;
struct TYPE_12__ {int doverify; } ;
struct TYPE_13__ {TYPE_4__ flags; struct irb irb; } ;

/* Variables and functions */
 int SCHN_STAT_CHN_CTRL_CHK ; 
 int SCHN_STAT_CHN_DATA_CHK ; 
 int SCHN_STAT_INTF_CTRL_CHK ; 
 int /*<<< orphan*/  ccw_device_accumulate_esw_valid (struct irb*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ccw_device_accumulate_esw(struct ccw_device *cdev, struct irb *irb)
{
	struct irb *cdev_irb;
	struct sublog *cdev_sublog, *sublog;

	if (!ccw_device_accumulate_esw_valid(irb))
		return;

	cdev_irb = &cdev->private->irb;

	/* Copy last path used mask. */
	cdev_irb->esw.esw1.lpum = irb->esw.esw1.lpum;

	/* Copy subchannel logout information if esw is of format 0. */
	if (irb->scsw.cmd.eswf) {
		cdev_sublog = &cdev_irb->esw.esw0.sublog;
		sublog = &irb->esw.esw0.sublog;
		/* Copy extended status flags. */
		cdev_sublog->esf = sublog->esf;
		/*
		 * Copy fields that have a meaning for channel data check
		 * channel control check and interface control check.
		 */
		if (irb->scsw.cmd.cstat & (SCHN_STAT_CHN_DATA_CHK |
				       SCHN_STAT_CHN_CTRL_CHK |
				       SCHN_STAT_INTF_CTRL_CHK)) {
			/* Copy ancillary report bit. */
			cdev_sublog->arep = sublog->arep;
			/* Copy field-validity-flags. */
			cdev_sublog->fvf = sublog->fvf;
			/* Copy storage access code. */
			cdev_sublog->sacc = sublog->sacc;
			/* Copy termination code. */
			cdev_sublog->termc = sublog->termc;
			/* Copy sequence code. */
			cdev_sublog->seqc = sublog->seqc;
		}
		/* Copy device status check. */
		cdev_sublog->devsc = sublog->devsc;
		/* Copy secondary error. */
		cdev_sublog->serr = sublog->serr;
		/* Copy i/o-error alert. */
		cdev_sublog->ioerr = sublog->ioerr;
		/* Copy channel path timeout bit. */
		if (irb->scsw.cmd.cstat & SCHN_STAT_INTF_CTRL_CHK)
			cdev_irb->esw.esw0.erw.cpt = irb->esw.esw0.erw.cpt;
		/* Copy failing storage address validity flag. */
		cdev_irb->esw.esw0.erw.fsavf = irb->esw.esw0.erw.fsavf;
		if (cdev_irb->esw.esw0.erw.fsavf) {
			/* ... and copy the failing storage address. */
			memcpy(cdev_irb->esw.esw0.faddr, irb->esw.esw0.faddr,
			       sizeof (irb->esw.esw0.faddr));
			/* ... and copy the failing storage address format. */
			cdev_irb->esw.esw0.erw.fsaf = irb->esw.esw0.erw.fsaf;
		}
		/* Copy secondary ccw address validity bit. */
		cdev_irb->esw.esw0.erw.scavf = irb->esw.esw0.erw.scavf;
		if (irb->esw.esw0.erw.scavf)
			/* ... and copy the secondary ccw address. */
			cdev_irb->esw.esw0.saddr = irb->esw.esw0.saddr;
		
	}
	/* FIXME: DCTI for format 2? */

	/* Copy authorization bit. */
	cdev_irb->esw.esw0.erw.auth = irb->esw.esw0.erw.auth;
	/* Copy path verification required flag. */
	cdev_irb->esw.esw0.erw.pvrf = irb->esw.esw0.erw.pvrf;
	if (irb->esw.esw0.erw.pvrf)
		cdev->private->flags.doverify = 1;
	/* Copy concurrent sense bit. */
	cdev_irb->esw.esw0.erw.cons = irb->esw.esw0.erw.cons;
	if (irb->esw.esw0.erw.cons)
		cdev_irb->esw.esw0.erw.scnt = irb->esw.esw0.erw.scnt;
}