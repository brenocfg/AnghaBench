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
struct TYPE_6__ {int flags; } ;
struct TYPE_5__ {scalar_t__ track; int /*<<< orphan*/  select_date; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* redo ) () ;int /*<<< orphan*/  (* error ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CLEARF (int /*<<< orphan*/ ) ; 
 TYPE_3__* DP ; 
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 TYPE_2__* DRS ; 
 int FD_DEBUG ; 
 int /*<<< orphan*/  FD_DISK_NEWCHANGE ; 
 scalar_t__ NEED_2_RECAL ; 
 int ST0 ; 
 scalar_t__ ST1 ; 
 int /*<<< orphan*/  blind_seek ; 
 TYPE_1__* cont ; 
 int /*<<< orphan*/  debugt (char*) ; 
 int /*<<< orphan*/  floppy_ready () ; 
 int inr ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

__attribute__((used)) static void seek_interrupt(void)
{
	debugt("seek interrupt:");
	if (inr != 2 || (ST0 & 0xF8) != 0x20) {
		DPRINT("seek failed\n");
		DRS->track = NEED_2_RECAL;
		cont->error();
		cont->redo();
		return;
	}
	if (DRS->track >= 0 && DRS->track != ST1 && !blind_seek) {
#ifdef DCL_DEBUG
		if (DP->flags & FD_DEBUG) {
			DPRINT
			    ("clearing NEWCHANGE flag because of effective seek\n");
			DPRINT("jiffies=%lu\n", jiffies);
		}
#endif
		CLEARF(FD_DISK_NEWCHANGE);	/* effective seek */
		DRS->select_date = jiffies;
	}
	DRS->track = ST1;
	floppy_ready();
}