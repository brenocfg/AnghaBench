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

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  FD_COMMAND_NONE ; 
 scalar_t__ blk_peek_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  command_status ; 
 int /*<<< orphan*/ * cont ; 
 scalar_t__ current_req ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_fd_request (int /*<<< orphan*/ ) ; 
 scalar_t__ do_floppy ; 
 int /*<<< orphan*/  fd_timeout ; 
 int /*<<< orphan*/  fdc_busy ; 
 int /*<<< orphan*/  fdc_wait ; 
 int /*<<< orphan*/  floppy_lock ; 
 int /*<<< orphan*/  floppy_queue ; 
 int /*<<< orphan*/ * raw_cmd ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void unlock_fdc(void)
{
	unsigned long flags;

	raw_cmd = NULL;
	if (!test_bit(0, &fdc_busy))
		DPRINT("FDC access conflict!\n");

	if (do_floppy)
		DPRINT("device interrupt still active at FDC release: %p!\n",
		       do_floppy);
	command_status = FD_COMMAND_NONE;
	spin_lock_irqsave(&floppy_lock, flags);
	del_timer(&fd_timeout);
	cont = NULL;
	clear_bit(0, &fdc_busy);
	if (current_req || blk_peek_request(floppy_queue))
		do_fd_request(floppy_queue);
	spin_unlock_irqrestore(&floppy_lock, flags);
	wake_up(&fdc_wait);
}