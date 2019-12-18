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
struct file {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 scalar_t__ splice_from_pipe (struct pipe_inode_info*,struct file*,int /*<<< orphan*/ *,size_t,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_pipe_buf ; 

__attribute__((used)) static ssize_t default_file_splice_write(struct pipe_inode_info *pipe,
					 struct file *out, loff_t *ppos,
					 size_t len, unsigned int flags)
{
	ssize_t ret;

	ret = splice_from_pipe(pipe, out, ppos, len, flags, write_pipe_buf);
	if (ret > 0)
		*ppos += ret;

	return ret;
}