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
struct tty_struct {struct acm* driver_data; } ;
struct acm_wb {int len; int /*<<< orphan*/  buf; } ;
struct acm {int writesize; int /*<<< orphan*/  write_lock; struct acm_wb* wb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACM_READY (struct acm*) ; 
 int EINVAL ; 
 int acm_wb_alloc (struct acm*) ; 
 int acm_write_start (struct acm*,int) ; 
 int /*<<< orphan*/  dbg (char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int acm_tty_write(struct tty_struct *tty,
					const unsigned char *buf, int count)
{
	struct acm *acm = tty->driver_data;
	int stat;
	unsigned long flags;
	int wbn;
	struct acm_wb *wb;

	dbg("Entering acm_tty_write to write %d bytes,", count);

	if (!ACM_READY(acm))
		return -EINVAL;
	if (!count)
		return 0;

	spin_lock_irqsave(&acm->write_lock, flags);
	wbn = acm_wb_alloc(acm);
	if (wbn < 0) {
		spin_unlock_irqrestore(&acm->write_lock, flags);
		return 0;
	}
	wb = &acm->wb[wbn];

	count = (count > acm->writesize) ? acm->writesize : count;
	dbg("Get %d bytes...", count);
	memcpy(wb->buf, buf, count);
	wb->len = count;
	spin_unlock_irqrestore(&acm->write_lock, flags);

	stat = acm_write_start(acm, wbn);
	if (stat < 0)
		return stat;
	return count;
}