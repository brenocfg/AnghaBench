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
struct pipe_buffer {int /*<<< orphan*/  page; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_USER0 ; 
 int /*<<< orphan*/  PIPE_BUF_FLAG_ATOMIC ; 
 void* kmap (int /*<<< orphan*/ ) ; 
 void* kmap_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void *generic_pipe_buf_map(struct pipe_inode_info *pipe,
			   struct pipe_buffer *buf, int atomic)
{
	if (atomic) {
		buf->flags |= PIPE_BUF_FLAG_ATOMIC;
		return kmap_atomic(buf->page, KM_USER0);
	}

	return kmap(buf->page);
}