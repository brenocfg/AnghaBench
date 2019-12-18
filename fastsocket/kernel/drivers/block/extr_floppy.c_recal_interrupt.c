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
struct TYPE_8__ {int flags; } ;
struct TYPE_7__ {int track; int /*<<< orphan*/  select_date; } ;
struct TYPE_6__ {int reset; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* redo ) () ;int /*<<< orphan*/  (* error ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CLEARF (int /*<<< orphan*/ ) ; 
 TYPE_4__* DP ; 
 int /*<<< orphan*/  DPRINT (char*) ; 
 TYPE_3__* DRS ; 
 TYPE_2__* FDCS ; 
 int FD_DEBUG ; 
 int /*<<< orphan*/  FD_DISK_NEWCHANGE ; 
#define  NEED_1_RECAL 129 
#define  NEED_2_RECAL 128 
 int ST0 ; 
 int ST0_ECE ; 
 int ST1 ; 
 TYPE_1__* cont ; 
 int /*<<< orphan*/  debugt (char*) ; 
 int /*<<< orphan*/  floppy_ready () ; 
 int inr ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

__attribute__((used)) static void recal_interrupt(void)
{
	debugt("recal interrupt:");
	if (inr != 2)
		FDCS->reset = 1;
	else if (ST0 & ST0_ECE) {
		switch (DRS->track) {
		case NEED_1_RECAL:
			debugt("recal interrupt need 1 recal:");
			/* after a second recalibrate, we still haven't
			 * reached track 0. Probably no drive. Raise an
			 * error, as failing immediately might upset
			 * computers possessed by the Devil :-) */
			cont->error();
			cont->redo();
			return;
		case NEED_2_RECAL:
			debugt("recal interrupt need 2 recal:");
			/* If we already did a recalibrate,
			 * and we are not at track 0, this
			 * means we have moved. (The only way
			 * not to move at recalibration is to
			 * be already at track 0.) Clear the
			 * new change flag */
#ifdef DCL_DEBUG
			if (DP->flags & FD_DEBUG) {
				DPRINT
				    ("clearing NEWCHANGE flag because of second recalibrate\n");
			}
#endif

			CLEARF(FD_DISK_NEWCHANGE);
			DRS->select_date = jiffies;
			/* fall through */
		default:
			debugt("recal interrupt default:");
			/* Recalibrate moves the head by at
			 * most 80 steps. If after one
			 * recalibrate we don't have reached
			 * track 0, this might mean that we
			 * started beyond track 80.  Try
			 * again.  */
			DRS->track = NEED_1_RECAL;
			break;
		}
	} else
		DRS->track = ST1;
	floppy_ready();
}