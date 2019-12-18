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
struct file {int f_flags; scalar_t__ private_data; } ;
struct dmabuf {size_t cnt_factor; int count; scalar_t__ nextOut; scalar_t__ rawbuf; scalar_t__ dmasize; int /*<<< orphan*/  wait; scalar_t__ stopped; scalar_t__ mapped; } ;
struct au1550_state {int /*<<< orphan*/  sem; int /*<<< orphan*/  lock; struct dmabuf dma_adc; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int EFAULT ; 
 int ENXIO ; 
 int ERESTARTSYS ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  VERIFY_WRITE ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  access_ok (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int copy_dmabuf_user (struct dmabuf*,char*,int,int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  start_adc (struct au1550_state*) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static ssize_t
au1550_read(struct file *file, char *buffer, size_t count, loff_t *ppos)
{
	struct au1550_state *s = (struct au1550_state *)file->private_data;
	struct dmabuf  *db = &s->dma_adc;
	DECLARE_WAITQUEUE(wait, current);
	ssize_t         ret;
	unsigned long   flags;
	int             cnt, usercnt, avail;

	if (db->mapped)
		return -ENXIO;
	if (!access_ok(VERIFY_WRITE, buffer, count))
		return -EFAULT;
	ret = 0;

	count *= db->cnt_factor;

	mutex_lock(&s->sem);
	add_wait_queue(&db->wait, &wait);

	while (count > 0) {
		/* wait for samples in ADC dma buffer
		*/
		do {
			spin_lock_irqsave(&s->lock, flags);
			if (db->stopped)
				start_adc(s);
			avail = db->count;
			if (avail <= 0)
				__set_current_state(TASK_INTERRUPTIBLE);
			spin_unlock_irqrestore(&s->lock, flags);
			if (avail <= 0) {
				if (file->f_flags & O_NONBLOCK) {
					if (!ret)
						ret = -EAGAIN;
					goto out;
				}
				mutex_unlock(&s->sem);
				schedule();
				if (signal_pending(current)) {
					if (!ret)
						ret = -ERESTARTSYS;
					goto out2;
				}
				mutex_lock(&s->sem);
			}
		} while (avail <= 0);

		/* copy from nextOut to user
		*/
		if ((cnt = copy_dmabuf_user(db, buffer,
					    count > avail ?
					    avail : count, 1)) < 0) {
			if (!ret)
				ret = -EFAULT;
			goto out;
		}

		spin_lock_irqsave(&s->lock, flags);
		db->count -= cnt;
		db->nextOut += cnt;
		if (db->nextOut >= db->rawbuf + db->dmasize)
			db->nextOut -= db->dmasize;
		spin_unlock_irqrestore(&s->lock, flags);

		count -= cnt;
		usercnt = cnt / db->cnt_factor;
		buffer += usercnt;
		ret += usercnt;
	}			/* while (count > 0) */

out:
	mutex_unlock(&s->sem);
out2:
	remove_wait_queue(&db->wait, &wait);
	set_current_state(TASK_RUNNING);
	return ret;
}