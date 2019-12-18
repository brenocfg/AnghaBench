#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ beg; int end; scalar_t__ search_start; int /*<<< orphan*/ * inode; scalar_t__ formatted_node; } ;
typedef  TYPE_1__ reiserfs_blocknr_hint_t ;
typedef  scalar_t__ b_blocknr_t ;
struct TYPE_5__ {int /*<<< orphan*/  k_dir_id; } ;

/* Variables and functions */
 TYPE_3__* INODE_PKEY (int /*<<< orphan*/ *) ; 
 scalar_t__ keyed_hash (char*,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int old_hashed_relocation(reiserfs_blocknr_hint_t * hint)
{
	b_blocknr_t border;
	u32 hash_in;

	if (hint->formatted_node || hint->inode == NULL) {
		return 0;
	}

	hash_in = le32_to_cpu((INODE_PKEY(hint->inode))->k_dir_id);
	border =
	    hint->beg + (u32) keyed_hash(((char *)(&hash_in)),
					 4) % (hint->end - hint->beg - 1);
	if (border > hint->search_start)
		hint->search_start = border;

	return 1;
}