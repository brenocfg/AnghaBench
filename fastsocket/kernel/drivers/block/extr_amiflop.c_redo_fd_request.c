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
struct request {char* buffer; TYPE_1__* rq_disk; } ;
struct amiga_floppy_struct {int blocks; char* trackbuf; int dirty; TYPE_3__* type; TYPE_2__* dtype; } ;
struct TYPE_6__ {unsigned int sect_mult; } ;
struct TYPE_5__ {unsigned int sects; } ;
struct TYPE_4__ {struct amiga_floppy_struct* private_data; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ READ ; 
 scalar_t__ __blk_end_request_cur (struct request*,int) ; 
 struct request* blk_fetch_request (int /*<<< orphan*/ ) ; 
 unsigned int blk_rq_cur_sectors (struct request*) ; 
 unsigned int blk_rq_pos (struct request*) ; 
 int /*<<< orphan*/  fd_motor_on (int) ; 
 int /*<<< orphan*/  floppy_queue ; 
 scalar_t__ flush_track_timer ; 
 int get_track (int,unsigned int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  mod_timer (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,unsigned int,unsigned int,char*) ; 
 scalar_t__ rq_data_dir (struct request*) ; 
 struct amiga_floppy_struct* unit ; 

__attribute__((used)) static void redo_fd_request(void)
{
	struct request *rq;
	unsigned int cnt, block, track, sector;
	int drive;
	struct amiga_floppy_struct *floppy;
	char *data;
	unsigned long flags;
	int err;

next_req:
	rq = blk_fetch_request(floppy_queue);
	if (!rq) {
		/* Nothing left to do */
		return;
	}

	floppy = rq->rq_disk->private_data;
	drive = floppy - unit;

next_segment:
	/* Here someone could investigate to be more efficient */
	for (cnt = 0, err = 0; cnt < blk_rq_cur_sectors(rq); cnt++) {
#ifdef DEBUG
		printk("fd: sector %ld + %d requested for %s\n",
		       blk_rq_pos(rq), cnt,
		       (rq_data_dir(rq) == READ) ? "read" : "write");
#endif
		block = blk_rq_pos(rq) + cnt;
		if ((int)block > floppy->blocks) {
			err = -EIO;
			break;
		}

		track = block / (floppy->dtype->sects * floppy->type->sect_mult);
		sector = block % (floppy->dtype->sects * floppy->type->sect_mult);
		data = rq->buffer + 512 * cnt;
#ifdef DEBUG
		printk("access to track %d, sector %d, with buffer at "
		       "0x%08lx\n", track, sector, data);
#endif

		if (get_track(drive, track) == -1) {
			err = -EIO;
			break;
		}

		if (rq_data_dir(rq) == READ) {
			memcpy(data, floppy->trackbuf + sector * 512, 512);
		} else {
			memcpy(floppy->trackbuf + sector * 512, data, 512);

			/* keep the drive spinning while writes are scheduled */
			if (!fd_motor_on(drive)) {
				err = -EIO;
				break;
			}
			/*
			 * setup a callback to write the track buffer
			 * after a short (1 tick) delay.
			 */
			local_irq_save(flags);

			floppy->dirty = 1;
		        /* reset the timer */
			mod_timer (flush_track_timer + drive, jiffies + 1);
			local_irq_restore(flags);
		}
	}

	if (__blk_end_request_cur(rq, err))
		goto next_segment;
	goto next_req;
}