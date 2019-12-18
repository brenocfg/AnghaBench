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
typedef  size_t u_int ;
struct ahd_tmode_tstate {TYPE_1__* transinfo; struct ahd_tmode_tstate* enabled_luns; } ;
struct ahd_softc {size_t our_id; struct ahd_tmode_tstate** enabled_targets; } ;
struct TYPE_2__ {struct ahd_tmode_tstate goal; struct ahd_tmode_tstate curr; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  ahd_name (struct ahd_softc*) ; 
 struct ahd_tmode_tstate* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ahd_tmode_tstate*,struct ahd_tmode_tstate*,int) ; 
 int /*<<< orphan*/  memset (struct ahd_tmode_tstate*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ahd_tmode_tstate *
ahd_alloc_tstate(struct ahd_softc *ahd, u_int scsi_id, char channel)
{
	struct ahd_tmode_tstate *master_tstate;
	struct ahd_tmode_tstate *tstate;
	int i;

	master_tstate = ahd->enabled_targets[ahd->our_id];
	if (ahd->enabled_targets[scsi_id] != NULL
	 && ahd->enabled_targets[scsi_id] != master_tstate)
		panic("%s: ahd_alloc_tstate - Target already allocated",
		      ahd_name(ahd));
	tstate = malloc(sizeof(*tstate), M_DEVBUF, M_NOWAIT);
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
		for (i = 0; i < 16; i++) {
			memset(&tstate->transinfo[i].curr, 0,
			      sizeof(tstate->transinfo[i].curr));
			memset(&tstate->transinfo[i].goal, 0,
			      sizeof(tstate->transinfo[i].goal));
		}
	} else
		memset(tstate, 0, sizeof(*tstate));
	ahd->enabled_targets[scsi_id] = tstate;
	return (tstate);
}