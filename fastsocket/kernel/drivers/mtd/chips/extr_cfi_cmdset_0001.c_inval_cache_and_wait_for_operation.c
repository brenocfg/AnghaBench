#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct map_info {struct cfi_private* fldrv_priv; } ;
struct flchip {int state; scalar_t__ write_suspended; scalar_t__ erase_suspended; int /*<<< orphan*/  mutex; int /*<<< orphan*/  wq; } ;
struct cfi_private {int dummy; } ;
typedef  int /*<<< orphan*/  map_word ;

/* Variables and functions */
 int /*<<< orphan*/  CMD (int) ; 
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ETIME ; 
 int FL_ERASING ; 
 void* FL_STATUS ; 
 int FL_WRITING ; 
 int HZ ; 
 int /*<<< orphan*/  INVALIDATE_CACHED_RANGE (struct map_info*,unsigned long,int) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  map_read (struct map_info*,unsigned long) ; 
 scalar_t__ map_word_andequal (struct map_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_write (struct map_info*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  msleep (unsigned int) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int inval_cache_and_wait_for_operation(
		struct map_info *map, struct flchip *chip,
		unsigned long cmd_adr, unsigned long inval_adr, int inval_len,
		unsigned int chip_op_time, unsigned int chip_op_time_max)
{
	struct cfi_private *cfi = map->fldrv_priv;
	map_word status, status_OK = CMD(0x80);
	int chip_state = chip->state;
	unsigned int timeo, sleep_time, reset_timeo;

	spin_unlock(chip->mutex);
	if (inval_len)
		INVALIDATE_CACHED_RANGE(map, inval_adr, inval_len);
	spin_lock(chip->mutex);

	timeo = chip_op_time_max;
	if (!timeo)
		timeo = 500000;
	reset_timeo = timeo;
	sleep_time = chip_op_time / 2;

	for (;;) {
		status = map_read(map, cmd_adr);
		if (map_word_andequal(map, status, status_OK, status_OK))
			break;

		if (!timeo) {
			map_write(map, CMD(0x70), cmd_adr);
			chip->state = FL_STATUS;
			return -ETIME;
		}

		/* OK Still waiting. Drop the lock, wait a while and retry. */
		spin_unlock(chip->mutex);
		if (sleep_time >= 1000000/HZ) {
			/*
			 * Half of the normal delay still remaining
			 * can be performed with a sleeping delay instead
			 * of busy waiting.
			 */
			msleep(sleep_time/1000);
			timeo -= sleep_time;
			sleep_time = 1000000/HZ;
		} else {
			udelay(1);
			cond_resched();
			timeo--;
		}
		spin_lock(chip->mutex);

		while (chip->state != chip_state) {
			/* Someone's suspended the operation: sleep */
			DECLARE_WAITQUEUE(wait, current);
			set_current_state(TASK_UNINTERRUPTIBLE);
			add_wait_queue(&chip->wq, &wait);
			spin_unlock(chip->mutex);
			schedule();
			remove_wait_queue(&chip->wq, &wait);
			spin_lock(chip->mutex);
		}
		if (chip->erase_suspended && chip_state == FL_ERASING)  {
			/* Erase suspend occured while sleep: reset timeout */
			timeo = reset_timeo;
			chip->erase_suspended = 0;
		}
		if (chip->write_suspended && chip_state == FL_WRITING)  {
			/* Write suspend occured while sleep: reset timeout */
			timeo = reset_timeo;
			chip->write_suspended = 0;
		}
	}

	/* Done and happy. */
 	chip->state = FL_STATUS;
	return 0;
}