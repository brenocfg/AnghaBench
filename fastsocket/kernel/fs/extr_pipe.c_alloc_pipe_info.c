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
struct pipe_inode_info {int r_counter; int w_counter; struct inode* inode; int /*<<< orphan*/  wait; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct pipe_inode_info* kzalloc (int,int /*<<< orphan*/ ) ; 

struct pipe_inode_info * alloc_pipe_info(struct inode *inode)
{
	struct pipe_inode_info *pipe;

	pipe = kzalloc(sizeof(struct pipe_inode_info), GFP_KERNEL);
	if (pipe) {
		init_waitqueue_head(&pipe->wait);
		pipe->r_counter = pipe->w_counter = 1;
		pipe->inode = inode;
	}

	return pipe;
}