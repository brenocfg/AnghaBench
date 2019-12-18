#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct file {int f_flags; TYPE_1__* f_dentry; } ;
struct comedi_subdevice {struct file* busy; struct comedi_async* async; } ;
struct comedi_device_file_info {struct comedi_device* device; } ;
struct comedi_device {int /*<<< orphan*/  minor; int /*<<< orphan*/  attached; } ;
struct comedi_async {scalar_t__ buf_write_ptr; scalar_t__ prealloc_bufsz; int prealloc_buf; int /*<<< orphan*/  wait_head; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTK (char*,int /*<<< orphan*/ ) ; 
 int EACCES ; 
 int EAGAIN ; 
 int EFAULT ; 
 int EIO ; 
 int ENODEV ; 
 int EPIPE ; 
 int ERESTARTSYS ; 
 int O_NONBLOCK ; 
 int SRF_ERROR ; 
 int SRF_RUNNING ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  comedi_buf_write_alloc (struct comedi_async*,int) ; 
 int /*<<< orphan*/  comedi_buf_write_free (struct comedi_async*,int) ; 
 int comedi_buf_write_n_allocated (struct comedi_async*) ; 
 struct comedi_device_file_info* comedi_get_device_file_info (unsigned int const) ; 
 int comedi_get_subdevice_runflags (struct comedi_subdevice*) ; 
 struct comedi_subdevice* comedi_get_write_subdevice (struct comedi_device_file_info*) ; 
 int copy_from_user (int,char const*,int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  do_become_nonbusy (struct comedi_device*,struct comedi_subdevice*) ; 
 unsigned int iminor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static ssize_t comedi_write(struct file *file, const char *buf, size_t nbytes,
			    loff_t * offset)
{
	struct comedi_subdevice *s;
	struct comedi_async *async;
	int n, m, count = 0, retval = 0;
	DECLARE_WAITQUEUE(wait, current);
	const unsigned minor = iminor(file->f_dentry->d_inode);
	struct comedi_device_file_info *dev_file_info =
	    comedi_get_device_file_info(minor);
	struct comedi_device *dev = dev_file_info->device;

	if (!dev->attached) {
		DPRINTK("no driver configured on comedi%i\n", dev->minor);
		retval = -ENODEV;
		goto done;
	}

	s = comedi_get_write_subdevice(dev_file_info);
	if (s == NULL) {
		retval = -EIO;
		goto done;
	}
	async = s->async;

	if (!nbytes) {
		retval = 0;
		goto done;
	}
	if (!s->busy) {
		retval = 0;
		goto done;
	}
	if (s->busy != file) {
		retval = -EACCES;
		goto done;
	}
	add_wait_queue(&async->wait_head, &wait);
	while (nbytes > 0 && !retval) {
		set_current_state(TASK_INTERRUPTIBLE);

		n = nbytes;

		m = n;
		if (async->buf_write_ptr + m > async->prealloc_bufsz)
			m = async->prealloc_bufsz - async->buf_write_ptr;
		comedi_buf_write_alloc(async, async->prealloc_bufsz);
		if (m > comedi_buf_write_n_allocated(async))
			m = comedi_buf_write_n_allocated(async);
		if (m < n)
			n = m;

		if (n == 0) {
			if (!(comedi_get_subdevice_runflags(s) & SRF_RUNNING)) {
				if (comedi_get_subdevice_runflags(s) &
				    SRF_ERROR) {
					retval = -EPIPE;
				} else {
					retval = 0;
				}
				do_become_nonbusy(dev, s);
				break;
			}
			if (file->f_flags & O_NONBLOCK) {
				retval = -EAGAIN;
				break;
			}
			if (signal_pending(current)) {
				retval = -ERESTARTSYS;
				break;
			}
			schedule();
			if (!s->busy)
				break;
			if (s->busy != file) {
				retval = -EACCES;
				break;
			}
			continue;
		}

		m = copy_from_user(async->prealloc_buf + async->buf_write_ptr,
				   buf, n);
		if (m) {
			n -= m;
			retval = -EFAULT;
		}
		comedi_buf_write_free(async, n);

		count += n;
		nbytes -= n;

		buf += n;
		break;		/* makes device work like a pipe */
	}
	set_current_state(TASK_RUNNING);
	remove_wait_queue(&async->wait_head, &wait);

done:
	return count ? count : retval;
}