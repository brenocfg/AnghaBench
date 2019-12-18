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
struct dmabuf {size_t cnt_factor; scalar_t__ dmasize; int count; scalar_t__ nextIn; scalar_t__ rawbuf; int dma_qcount; int fragsize; scalar_t__ nextOut; int /*<<< orphan*/  wait; scalar_t__ dma_fragsize; int /*<<< orphan*/  total_bytes; int /*<<< orphan*/  dmanr; scalar_t__ mapped; } ;
struct au1550_state {int /*<<< orphan*/  sem; int /*<<< orphan*/  lock; struct dmabuf dma_dac; } ;
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
 int /*<<< orphan*/  VERIFY_READ ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  access_ok (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ au1xxx_dbdma_put_source (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int copy_dmabuf_user (struct dmabuf*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,size_t) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  start_dac (struct au1550_state*) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static ssize_t
au1550_write(struct file *file, const char *buffer, size_t count, loff_t * ppos)
{
	struct au1550_state *s = (struct au1550_state *)file->private_data;
	struct dmabuf  *db = &s->dma_dac;
	DECLARE_WAITQUEUE(wait, current);
	ssize_t         ret = 0;
	unsigned long   flags;
	int             cnt, usercnt, avail;

	pr_debug("write: count=%d\n", count);

	if (db->mapped)
		return -ENXIO;
	if (!access_ok(VERIFY_READ, buffer, count))
		return -EFAULT;

	count *= db->cnt_factor;

	mutex_lock(&s->sem);
	add_wait_queue(&db->wait, &wait);

	while (count > 0) {
		/* wait for space in playback buffer
		*/
		do {
			spin_lock_irqsave(&s->lock, flags);
			avail = (int) db->dmasize - db->count;
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

		/* copy from user to nextIn
		*/
		if ((cnt = copy_dmabuf_user(db, (char *) buffer,
					    count > avail ?
					    avail : count, 0)) < 0) {
			if (!ret)
				ret = -EFAULT;
			goto out;
		}

		spin_lock_irqsave(&s->lock, flags);
		db->count += cnt;
		db->nextIn += cnt;
		if (db->nextIn >= db->rawbuf + db->dmasize)
			db->nextIn -= db->dmasize;

		/* If the data is available, we want to keep two buffers
		 * on the dma queue.  If the queue count reaches zero,
		 * we know the dma has stopped.
		 */
		while ((db->dma_qcount < 2) && (db->count >= db->fragsize)) {
			if (au1xxx_dbdma_put_source(db->dmanr, db->nextOut,
							db->fragsize) == 0) {
				err("qcount < 2 and no ring room!");
			}
			db->nextOut += db->fragsize;
			if (db->nextOut >= db->rawbuf + db->dmasize)
				db->nextOut -= db->dmasize;
			db->total_bytes += db->dma_fragsize;
			if (db->dma_qcount == 0)
				start_dac(s);
			db->dma_qcount++;
		}
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