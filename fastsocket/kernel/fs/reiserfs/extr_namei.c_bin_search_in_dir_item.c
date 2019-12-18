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
struct reiserfs_dir_entry {int de_entry_num; struct reiserfs_de_head* de_deh; struct item_head* de_ih; } ;
struct reiserfs_de_head {int dummy; } ;
struct item_head {int dummy; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int I_ENTRY_COUNT (struct item_head*) ; 
 int NAME_FOUND ; 
 int NAME_NOT_FOUND ; 
 scalar_t__ deh_offset (struct reiserfs_de_head*) ; 

__attribute__((used)) static int bin_search_in_dir_item(struct reiserfs_dir_entry *de, loff_t off)
{
	struct item_head *ih = de->de_ih;
	struct reiserfs_de_head *deh = de->de_deh;
	int rbound, lbound, j;

	lbound = 0;
	rbound = I_ENTRY_COUNT(ih) - 1;

	for (j = (rbound + lbound) / 2; lbound <= rbound;
	     j = (rbound + lbound) / 2) {
		if (off < deh_offset(deh + j)) {
			rbound = j - 1;
			continue;
		}
		if (off > deh_offset(deh + j)) {
			lbound = j + 1;
			continue;
		}
		// this is not name found, but matched third key component
		de->de_entry_num = j;
		return NAME_FOUND;
	}

	de->de_entry_num = lbound;
	return NAME_NOT_FOUND;
}