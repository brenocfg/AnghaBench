#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct request {int /*<<< orphan*/  errors; TYPE_1__* rq_disk; } ;
struct TYPE_12__ {int* autodetect; } ;
struct TYPE_11__ {size_t probed_format; } ;
struct TYPE_10__ {int /*<<< orphan*/  queue_lock; } ;
struct TYPE_9__ {scalar_t__ flags; } ;
struct TYPE_8__ {scalar_t__ private_data; } ;

/* Variables and functions */
 TYPE_7__* DP ; 
 int /*<<< orphan*/  DPRINT (char*) ; 
 TYPE_6__* DRS ; 
 int /*<<< orphan*/  FD_DISK_CHANGED ; 
 int /*<<< orphan*/  FD_NEED_TWADDLE ; 
 scalar_t__ N_DRIVE ; 
 int /*<<< orphan*/  REPEAT ; 
 scalar_t__ TESTF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * _floppy ; 
 struct request* blk_fetch_request (TYPE_3__*) ; 
 scalar_t__ current_drive ; 
 struct request* current_req ; 
 int /*<<< orphan*/  current_reqD ; 
 int /*<<< orphan*/  debugt (char*) ; 
 TYPE_2__ default_raw_cmd ; 
 int /*<<< orphan*/  disk_change (scalar_t__) ; 
 int /*<<< orphan*/ * do_floppy ; 
 int /*<<< orphan*/ * errors ; 
 int /*<<< orphan*/  fake_change ; 
 int /*<<< orphan*/  floppy_off (scalar_t__) ; 
 TYPE_3__* floppy_queue ; 
 int /*<<< orphan*/  floppy_start ; 
 int /*<<< orphan*/ * floppy_type ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  lastredo ; 
 int make_raw_rw_request () ; 
 scalar_t__ next_valid_format () ; 
 int probing ; 
 TYPE_2__* raw_cmd ; 
 int /*<<< orphan*/  request_done (int) ; 
 int /*<<< orphan*/  reschedule_timeout (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_fdc (int) ; 
 int /*<<< orphan*/  set_floppy (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ start_motor (void (*) ()) ; 
 scalar_t__ test_bit (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  twaddle () ; 
 int /*<<< orphan*/  unlock_fdc () ; 

__attribute__((used)) static void redo_fd_request(void)
{
#define REPEAT {request_done(0); continue; }
	int drive;
	int tmp;

	lastredo = jiffies;
	if (current_drive < N_DRIVE)
		floppy_off(current_drive);

	for (;;) {
		if (!current_req) {
			struct request *req;

			spin_lock_irq(floppy_queue->queue_lock);
			req = blk_fetch_request(floppy_queue);
			spin_unlock_irq(floppy_queue->queue_lock);
			if (!req) {
				do_floppy = NULL;
				unlock_fdc();
				return;
			}
			current_req = req;
		}
		drive = (long)current_req->rq_disk->private_data;
		set_fdc(drive);
		reschedule_timeout(current_reqD, "redo fd request", 0);

		set_floppy(drive);
		raw_cmd = &default_raw_cmd;
		raw_cmd->flags = 0;
		if (start_motor(redo_fd_request))
			return;
		disk_change(current_drive);
		if (test_bit(current_drive, &fake_change) ||
		    TESTF(FD_DISK_CHANGED)) {
			DPRINT("disk absent or changed during operation\n");
			REPEAT;
		}
		if (!_floppy) {	/* Autodetection */
			if (!probing) {
				DRS->probed_format = 0;
				if (next_valid_format()) {
					DPRINT("no autodetectable formats\n");
					_floppy = NULL;
					REPEAT;
				}
			}
			probing = 1;
			_floppy =
			    floppy_type + DP->autodetect[DRS->probed_format];
		} else
			probing = 0;
		errors = &(current_req->errors);
		tmp = make_raw_rw_request();
		if (tmp < 2) {
			request_done(tmp);
			continue;
		}

		if (TESTF(FD_NEED_TWADDLE))
			twaddle();
		schedule_bh(floppy_start);
		debugt("queue fd request");
		return;
	}
#undef REPEAT
}