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
struct the_nilfs {int ns_blocks_per_segment; unsigned long ns_nrsvsegs; int /*<<< orphan*/  ns_ndirtyblks; struct inode* ns_sufile; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int nilfs_sufile_get_ncleansegs (struct inode*,unsigned long*) ; 

int nilfs_near_disk_full(struct the_nilfs *nilfs)
{
	struct inode *sufile = nilfs->ns_sufile;
	unsigned long ncleansegs, nincsegs;
	int ret;

	ret = nilfs_sufile_get_ncleansegs(sufile, &ncleansegs);
	if (likely(!ret)) {
		nincsegs = atomic_read(&nilfs->ns_ndirtyblks) /
			nilfs->ns_blocks_per_segment + 1;
		if (ncleansegs <= nilfs->ns_nrsvsegs + nincsegs)
			ret++;
	}
	return ret;
}