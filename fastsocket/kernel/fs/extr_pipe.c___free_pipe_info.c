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
struct pipe_inode_info {scalar_t__ tmp_page; struct pipe_buffer* bufs; } ;
struct pipe_buffer {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* release ) (struct pipe_inode_info*,struct pipe_buffer*) ;} ;

/* Variables and functions */
 int PIPE_BUFFERS ; 
 int /*<<< orphan*/  __free_page (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct pipe_inode_info*) ; 
 int /*<<< orphan*/  stub1 (struct pipe_inode_info*,struct pipe_buffer*) ; 

void __free_pipe_info(struct pipe_inode_info *pipe)
{
	int i;

	for (i = 0; i < PIPE_BUFFERS; i++) {
		struct pipe_buffer *buf = pipe->bufs + i;
		if (buf->ops)
			buf->ops->release(pipe, buf);
	}
	if (pipe->tmp_page)
		__free_page(pipe->tmp_page);
	kfree(pipe);
}