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
struct reiserfs_list_bitmap {int /*<<< orphan*/  bitmaps; int /*<<< orphan*/ * journal_list; } ;
struct reiserfs_bitmap_node {int dummy; } ;

/* Variables and functions */
 int JOURNAL_NUM_BITMAPS ; 
 int /*<<< orphan*/  free_list_bitmaps (struct super_block*,struct reiserfs_list_bitmap*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reiserfs_warning (struct super_block*,char*,char*) ; 
 int /*<<< orphan*/  vmalloc (int) ; 

int reiserfs_allocate_list_bitmaps(struct super_block *sb,
				   struct reiserfs_list_bitmap *jb_array,
				   unsigned int bmap_nr)
{
	int i;
	int failed = 0;
	struct reiserfs_list_bitmap *jb;
	int mem = bmap_nr * sizeof(struct reiserfs_bitmap_node *);

	for (i = 0; i < JOURNAL_NUM_BITMAPS; i++) {
		jb = jb_array + i;
		jb->journal_list = NULL;
		jb->bitmaps = vmalloc(mem);
		if (!jb->bitmaps) {
			reiserfs_warning(sb, "clm-2000", "unable to "
					 "allocate bitmaps for journal lists");
			failed = 1;
			break;
		}
		memset(jb->bitmaps, 0, mem);
	}
	if (failed) {
		free_list_bitmaps(sb, jb_array);
		return -1;
	}
	return 0;
}