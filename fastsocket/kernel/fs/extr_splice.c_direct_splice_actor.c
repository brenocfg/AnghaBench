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
struct TYPE_2__ {struct file* file; } ;
struct splice_desc {int /*<<< orphan*/  flags; int /*<<< orphan*/  total_len; TYPE_1__ u; } ;
struct pipe_inode_info {int dummy; } ;
struct file {int /*<<< orphan*/  f_pos; } ;

/* Variables and functions */
 int do_splice_from (struct pipe_inode_info*,struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int direct_splice_actor(struct pipe_inode_info *pipe,
			       struct splice_desc *sd)
{
	struct file *file = sd->u.file;

	return do_splice_from(pipe, file, &file->f_pos, sd->total_len,
			      sd->flags);
}