#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u_int ;
struct ahc_softc {int features; int flags; int our_id_b; int seltime_b; int our_id; int seltime; int* qoutfifo; int* qinfifo; int shared_data_busaddr; int tqinfifonext; int qinfifonext; int qoutfifonext; TYPE_2__* next_queued_scb; TYPE_3__* scb_data; } ;
struct TYPE_6__ {int hscb_busaddr; } ;
struct TYPE_5__ {TYPE_1__* hscb; } ;
struct TYPE_4__ {int tag; } ;

/* Variables and functions */
 int ACTNEGEN ; 
 int AHC_HS_MAILBOX ; 
 int AHC_INITIATORROLE ; 
 int AHC_MULTI_TID ; 
 int AHC_NUM_LUNS ; 
 int AHC_QUEUE_REGS ; 
 int AHC_SCB_BTT ; 
 int AHC_TARGETMODE ; 
 int AHC_TERM_ENB_A ; 
 int AHC_TERM_ENB_B ; 
 int AHC_TWIN ; 
 int AHC_ULTRA2 ; 
 int /*<<< orphan*/  BUILD_TCL (int,int) ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 scalar_t__ CMDSIZE_TABLE ; 
 int DFON ; 
 scalar_t__ DISCONNECTED_SCBH ; 
 int ENAB20 ; 
 int ENAB40 ; 
 int ENAUTOATNO ; 
 int ENAUTOATNP ; 
 int ENIOERR ; 
 int ENRSELI ; 
 int ENSCSIPERR ; 
 int ENSCSIRST ; 
 int ENSELO ; 
 int ENSELTIMO ; 
 int ENSPCHK ; 
 int ENSTIMER ; 
 scalar_t__ HNSCB_QOFF ; 
 scalar_t__ HSCB_ADDR ; 
 scalar_t__ HS_MAILBOX ; 
 scalar_t__ KERNEL_QINPOS ; 
 scalar_t__ KERNEL_TQINPOS ; 
 int MSG_NOOP ; 
 scalar_t__ MSG_OUT ; 
 scalar_t__ NEXT_QUEUED_SCB ; 
 scalar_t__ QINPOS ; 
 scalar_t__ QOFF_CTLSTA ; 
 scalar_t__ QOUTPOS ; 
 scalar_t__ SBLKCTL ; 
 int SCB_LIST_NULL ; 
 int SCB_QSIZE_256 ; 
 scalar_t__ SCSICONF ; 
 scalar_t__ SCSIID ; 
 scalar_t__ SCSIID_ULTRA2 ; 
 scalar_t__ SCSISEQ_TEMPLATE ; 
 scalar_t__ SDSCB_QOFF ; 
 int SELBUSB ; 
 scalar_t__ SEQ_FLAGS ; 
 scalar_t__ SEQ_FLAGS2 ; 
 scalar_t__ SHARED_DATA_ADDR ; 
 scalar_t__ SIMODE0 ; 
 scalar_t__ SIMODE1 ; 
 scalar_t__ SNSCB_QOFF ; 
 int SPIOEN ; 
 int STIMESEL ; 
 int STPWEN ; 
 scalar_t__ SXFRCTL0 ; 
 scalar_t__ SXFRCTL1 ; 
 scalar_t__ TARGID ; 
 scalar_t__ TQINPOS ; 
 scalar_t__ WAITING_SCBH ; 
 int /*<<< orphan*/  ahc_build_free_scb_list (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_delay (int) ; 
 int ahc_inb (struct ahc_softc*,scalar_t__) ; 
 int ahc_loadseq (struct ahc_softc*) ; 
 char* ahc_name (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_outb (struct ahc_softc*,scalar_t__,int) ; 
 int /*<<< orphan*/  ahc_restart (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_sync_qoutfifo (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_unbusy_tcl (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

int
ahc_chip_init(struct ahc_softc *ahc)
{
	int	 term;
	int	 error;
	u_int	 i;
	u_int	 scsi_conf;
	u_int	 scsiseq_template;
	uint32_t physaddr;

	ahc_outb(ahc, SEQ_FLAGS, 0);
	ahc_outb(ahc, SEQ_FLAGS2, 0);

	/* Set the SCSI Id, SXFRCTL0, SXFRCTL1, and SIMODE1, for both channels*/
	if (ahc->features & AHC_TWIN) {

		/*
		 * Setup Channel B first.
		 */
		ahc_outb(ahc, SBLKCTL, ahc_inb(ahc, SBLKCTL) | SELBUSB);
		term = (ahc->flags & AHC_TERM_ENB_B) != 0 ? STPWEN : 0;
		ahc_outb(ahc, SCSIID, ahc->our_id_b);
		scsi_conf = ahc_inb(ahc, SCSICONF + 1);
		ahc_outb(ahc, SXFRCTL1, (scsi_conf & (ENSPCHK|STIMESEL))
					|term|ahc->seltime_b|ENSTIMER|ACTNEGEN);
		if ((ahc->features & AHC_ULTRA2) != 0)
			ahc_outb(ahc, SIMODE0, ahc_inb(ahc, SIMODE0)|ENIOERR);
		ahc_outb(ahc, SIMODE1, ENSELTIMO|ENSCSIRST|ENSCSIPERR);
		ahc_outb(ahc, SXFRCTL0, DFON|SPIOEN);

		/* Select Channel A */
		ahc_outb(ahc, SBLKCTL, ahc_inb(ahc, SBLKCTL) & ~SELBUSB);
	}
	term = (ahc->flags & AHC_TERM_ENB_A) != 0 ? STPWEN : 0;
	if ((ahc->features & AHC_ULTRA2) != 0)
		ahc_outb(ahc, SCSIID_ULTRA2, ahc->our_id);
	else
		ahc_outb(ahc, SCSIID, ahc->our_id);
	scsi_conf = ahc_inb(ahc, SCSICONF);
	ahc_outb(ahc, SXFRCTL1, (scsi_conf & (ENSPCHK|STIMESEL))
				|term|ahc->seltime
				|ENSTIMER|ACTNEGEN);
	if ((ahc->features & AHC_ULTRA2) != 0)
		ahc_outb(ahc, SIMODE0, ahc_inb(ahc, SIMODE0)|ENIOERR);
	ahc_outb(ahc, SIMODE1, ENSELTIMO|ENSCSIRST|ENSCSIPERR);
	ahc_outb(ahc, SXFRCTL0, DFON|SPIOEN);

	/* There are no untagged SCBs active yet. */
	for (i = 0; i < 16; i++) {
		ahc_unbusy_tcl(ahc, BUILD_TCL(i << 4, 0));
		if ((ahc->flags & AHC_SCB_BTT) != 0) {
			int lun;

			/*
			 * The SCB based BTT allows an entry per
			 * target and lun pair.
			 */
			for (lun = 1; lun < AHC_NUM_LUNS; lun++)
				ahc_unbusy_tcl(ahc, BUILD_TCL(i << 4, lun));
		}
	}

	/* All of our queues are empty */
	for (i = 0; i < 256; i++)
		ahc->qoutfifo[i] = SCB_LIST_NULL;
	ahc_sync_qoutfifo(ahc, BUS_DMASYNC_PREREAD);

	for (i = 0; i < 256; i++)
		ahc->qinfifo[i] = SCB_LIST_NULL;

	if ((ahc->features & AHC_MULTI_TID) != 0) {
		ahc_outb(ahc, TARGID, 0);
		ahc_outb(ahc, TARGID + 1, 0);
	}

	/*
	 * Tell the sequencer where it can find our arrays in memory.
	 */
	physaddr = ahc->scb_data->hscb_busaddr;
	ahc_outb(ahc, HSCB_ADDR, physaddr & 0xFF);
	ahc_outb(ahc, HSCB_ADDR + 1, (physaddr >> 8) & 0xFF);
	ahc_outb(ahc, HSCB_ADDR + 2, (physaddr >> 16) & 0xFF);
	ahc_outb(ahc, HSCB_ADDR + 3, (physaddr >> 24) & 0xFF);

	physaddr = ahc->shared_data_busaddr;
	ahc_outb(ahc, SHARED_DATA_ADDR, physaddr & 0xFF);
	ahc_outb(ahc, SHARED_DATA_ADDR + 1, (physaddr >> 8) & 0xFF);
	ahc_outb(ahc, SHARED_DATA_ADDR + 2, (physaddr >> 16) & 0xFF);
	ahc_outb(ahc, SHARED_DATA_ADDR + 3, (physaddr >> 24) & 0xFF);

	/*
	 * Initialize the group code to command length table.
	 * This overrides the values in TARG_SCSIRATE, so only
	 * setup the table after we have processed that information.
	 */
	ahc_outb(ahc, CMDSIZE_TABLE, 5);
	ahc_outb(ahc, CMDSIZE_TABLE + 1, 9);
	ahc_outb(ahc, CMDSIZE_TABLE + 2, 9);
	ahc_outb(ahc, CMDSIZE_TABLE + 3, 0);
	ahc_outb(ahc, CMDSIZE_TABLE + 4, 15);
	ahc_outb(ahc, CMDSIZE_TABLE + 5, 11);
	ahc_outb(ahc, CMDSIZE_TABLE + 6, 0);
	ahc_outb(ahc, CMDSIZE_TABLE + 7, 0);
		
	if ((ahc->features & AHC_HS_MAILBOX) != 0)
		ahc_outb(ahc, HS_MAILBOX, 0);

	/* Tell the sequencer of our initial queue positions */
	if ((ahc->features & AHC_TARGETMODE) != 0) {
		ahc->tqinfifonext = 1;
		ahc_outb(ahc, KERNEL_TQINPOS, ahc->tqinfifonext - 1);
		ahc_outb(ahc, TQINPOS, ahc->tqinfifonext);
	}
	ahc->qinfifonext = 0;
	ahc->qoutfifonext = 0;
	if ((ahc->features & AHC_QUEUE_REGS) != 0) {
		ahc_outb(ahc, QOFF_CTLSTA, SCB_QSIZE_256);
		ahc_outb(ahc, HNSCB_QOFF, ahc->qinfifonext);
		ahc_outb(ahc, SNSCB_QOFF, ahc->qinfifonext);
		ahc_outb(ahc, SDSCB_QOFF, 0);
	} else {
		ahc_outb(ahc, KERNEL_QINPOS, ahc->qinfifonext);
		ahc_outb(ahc, QINPOS, ahc->qinfifonext);
		ahc_outb(ahc, QOUTPOS, ahc->qoutfifonext);
	}

	/* We don't have any waiting selections */
	ahc_outb(ahc, WAITING_SCBH, SCB_LIST_NULL);

	/* Our disconnection list is empty too */
	ahc_outb(ahc, DISCONNECTED_SCBH, SCB_LIST_NULL);

	/* Message out buffer starts empty */
	ahc_outb(ahc, MSG_OUT, MSG_NOOP);

	/*
	 * Setup the allowed SCSI Sequences based on operational mode.
	 * If we are a target, we'll enable select in operations once
	 * we've had a lun enabled.
	 */
	scsiseq_template = ENSELO|ENAUTOATNO|ENAUTOATNP;
	if ((ahc->flags & AHC_INITIATORROLE) != 0)
		scsiseq_template |= ENRSELI;
	ahc_outb(ahc, SCSISEQ_TEMPLATE, scsiseq_template);

	/* Initialize our list of free SCBs. */
	ahc_build_free_scb_list(ahc);

	/*
	 * Tell the sequencer which SCB will be the next one it receives.
	 */
	ahc_outb(ahc, NEXT_QUEUED_SCB, ahc->next_queued_scb->hscb->tag);

	/*
	 * Load the Sequencer program and Enable the adapter
	 * in "fast" mode.
	 */
	if (bootverbose)
		printf("%s: Downloading Sequencer Program...",
		       ahc_name(ahc));

	error = ahc_loadseq(ahc);
	if (error != 0)
		return (error);

	if ((ahc->features & AHC_ULTRA2) != 0) {
		int wait;

		/*
		 * Wait for up to 500ms for our transceivers
		 * to settle.  If the adapter does not have
		 * a cable attached, the transceivers may
		 * never settle, so don't complain if we
		 * fail here.
		 */
		for (wait = 5000;
		     (ahc_inb(ahc, SBLKCTL) & (ENAB40|ENAB20)) == 0 && wait;
		     wait--)
			ahc_delay(100);
	}
	ahc_restart(ahc);
	return (0);
}