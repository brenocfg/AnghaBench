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
struct TYPE_3__ {int /*<<< orphan*/  file; } ;
struct splice_desc {int /*<<< orphan*/  pos; int /*<<< orphan*/  len; TYPE_1__ u; } ;
struct pipe_inode_info {int dummy; } ;
struct pipe_buffer {int offset; TYPE_2__* ops; } ;
struct TYPE_4__ {int (* confirm ) (struct pipe_inode_info*,struct pipe_buffer*) ;int /*<<< orphan*/  (* unmap ) (struct pipe_inode_info*,struct pipe_buffer*,void*) ;void* (* map ) (struct pipe_inode_info*,struct pipe_buffer*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int kernel_write (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct pipe_inode_info*,struct pipe_buffer*) ; 
 void* stub2 (struct pipe_inode_info*,struct pipe_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct pipe_inode_info*,struct pipe_buffer*,void*) ; 

__attribute__((used)) static int write_pipe_buf(struct pipe_inode_info *pipe, struct pipe_buffer *buf,
			  struct splice_desc *sd)
{
	int ret;
	void *data;

	ret = buf->ops->confirm(pipe, buf);
	if (ret)
		return ret;

	data = buf->ops->map(pipe, buf, 0);
	ret = kernel_write(sd->u.file, data + buf->offset, sd->len, sd->pos);
	buf->ops->unmap(pipe, buf, data);

	return ret;
}