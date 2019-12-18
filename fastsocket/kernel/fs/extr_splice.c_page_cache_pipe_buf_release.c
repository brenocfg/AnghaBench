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
struct pipe_buffer {int /*<<< orphan*/  flags; int /*<<< orphan*/  page; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIPE_BUF_FLAG_LRU ; 
 int /*<<< orphan*/  page_cache_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void page_cache_pipe_buf_release(struct pipe_inode_info *pipe,
					struct pipe_buffer *buf)
{
	page_cache_release(buf->page);
	buf->flags &= ~PIPE_BUF_FLAG_LRU;
}