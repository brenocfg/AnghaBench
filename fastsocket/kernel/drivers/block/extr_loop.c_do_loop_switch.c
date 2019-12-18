#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct switch_request {int /*<<< orphan*/  wait; struct file* file; } ;
struct loop_device {int old_gfp_mask; int /*<<< orphan*/  lo_blocksize; struct file* lo_backing_file; } ;
struct file {struct address_space* f_mapping; } ;
struct address_space {TYPE_2__* host; } ;
struct TYPE_4__ {TYPE_1__* i_bdev; int /*<<< orphan*/  i_mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  bd_block_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 int __GFP_FS ; 
 int __GFP_IO ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int mapping_gfp_mask (struct address_space*) ; 
 int /*<<< orphan*/  mapping_set_gfp_mask (struct address_space*,int) ; 

__attribute__((used)) static void do_loop_switch(struct loop_device *lo, struct switch_request *p)
{
	struct file *file = p->file;
	struct file *old_file = lo->lo_backing_file;
	struct address_space *mapping;

	/* if no new file, only flush of queued bios requested */
	if (!file)
		goto out;

	mapping = file->f_mapping;
	mapping_set_gfp_mask(old_file->f_mapping, lo->old_gfp_mask);
	lo->lo_backing_file = file;
	lo->lo_blocksize = S_ISBLK(mapping->host->i_mode) ?
		mapping->host->i_bdev->bd_block_size : PAGE_SIZE;
	lo->old_gfp_mask = mapping_gfp_mask(mapping);
	mapping_set_gfp_mask(mapping, lo->old_gfp_mask & ~(__GFP_IO|__GFP_FS));
out:
	complete(&p->wait);
}