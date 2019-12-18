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
typedef  int u_int ;
struct ahc_tmode_tstate {TYPE_1__* transinfo; scalar_t__ ultraenb; struct ahc_tmode_tstate* enabled_luns; } ;
struct ahc_softc {size_t our_id; int our_id_b; struct ahc_tmode_tstate** enabled_targets; } ;
struct TYPE_2__ {struct ahc_tmode_tstate goal; struct ahc_tmode_tstate curr; } ;

/* Variables and functions */
 int AHC_NUM_TARGETS ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  ahc_name (struct ahc_softc*) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ahc_tmode_tstate*,struct ahc_tmode_tstate*,int) ; 
 int /*<<< orphan*/  memset (struct ahc_tmode_tstate*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ahc_tmode_tstate *
ahc_alloc_tstate(struct ahc_softc *ahc, u_int scsi_id, char channel)
{
	struct ahc_tmode_tstate *master_tstate;
	struct ahc_tmode_tstate *tstate;
	int i;

	master_tstate = ahc->enabled_targets[ahc->our_id];
	if (channel == 'B') {
		scsi_id += 8;
		master_tstate = ahc->enabled_targets[ahc->our_id_b + 8];
	}
	if (ahc->enabled_targets[scsi_id] != NULL
	 && ahc->enabled_targets[scsi_id] != master_tstate)
		panic("%s: ahc_alloc_tstate - Target already allocated",
		      ahc_name(ahc));
	tstate = (struct ahc_tmode_tstate*)malloc(sizeof(*tstate),
						   M_DEVBUF, M_NOWAIT);
	if (tstate == NULL)
		return (NULL);

	/*
	 * If we have allocated a master tstate, copy user settings from
	 * the master tstate (taken from SRAM or the EEPROM) for this
	 * channel, but reset our current and goal settings to async/narrow
	 * until an initiator talks to us.
	 */
	if (master_tstate != NULL) {
		memcpy(tstate, master_tstate, sizeof(*tstate));
		memset(tstate->enabled_luns, 0, sizeof(tstate->enabled_luns));
		tstate->ultraenb = 0;
		for (i = 0; i < AHC_NUM_TARGETS; i++) {
			memset(&tstate->transinfo[i].curr, 0,
			      sizeof(tstate->transinfo[i].curr));
			memset(&tstate->transinfo[i].goal, 0,
			      sizeof(tstate->transinfo[i].goal));
		}
	} else
		memset(tstate, 0, sizeof(*tstate));
	ahc->enabled_targets[scsi_id] = tstate;
	return (tstate);
}