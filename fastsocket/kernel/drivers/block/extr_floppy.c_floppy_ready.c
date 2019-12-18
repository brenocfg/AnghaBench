#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; int /*<<< orphan*/  select_delay; } ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  length; int /*<<< orphan*/  kernel_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_RESET ; 
 TYPE_2__* DP ; 
 int /*<<< orphan*/  DPRINT (char*) ; 
 int FD_DEBUG ; 
 int FD_RAW_NEED_DISK ; 
 int FD_RAW_NEED_SEEK ; 
 int FD_RAW_NO_MOTOR ; 
 int FD_RAW_READ ; 
 int FD_RAW_WRITE ; 
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  current_drive ; 
 scalar_t__ disk_change (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fd_chose_dma_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fdc_dtr () ; 
 int /*<<< orphan*/  fdc_specify () ; 
 int /*<<< orphan*/  perpendicular_mode () ; 
 TYPE_1__* raw_cmd ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  seek_floppy () ; 
 int /*<<< orphan*/  setup_rw_floppy () ; 
 scalar_t__ start_motor (void (*) ()) ; 
 int /*<<< orphan*/  twaddle () ; 

__attribute__((used)) static void floppy_ready(void)
{
	CHECK_RESET;
	if (start_motor(floppy_ready))
		return;
	if (fdc_dtr())
		return;

#ifdef DCL_DEBUG
	if (DP->flags & FD_DEBUG) {
		DPRINT("calling disk change from floppy_ready\n");
	}
#endif
	if (!(raw_cmd->flags & FD_RAW_NO_MOTOR) &&
	    disk_change(current_drive) && !DP->select_delay)
		twaddle();	/* this clears the dcl on certain drive/controller
				 * combinations */

#ifdef fd_chose_dma_mode
	if ((raw_cmd->flags & FD_RAW_READ) || (raw_cmd->flags & FD_RAW_WRITE)) {
		unsigned long flags = claim_dma_lock();
		fd_chose_dma_mode(raw_cmd->kernel_data, raw_cmd->length);
		release_dma_lock(flags);
	}
#endif

	if (raw_cmd->flags & (FD_RAW_NEED_SEEK | FD_RAW_NEED_DISK)) {
		perpendicular_mode();
		fdc_specify();	/* must be done here because of hut, hlt ... */
		seek_floppy();
	} else {
		if ((raw_cmd->flags & FD_RAW_READ) ||
		    (raw_cmd->flags & FD_RAW_WRITE))
			fdc_specify();
		setup_rw_floppy();
	}
}