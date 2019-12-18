#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int index; TYPE_3__* driver; } ;
struct inode {int dummy; } ;
struct TYPE_12__ {int rows; int cols; } ;
struct idal_buffer {TYPE_4__ view; struct idal_buffer* rdbuf; int /*<<< orphan*/  fs_pid; int /*<<< orphan*/  wait; } ;
struct fs3270 {TYPE_4__ view; struct fs3270* rdbuf; int /*<<< orphan*/  fs_pid; int /*<<< orphan*/  wait; } ;
struct TYPE_10__ {TYPE_1__* dentry; } ;
struct file {struct idal_buffer* private_data; TYPE_2__ f_path; } ;
struct TYPE_11__ {scalar_t__ major; } ;
struct TYPE_9__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 scalar_t__ IBM_FS3270_MAJOR ; 
 scalar_t__ IBM_TTY3270_MAJOR ; 
 scalar_t__ IS_ERR (struct idal_buffer*) ; 
 int PTR_ERR (struct idal_buffer*) ; 
 int RAW3270_FIRSTMINOR ; 
 int /*<<< orphan*/  current ; 
 struct idal_buffer* fs3270_alloc_view () ; 
 int /*<<< orphan*/  fs3270_fn ; 
 int /*<<< orphan*/  fs3270_free_view (TYPE_4__*) ; 
 struct tty_struct* get_current_tty () ; 
 int /*<<< orphan*/  get_pid (int /*<<< orphan*/ ) ; 
 struct idal_buffer* idal_buffer_alloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ imajor (int /*<<< orphan*/ ) ; 
 int iminor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int raw3270_activate_view (TYPE_4__*) ; 
 int raw3270_add_view (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  raw3270_del_view (TYPE_4__*) ; 
 scalar_t__ raw3270_find_view (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  raw3270_put_view (TYPE_4__*) ; 
 int /*<<< orphan*/  task_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int
fs3270_open(struct inode *inode, struct file *filp)
{
	struct fs3270 *fp;
	struct idal_buffer *ib;
	int minor, rc = 0;

	if (imajor(filp->f_path.dentry->d_inode) != IBM_FS3270_MAJOR)
		return -ENODEV;
	minor = iminor(filp->f_path.dentry->d_inode);
	/* Check for minor 0 multiplexer. */
	if (minor == 0) {
		struct tty_struct *tty = get_current_tty();
		if (!tty || tty->driver->major != IBM_TTY3270_MAJOR) {
			tty_kref_put(tty);
			return -ENODEV;
		}
		minor = tty->index + RAW3270_FIRSTMINOR;
		tty_kref_put(tty);
	}
	lock_kernel();
	/* Check if some other program is already using fullscreen mode. */
	fp = (struct fs3270 *) raw3270_find_view(&fs3270_fn, minor);
	if (!IS_ERR(fp)) {
		raw3270_put_view(&fp->view);
		rc = -EBUSY;
		goto out;
	}
	/* Allocate fullscreen view structure. */
	fp = fs3270_alloc_view();
	if (IS_ERR(fp)) {
		rc = PTR_ERR(fp);
		goto out;
	}

	init_waitqueue_head(&fp->wait);
	fp->fs_pid = get_pid(task_pid(current));
	rc = raw3270_add_view(&fp->view, &fs3270_fn, minor);
	if (rc) {
		fs3270_free_view(&fp->view);
		goto out;
	}

	/* Allocate idal-buffer. */
	ib = idal_buffer_alloc(2*fp->view.rows*fp->view.cols + 5, 0);
	if (IS_ERR(ib)) {
		raw3270_put_view(&fp->view);
		raw3270_del_view(&fp->view);
		rc = PTR_ERR(fp);
		goto out;
	}
	fp->rdbuf = ib;

	rc = raw3270_activate_view(&fp->view);
	if (rc) {
		raw3270_put_view(&fp->view);
		raw3270_del_view(&fp->view);
		goto out;
	}
	filp->private_data = fp;
out:
	unlock_kernel();
	return rc;
}