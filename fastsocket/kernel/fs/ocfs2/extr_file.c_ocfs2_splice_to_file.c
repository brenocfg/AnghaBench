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
struct splice_desc {int /*<<< orphan*/  total_len; int /*<<< orphan*/  pos; } ;
struct pipe_inode_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dentry; } ;
struct file {TYPE_1__ f_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_prepare_inode_for_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pipe_to_file ; 
 int splice_from_pipe_feed (struct pipe_inode_info*,struct splice_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_splice_to_file(struct pipe_inode_info *pipe,
				struct file *out,
				struct splice_desc *sd)
{
	int ret;

	ret = ocfs2_prepare_inode_for_write(out->f_path.dentry,	&sd->pos,
					    sd->total_len, 0, NULL);
	if (ret < 0) {
		mlog_errno(ret);
		return ret;
	}

	return splice_from_pipe_feed(pipe, sd, pipe_to_file);
}