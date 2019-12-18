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
struct raw3215_info {unsigned int count; int flags; int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 unsigned int RAW3215_BUFFER_SIZE ; 
 int RAW3215_FLUSHING ; 
 int RAW3215_FROZEN ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw3215_drop_line (struct raw3215_info*) ; 
 int /*<<< orphan*/  raw3215_mk_write_req (struct raw3215_info*) ; 
 int /*<<< orphan*/  raw3215_try_io (struct raw3215_info*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wait_cons_dev () ; 

__attribute__((used)) static void raw3215_make_room(struct raw3215_info *raw, unsigned int length)
{
	while (RAW3215_BUFFER_SIZE - raw->count < length) {
		/* While console is frozen for suspend we have no other
		 * choice but to drop message from the buffer to make
		 * room for even more messages. */
		if (raw->flags & RAW3215_FROZEN) {
			raw3215_drop_line(raw);
			continue;
		}
		/* there might be a request pending */
		raw->flags |= RAW3215_FLUSHING;
		raw3215_mk_write_req(raw);
		raw3215_try_io(raw);
		raw->flags &= ~RAW3215_FLUSHING;
#ifdef CONFIG_TN3215_CONSOLE
		wait_cons_dev();
#endif
		/* Enough room freed up ? */
		if (RAW3215_BUFFER_SIZE - raw->count >= length)
			break;
		/* there might be another cpu waiting for the lock */
		spin_unlock(get_ccwdev_lock(raw->cdev));
		udelay(100);
		spin_lock(get_ccwdev_lock(raw->cdev));
	}
}