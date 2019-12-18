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
typedef  int uint64_t ;
typedef  int u_int ;
struct scb {scalar_t__ sg_count; TYPE_1__* hscb; } ;
struct ahd_softc {int* qinfifo; int /*<<< orphan*/  qinfifonext; } ;
struct TYPE_2__ {int scsiid; int /*<<< orphan*/  hscb_busaddr; int /*<<< orphan*/  datacnt; int /*<<< orphan*/  dataptr; } ;

/* Variables and functions */
 size_t AHD_QIN_WRAP (int /*<<< orphan*/ ) ; 
 int AHD_SHOW_QUEUE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 scalar_t__ SCBID_IS_NULL (int) ; 
 int SCB_GET_TAG (struct scb*) ; 
 int ahd_debug ; 
 int ahd_le32toh (int /*<<< orphan*/ ) ; 
 int ahd_le64toh (int /*<<< orphan*/ ) ; 
 char* ahd_name (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_set_hnscb_qoff (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_setup_data_scb (struct ahd_softc*,struct scb*) ; 
 int /*<<< orphan*/  ahd_setup_noxfer_scb (struct ahd_softc*,struct scb*) ; 
 int /*<<< orphan*/  ahd_setup_scb_common (struct ahd_softc*,struct scb*) ; 
 int /*<<< orphan*/  ahd_swap_with_next_hscb (struct ahd_softc*,struct scb*) ; 
 int /*<<< orphan*/  ahd_sync_scb (struct ahd_softc*,struct scb*,int) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int,int,int,int) ; 

void
ahd_queue_scb(struct ahd_softc *ahd, struct scb *scb)
{
	ahd_swap_with_next_hscb(ahd, scb);

	if (SCBID_IS_NULL(SCB_GET_TAG(scb)))
		panic("Attempt to queue invalid SCB tag %x\n",
		      SCB_GET_TAG(scb));

	/*
	 * Keep a history of SCBs we've downloaded in the qinfifo.
	 */
	ahd->qinfifo[AHD_QIN_WRAP(ahd->qinfifonext)] = SCB_GET_TAG(scb);
	ahd->qinfifonext++;

	if (scb->sg_count != 0)
		ahd_setup_data_scb(ahd, scb);
	else
		ahd_setup_noxfer_scb(ahd, scb);
	ahd_setup_scb_common(ahd, scb);

	/*
	 * Make sure our data is consistent from the
	 * perspective of the adapter.
	 */
	ahd_sync_scb(ahd, scb, BUS_DMASYNC_PREREAD|BUS_DMASYNC_PREWRITE);

#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_QUEUE) != 0) {
		uint64_t host_dataptr;

		host_dataptr = ahd_le64toh(scb->hscb->dataptr);
		printf("%s: Queueing SCB %d:0x%x bus addr 0x%x - 0x%x%x/0x%x\n",
		       ahd_name(ahd),
		       SCB_GET_TAG(scb), scb->hscb->scsiid,
		       ahd_le32toh(scb->hscb->hscb_busaddr),
		       (u_int)((host_dataptr >> 32) & 0xFFFFFFFF),
		       (u_int)(host_dataptr & 0xFFFFFFFF),
		       ahd_le32toh(scb->hscb->datacnt));
	}
#endif
	/* Tell the adapter about the newly queued SCB */
	ahd_set_hnscb_qoff(ahd, ahd->qinfifonext);
}