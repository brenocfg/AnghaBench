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
struct super_block {int dummy; } ;
struct buffer_head {void* b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  printk (char*) ; 
 struct buffer_head* sb_getblk (struct super_block*,unsigned int) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 

void *hpfs_get_sector(struct super_block *s, unsigned secno, struct buffer_head **bhp)
{
	struct buffer_head *bh;
	/*return hpfs_map_sector(s, secno, bhp, 0);*/

	cond_resched();

	if ((*bhp = bh = sb_getblk(s, secno)) != NULL) {
		if (!buffer_uptodate(bh)) wait_on_buffer(bh);
		set_buffer_uptodate(bh);
		return bh->b_data;
	} else {
		printk("HPFS: hpfs_get_sector: getblk failed\n");
		return NULL;
	}
}