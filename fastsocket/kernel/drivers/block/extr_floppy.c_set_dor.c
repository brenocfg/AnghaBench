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
struct TYPE_6__ {int address; unsigned char dor; } ;
struct TYPE_5__ {int flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  select_date; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 TYPE_3__* FDCS ; 
 int FD_DEBUG ; 
 int /*<<< orphan*/  FD_DOR ; 
 unsigned char REVDRIVE (int,unsigned char) ; 
 TYPE_2__* UDP ; 
 TYPE_1__* UDRS ; 
 int /*<<< orphan*/  disk_change (unsigned char) ; 
 int /*<<< orphan*/  fd_outb (unsigned char,int /*<<< orphan*/ ) ; 
 scalar_t__ is_selected (unsigned char,unsigned char) ; 
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static int set_dor(int fdc, char mask, char data)
{
	unsigned char unit;
	unsigned char drive;
	unsigned char newdor;
	unsigned char olddor;

	if (FDCS->address == -1)
		return -1;

	olddor = FDCS->dor;
	newdor = (olddor & mask) | data;
	if (newdor != olddor) {
		unit = olddor & 0x3;
		if (is_selected(olddor, unit) && !is_selected(newdor, unit)) {
			drive = REVDRIVE(fdc, unit);
#ifdef DCL_DEBUG
			if (UDP->flags & FD_DEBUG) {
				DPRINT("calling disk change from set_dor\n");
			}
#endif
			disk_change(drive);
		}
		FDCS->dor = newdor;
		fd_outb(newdor, FD_DOR);

		unit = newdor & 0x3;
		if (!is_selected(olddor, unit) && is_selected(newdor, unit)) {
			drive = REVDRIVE(fdc, unit);
			UDRS->select_date = jiffies;
		}
	}
	return olddor;
}