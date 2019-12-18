#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct scb_tailq {int dummy; } ;
struct scb {TYPE_3__* hscb; int /*<<< orphan*/  flags; int /*<<< orphan*/  io_ctx; } ;
struct ahc_tmode_tstate {int dummy; } ;
struct ahc_softc {int flags; struct scb_tailq* untagged_queues; scalar_t__ msgout_index; scalar_t__ msgout_len; } ;
struct TYPE_6__ {int transport_version; scalar_t__ offset; } ;
struct TYPE_5__ {int transport_version; scalar_t__ offset; scalar_t__ ppr_options; } ;
struct ahc_initiator_tinfo {TYPE_2__ curr; TYPE_1__ goal; } ;
struct ahc_devinfo {int channel; int target; int lun; size_t target_offset; int /*<<< orphan*/  our_scsiid; } ;
struct TYPE_8__ {int /*<<< orphan*/  tqe; } ;
struct TYPE_7__ {int control; int /*<<< orphan*/  tag; int /*<<< orphan*/  scsiid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHCMSG_EXT ; 
 int /*<<< orphan*/  AHC_QUEUE_BASIC ; 
 int /*<<< orphan*/  AHC_QUEUE_NONE ; 
 int AHC_SCB_BTT ; 
 int AHC_TRANS_ACTIVE ; 
 int AHC_TRANS_GOAL ; 
 int /*<<< orphan*/  BUILD_TCL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CAM_REQUEUE_REQ ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LAST_MSG ; 
 int /*<<< orphan*/  MSG_EXT_PPR ; 
 int /*<<< orphan*/  MSG_EXT_SDTR ; 
 int /*<<< orphan*/  MSG_EXT_WDTR ; 
 int /*<<< orphan*/  MSG_EXT_WDTR_BUS_8_BIT ; 
 int MSG_IDENTIFYFLAG ; 
 int MSG_ORDERED_TASK ; 
 int /*<<< orphan*/  MSG_OUT ; 
 int MSG_SIMPLE_TASK ; 
 int /*<<< orphan*/  ROLE_INITIATOR ; 
 int /*<<< orphan*/  SCB_CONTROL ; 
 int /*<<< orphan*/  SCB_GET_CHANNEL (struct ahc_softc*,struct scb*) ; 
 int /*<<< orphan*/  SCB_GET_LUN (struct scb*) ; 
 int /*<<< orphan*/  SCB_GET_TARGET (struct ahc_softc*,struct scb*) ; 
 int /*<<< orphan*/  SCB_LIST_NULL ; 
 int /*<<< orphan*/  SCB_TAG ; 
 int /*<<< orphan*/  SCB_UNTAGGEDQ ; 
 int /*<<< orphan*/  SEARCH_COMPLETE ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (struct scb_tailq*,struct scb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ahc_assert_atn (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_build_transfer_msg (struct ahc_softc*,struct ahc_devinfo*) ; 
 int /*<<< orphan*/  ahc_busy_tcl (struct ahc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ahc_initiator_tinfo* ahc_fetch_transinfo (struct ahc_softc*,int,int /*<<< orphan*/ ,int,struct ahc_tmode_tstate**) ; 
 int ahc_inb (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 struct scb* ahc_lookup_scb (struct ahc_softc*,int) ; 
 char* ahc_name (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_outb (struct ahc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ahc_search_qinfifo (struct ahc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ahc_sent_msg (struct ahc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_set_syncrate (struct ahc_softc*,struct ahc_devinfo*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_set_tags (struct ahc_softc*,int /*<<< orphan*/ ,struct ahc_devinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_set_transaction_tag (struct scb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ahc_set_width (struct ahc_softc*,struct ahc_devinfo*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 TYPE_4__ links ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int,...) ; 

__attribute__((used)) static int
ahc_handle_msg_reject(struct ahc_softc *ahc, struct ahc_devinfo *devinfo)
{
	/*
	 * What we care about here is if we had an
	 * outstanding SDTR or WDTR message for this
	 * target.  If we did, this is a signal that
	 * the target is refusing negotiation.
	 */
	struct scb *scb;
	struct ahc_initiator_tinfo *tinfo;
	struct ahc_tmode_tstate *tstate;
	u_int scb_index;
	u_int last_msg;
	int   response = 0;

	scb_index = ahc_inb(ahc, SCB_TAG);
	scb = ahc_lookup_scb(ahc, scb_index);
	tinfo = ahc_fetch_transinfo(ahc, devinfo->channel,
				    devinfo->our_scsiid,
				    devinfo->target, &tstate);
	/* Might be necessary */
	last_msg = ahc_inb(ahc, LAST_MSG);

	if (ahc_sent_msg(ahc, AHCMSG_EXT, MSG_EXT_PPR, /*full*/FALSE)) {
		/*
		 * Target does not support the PPR message.
		 * Attempt to negotiate SPI-2 style.
		 */
		if (bootverbose) {
			printf("(%s:%c:%d:%d): PPR Rejected. "
			       "Trying WDTR/SDTR\n",
			       ahc_name(ahc), devinfo->channel,
			       devinfo->target, devinfo->lun);
		}
		tinfo->goal.ppr_options = 0;
		tinfo->curr.transport_version = 2;
		tinfo->goal.transport_version = 2;
		ahc->msgout_index = 0;
		ahc->msgout_len = 0;
		ahc_build_transfer_msg(ahc, devinfo);
		ahc->msgout_index = 0;
		response = 1;
	} else if (ahc_sent_msg(ahc, AHCMSG_EXT, MSG_EXT_WDTR, /*full*/FALSE)) {

		/* note 8bit xfers */
		printf("(%s:%c:%d:%d): refuses WIDE negotiation.  Using "
		       "8bit transfers\n", ahc_name(ahc),
		       devinfo->channel, devinfo->target, devinfo->lun);
		ahc_set_width(ahc, devinfo, MSG_EXT_WDTR_BUS_8_BIT,
			      AHC_TRANS_ACTIVE|AHC_TRANS_GOAL,
			      /*paused*/TRUE);
		/*
		 * No need to clear the sync rate.  If the target
		 * did not accept the command, our syncrate is
		 * unaffected.  If the target started the negotiation,
		 * but rejected our response, we already cleared the
		 * sync rate before sending our WDTR.
		 */
		if (tinfo->goal.offset != tinfo->curr.offset) {

			/* Start the sync negotiation */
			ahc->msgout_index = 0;
			ahc->msgout_len = 0;
			ahc_build_transfer_msg(ahc, devinfo);
			ahc->msgout_index = 0;
			response = 1;
		}
	} else if (ahc_sent_msg(ahc, AHCMSG_EXT, MSG_EXT_SDTR, /*full*/FALSE)) {
		/* note asynch xfers and clear flag */
		ahc_set_syncrate(ahc, devinfo, /*syncrate*/NULL, /*period*/0,
				 /*offset*/0, /*ppr_options*/0,
				 AHC_TRANS_ACTIVE|AHC_TRANS_GOAL,
				 /*paused*/TRUE);
		printf("(%s:%c:%d:%d): refuses synchronous negotiation. "
		       "Using asynchronous transfers\n",
		       ahc_name(ahc), devinfo->channel,
		       devinfo->target, devinfo->lun);
	} else if ((scb->hscb->control & MSG_SIMPLE_TASK) != 0) {
		int tag_type;
		int mask;

		tag_type = (scb->hscb->control & MSG_SIMPLE_TASK);

		if (tag_type == MSG_SIMPLE_TASK) {
			printf("(%s:%c:%d:%d): refuses tagged commands.  "
			       "Performing non-tagged I/O\n", ahc_name(ahc),
			       devinfo->channel, devinfo->target, devinfo->lun);
			ahc_set_tags(ahc, scb->io_ctx, devinfo, AHC_QUEUE_NONE);
			mask = ~0x23;
		} else {
			printf("(%s:%c:%d:%d): refuses %s tagged commands.  "
			       "Performing simple queue tagged I/O only\n",
			       ahc_name(ahc), devinfo->channel, devinfo->target,
			       devinfo->lun, tag_type == MSG_ORDERED_TASK
			       ? "ordered" : "head of queue");
			ahc_set_tags(ahc, scb->io_ctx, devinfo, AHC_QUEUE_BASIC);
			mask = ~0x03;
		}

		/*
		 * Resend the identify for this CCB as the target
		 * may believe that the selection is invalid otherwise.
		 */
		ahc_outb(ahc, SCB_CONTROL,
			 ahc_inb(ahc, SCB_CONTROL) & mask);
	 	scb->hscb->control &= mask;
		ahc_set_transaction_tag(scb, /*enabled*/FALSE,
					/*type*/MSG_SIMPLE_TASK);
		ahc_outb(ahc, MSG_OUT, MSG_IDENTIFYFLAG);
		ahc_assert_atn(ahc);

		/*
		 * This transaction is now at the head of
		 * the untagged queue for this target.
		 */
		if ((ahc->flags & AHC_SCB_BTT) == 0) {
			struct scb_tailq *untagged_q;

			untagged_q =
			    &(ahc->untagged_queues[devinfo->target_offset]);
			TAILQ_INSERT_HEAD(untagged_q, scb, links.tqe);
			scb->flags |= SCB_UNTAGGEDQ;
		}
		ahc_busy_tcl(ahc, BUILD_TCL(scb->hscb->scsiid, devinfo->lun),
			     scb->hscb->tag);

		/*
		 * Requeue all tagged commands for this target
		 * currently in our posession so they can be
		 * converted to untagged commands.
		 */
		ahc_search_qinfifo(ahc, SCB_GET_TARGET(ahc, scb),
				   SCB_GET_CHANNEL(ahc, scb),
				   SCB_GET_LUN(scb), /*tag*/SCB_LIST_NULL,
				   ROLE_INITIATOR, CAM_REQUEUE_REQ,
				   SEARCH_COMPLETE);
	} else {
		/*
		 * Otherwise, we ignore it.
		 */
		printf("%s:%c:%d: Message reject for %x -- ignored\n",
		       ahc_name(ahc), devinfo->channel, devinfo->target,
		       last_msg);
	}
	return (response);
}