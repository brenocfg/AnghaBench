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
typedef  int b_blocknr_t ;
struct TYPE_2__ {int /*<<< orphan*/  retry; int /*<<< orphan*/  in_journal_nohint; int /*<<< orphan*/  in_journal_hint; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_INFO_INC (struct super_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ reiserfs_in_journal (struct super_block*,unsigned int,int,int,int*) ; 
 TYPE_1__ scan_bitmap ; 

__attribute__((used)) static inline int is_block_in_journal(struct super_block *s, unsigned int bmap,
				      int off, int *next)
{
	b_blocknr_t tmp;

	if (reiserfs_in_journal(s, bmap, off, 1, &tmp)) {
		if (tmp) {	/* hint supplied */
			*next = tmp;
			PROC_INFO_INC(s, scan_bitmap.in_journal_hint);
		} else {
			(*next) = off + 1;	/* inc offset to avoid looping. */
			PROC_INFO_INC(s, scan_bitmap.in_journal_nohint);
		}
		PROC_INFO_INC(s, scan_bitmap.retry);
		return 1;
	}
	return 0;
}