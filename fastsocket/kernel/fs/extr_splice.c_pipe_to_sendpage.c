#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct file* file; } ;
struct splice_desc {int flags; int /*<<< orphan*/  len; int /*<<< orphan*/  total_len; int /*<<< orphan*/  pos; TYPE_1__ u; } ;
struct pipe_inode_info {int dummy; } ;
struct pipe_buffer {int /*<<< orphan*/  offset; int /*<<< orphan*/  page; TYPE_2__* ops; } ;
struct file {TYPE_3__* f_op; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_6__ {int (* sendpage ) (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;} ;
struct TYPE_5__ {int (* confirm ) (struct pipe_inode_info*,struct pipe_buffer*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int SPLICE_F_MORE ; 
 int stub1 (struct pipe_inode_info*,struct pipe_buffer*) ; 
 int stub2 (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int pipe_to_sendpage(struct pipe_inode_info *pipe,
			    struct pipe_buffer *buf, struct splice_desc *sd)
{
	struct file *file = sd->u.file;
	loff_t pos = sd->pos;
	int ret, more;

	ret = buf->ops->confirm(pipe, buf);
	if (!ret) {
		more = (sd->flags & SPLICE_F_MORE) || sd->len < sd->total_len;
		if (file->f_op && file->f_op->sendpage)
			ret = file->f_op->sendpage(file, buf->page, buf->offset,
						   sd->len, &pos, more);
		else
			ret = -EINVAL;
	}

	return ret;
}