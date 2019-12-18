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
struct seq_file {struct gfs2_glock_iter* private; } ;
struct inode {int /*<<< orphan*/  i_private; } ;
struct gfs2_glock_iter {int /*<<< orphan*/  sdp; } ;
struct file {struct seq_file* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  gfs2_sbstats_seq_ops ; 
 int seq_open_private (struct file*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int gfs2_sbstats_open(struct inode *inode, struct file *file)
{
	int ret = seq_open_private(file, &gfs2_sbstats_seq_ops,
				   sizeof(struct gfs2_glock_iter));
	if (ret == 0) {
		struct seq_file *seq = file->private_data;
		struct gfs2_glock_iter *gi = seq->private;
		gi->sdp = inode->i_private;
	}
	return ret;
}