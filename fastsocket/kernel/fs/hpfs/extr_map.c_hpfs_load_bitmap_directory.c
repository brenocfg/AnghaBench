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
struct super_block {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  scalar_t__ secno ;
struct TYPE_2__ {int sb_fs_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__* hpfs_map_sector (struct super_block*,scalar_t__,struct buffer_head**,int) ; 
 TYPE_1__* hpfs_sb (struct super_block*) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__*,int) ; 
 int /*<<< orphan*/  printk (char*) ; 

secno *hpfs_load_bitmap_directory(struct super_block *s, secno bmp)
{
	struct buffer_head *bh;
	int n = (hpfs_sb(s)->sb_fs_size + 0x200000 - 1) >> 21;
	int i;
	secno *b;
	if (!(b = kmalloc(n * 512, GFP_KERNEL))) {
		printk("HPFS: can't allocate memory for bitmap directory\n");
		return NULL;
	}	
	for (i=0;i<n;i++) {
		secno *d = hpfs_map_sector(s, bmp+i, &bh, n - i - 1);
		if (!d) {
			kfree(b);
			return NULL;
		}
		memcpy((char *)b + 512 * i, d, 512);
		brelse(bh);
	}
	return b;
}