#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  k_dir_id; } ;
struct TYPE_8__ {int search_start; int beg; int end; int /*<<< orphan*/  inode; TYPE_2__* th; TYPE_1__ key; scalar_t__ formatted_node; } ;
typedef  TYPE_3__ reiserfs_blocknr_hint_t ;
struct TYPE_9__ {int /*<<< orphan*/  k_objectid; int /*<<< orphan*/  k_dir_id; } ;
struct TYPE_7__ {int /*<<< orphan*/  t_super; } ;

/* Variables and functions */
 TYPE_5__* INODE_PKEY (int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_OPTION (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  displace_based_on_dirid ; 
 int keyed_hash (char*,int) ; 

__attribute__((used)) static inline void new_hashed_relocation(reiserfs_blocknr_hint_t * hint)
{
	char *hash_in;
	if (hint->formatted_node) {
		hash_in = (char *)&hint->key.k_dir_id;
	} else {
		if (!hint->inode) {
			//hint->search_start = hint->beg;
			hash_in = (char *)&hint->key.k_dir_id;
		} else
		    if (TEST_OPTION(displace_based_on_dirid, hint->th->t_super))
			hash_in = (char *)(&INODE_PKEY(hint->inode)->k_dir_id);
		else
			hash_in =
			    (char *)(&INODE_PKEY(hint->inode)->k_objectid);
	}

	hint->search_start =
	    hint->beg + keyed_hash(hash_in, 4) % (hint->end - hint->beg);
}