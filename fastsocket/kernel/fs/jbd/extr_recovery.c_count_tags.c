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
struct buffer_head {char* b_data; } ;
typedef  int /*<<< orphan*/  journal_header_t ;
struct TYPE_2__ {int t_flags; } ;
typedef  TYPE_1__ journal_block_tag_t ;

/* Variables and functions */
 int /*<<< orphan*/  JFS_FLAG_LAST_TAG ; 
 int /*<<< orphan*/  JFS_FLAG_SAME_UUID ; 
 int cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int count_tags(struct buffer_head *bh, int size)
{
	char *			tagp;
	journal_block_tag_t *	tag;
	int			nr = 0;

	tagp = &bh->b_data[sizeof(journal_header_t)];

	while ((tagp - bh->b_data + sizeof(journal_block_tag_t)) <= size) {
		tag = (journal_block_tag_t *) tagp;

		nr++;
		tagp += sizeof(journal_block_tag_t);
		if (!(tag->t_flags & cpu_to_be32(JFS_FLAG_SAME_UUID)))
			tagp += 16;

		if (tag->t_flags & cpu_to_be32(JFS_FLAG_LAST_TAG))
			break;
	}

	return nr;
}