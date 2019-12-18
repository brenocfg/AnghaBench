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
struct TYPE_2__ {scalar_t__ znode; } ;
struct ubifs_info {int /*<<< orphan*/  ilebs; int /*<<< orphan*/  gap_lebs; TYPE_1__ zroot; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_long_sub (long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_old_idx (struct ubifs_info*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tnc_destroy_cnext (struct ubifs_info*) ; 
 int /*<<< orphan*/  ubifs_clean_zn_cnt ; 
 long ubifs_destroy_tnc_subtree (scalar_t__) ; 

void ubifs_tnc_close(struct ubifs_info *c)
{
	long clean_freed;

	tnc_destroy_cnext(c);
	if (c->zroot.znode) {
		clean_freed = ubifs_destroy_tnc_subtree(c->zroot.znode);
		atomic_long_sub(clean_freed, &ubifs_clean_zn_cnt);
	}
	kfree(c->gap_lebs);
	kfree(c->ilebs);
	destroy_old_idx(c);
}