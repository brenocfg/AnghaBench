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
struct TYPE_6__ {int dor; } ;
struct TYPE_5__ {int flags; scalar_t__ select_delay; } ;
struct TYPE_4__ {scalar_t__ keep_data; int /*<<< orphan*/  last_checked; scalar_t__ maxblock; int /*<<< orphan*/  flags; scalar_t__ select_date; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int FDC (int) ; 
 TYPE_3__* FDCS ; 
 int FD_BROKEN_DCL ; 
 int FD_DEBUG ; 
 int /*<<< orphan*/  FD_DIR ; 
 int /*<<< orphan*/  FD_DISK_CHANGED ; 
 int /*<<< orphan*/  FD_DISK_NEWCHANGE ; 
 int /*<<< orphan*/  FD_VERIFY ; 
 int FTD_MSG ; 
 int MAX_DISK_SIZE ; 
 size_t TOMINOR (int) ; 
 int /*<<< orphan*/  UCLEARF (int /*<<< orphan*/ ) ; 
 TYPE_2__* UDP ; 
 TYPE_1__* UDRS ; 
 int UNIT (int) ; 
 int /*<<< orphan*/  USETF (int /*<<< orphan*/ ) ; 
 int UTESTF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** current_type ; 
 int fd_inb (int /*<<< orphan*/ ) ; 
 int* floppy_sizes ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int disk_change(int drive)
{
	int fdc = FDC(drive);

#ifdef FLOPPY_SANITY_CHECK
	if (time_before(jiffies, UDRS->select_date + UDP->select_delay))
		DPRINT("WARNING disk change called early\n");
	if (!(FDCS->dor & (0x10 << UNIT(drive))) ||
	    (FDCS->dor & 3) != UNIT(drive) || fdc != FDC(drive)) {
		DPRINT("probing disk change on unselected drive\n");
		DPRINT("drive=%d fdc=%d dor=%x\n", drive, FDC(drive),
		       (unsigned int)FDCS->dor);
	}
#endif

#ifdef DCL_DEBUG
	if (UDP->flags & FD_DEBUG) {
		DPRINT("checking disk change line for drive %d\n", drive);
		DPRINT("jiffies=%lu\n", jiffies);
		DPRINT("disk change line=%x\n", fd_inb(FD_DIR) & 0x80);
		DPRINT("flags=%lx\n", UDRS->flags);
	}
#endif
	if (UDP->flags & FD_BROKEN_DCL)
		return UTESTF(FD_DISK_CHANGED);
	if ((fd_inb(FD_DIR) ^ UDP->flags) & 0x80) {
		USETF(FD_VERIFY);	/* verify write protection */
		if (UDRS->maxblock) {
			/* mark it changed */
			USETF(FD_DISK_CHANGED);
		}

		/* invalidate its geometry */
		if (UDRS->keep_data >= 0) {
			if ((UDP->flags & FTD_MSG) &&
			    current_type[drive] != NULL)
				DPRINT("Disk type is undefined after "
				       "disk change\n");
			current_type[drive] = NULL;
			floppy_sizes[TOMINOR(drive)] = MAX_DISK_SIZE << 1;
		}

		return 1;
	} else {
		UDRS->last_checked = jiffies;
		UCLEARF(FD_DISK_NEWCHANGE);
	}
	return 0;
}