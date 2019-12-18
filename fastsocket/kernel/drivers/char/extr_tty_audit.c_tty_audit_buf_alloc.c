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
struct tty_audit_buf {int major; int minor; int icanon; scalar_t__ valid; int /*<<< orphan*/  mutex; int /*<<< orphan*/  count; void* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int N_TTY_BUF_SIZE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct tty_audit_buf*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct tty_audit_buf *tty_audit_buf_alloc(int major, int minor,
						 int icanon)
{
	struct tty_audit_buf *buf;

	buf = kmalloc(sizeof(*buf), GFP_KERNEL);
	if (!buf)
		goto err;
	buf->data = kmalloc(N_TTY_BUF_SIZE, GFP_KERNEL);
	if (!buf->data)
		goto err_buf;
	atomic_set(&buf->count, 1);
	mutex_init(&buf->mutex);
	buf->major = major;
	buf->minor = minor;
	buf->icanon = icanon;
	buf->valid = 0;
	return buf;

err_buf:
	kfree(buf);
err:
	return NULL;
}