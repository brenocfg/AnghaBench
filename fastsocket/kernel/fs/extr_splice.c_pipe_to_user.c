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
struct TYPE_4__ {int userptr; } ;
struct splice_desc {int len; TYPE_2__ u; } ;
struct pipe_inode_info {int dummy; } ;
struct pipe_buffer {int offset; TYPE_1__* ops; } ;
struct TYPE_3__ {int (* confirm ) (struct pipe_inode_info*,struct pipe_buffer*) ;char* (* map ) (struct pipe_inode_info*,struct pipe_buffer*,int) ;int /*<<< orphan*/  (* unmap ) (struct pipe_inode_info*,struct pipe_buffer*,char*) ;} ;

/* Variables and functions */
 int EFAULT ; 
 int __copy_to_user_inatomic (int,char*,int) ; 
 scalar_t__ copy_to_user (int,char*,int) ; 
 int /*<<< orphan*/  fault_in_pages_writeable (int,int) ; 
 int stub1 (struct pipe_inode_info*,struct pipe_buffer*) ; 
 char* stub2 (struct pipe_inode_info*,struct pipe_buffer*,int) ; 
 int /*<<< orphan*/  stub3 (struct pipe_inode_info*,struct pipe_buffer*,char*) ; 
 char* stub4 (struct pipe_inode_info*,struct pipe_buffer*,int) ; 
 int /*<<< orphan*/  stub5 (struct pipe_inode_info*,struct pipe_buffer*,char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int pipe_to_user(struct pipe_inode_info *pipe, struct pipe_buffer *buf,
			struct splice_desc *sd)
{
	char *src;
	int ret;

	ret = buf->ops->confirm(pipe, buf);
	if (unlikely(ret))
		return ret;

	/*
	 * See if we can use the atomic maps, by prefaulting in the
	 * pages and doing an atomic copy
	 */
	if (!fault_in_pages_writeable(sd->u.userptr, sd->len)) {
		src = buf->ops->map(pipe, buf, 1);
		ret = __copy_to_user_inatomic(sd->u.userptr, src + buf->offset,
							sd->len);
		buf->ops->unmap(pipe, buf, src);
		if (!ret) {
			ret = sd->len;
			goto out;
		}
	}

	/*
	 * No dice, use slow non-atomic map and copy
 	 */
	src = buf->ops->map(pipe, buf, 0);

	ret = sd->len;
	if (copy_to_user(sd->u.userptr, src + buf->offset, sd->len))
		ret = -EFAULT;

	buf->ops->unmap(pipe, buf, src);
out:
	if (ret > 0)
		sd->u.userptr += ret;
	return ret;
}