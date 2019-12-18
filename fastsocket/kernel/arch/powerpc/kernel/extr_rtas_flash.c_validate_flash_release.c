#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rtas_validate_flash_t {scalar_t__ status; int /*<<< orphan*/  buf_size; } ;
struct proc_dir_entry {int /*<<< orphan*/  count; scalar_t__ data; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; } ;
struct TYPE_3__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 struct proc_dir_entry* PDE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALIDATE_BUF_SIZE ; 
 scalar_t__ VALIDATE_READY ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  validate_flash (struct rtas_validate_flash_t*) ; 

__attribute__((used)) static int validate_flash_release(struct inode *inode, struct file *file)
{
	struct proc_dir_entry *dp = PDE(file->f_path.dentry->d_inode);
	struct rtas_validate_flash_t *args_buf;

	args_buf = (struct rtas_validate_flash_t *) dp->data;

	if (args_buf->status == VALIDATE_READY) {
		args_buf->buf_size = VALIDATE_BUF_SIZE;
		validate_flash(args_buf);
	}

	/* The matching atomic_inc was in rtas_excl_open() */
	atomic_dec(&dp->count);

	return 0;
}