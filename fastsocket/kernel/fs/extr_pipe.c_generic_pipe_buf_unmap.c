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
struct pipe_inode_info {int dummy; } ;
struct pipe_buffer {int flags; int /*<<< orphan*/  page; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_USER0 ; 
 int PIPE_BUF_FLAG_ATOMIC ; 
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*,int /*<<< orphan*/ ) ; 

void generic_pipe_buf_unmap(struct pipe_inode_info *pipe,
			    struct pipe_buffer *buf, void *map_data)
{
	if (buf->flags & PIPE_BUF_FLAG_ATOMIC) {
		buf->flags &= ~PIPE_BUF_FLAG_ATOMIC;
		kunmap_atomic(map_data, KM_USER0);
	} else
		kunmap(buf->page);
}