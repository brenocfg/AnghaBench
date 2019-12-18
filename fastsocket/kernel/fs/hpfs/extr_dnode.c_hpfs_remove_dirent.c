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
struct quad_buffer_head {struct dnode* data; } ;
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_version; } ;
struct hpfs_dirent {scalar_t__ down; scalar_t__ last; scalar_t__ first; } ;
struct dnode {int dummy; } ;
typedef  int loff_t ;
typedef  scalar_t__ dnode_secno ;
struct TYPE_2__ {scalar_t__ last; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_DNODES_DEL ; 
 scalar_t__ de_down_pointer (struct hpfs_dirent*) ; 
 TYPE_1__* de_next_de (struct hpfs_dirent*) ; 
 int /*<<< orphan*/  delete_empty_dnode (struct inode*,scalar_t__) ; 
 struct hpfs_dirent* dnode_first_de (struct dnode*) ; 
 int /*<<< orphan*/  for_all_poss (struct inode*,int /*<<< orphan*/ ,int,int) ; 
 int get_pos (struct dnode*,struct hpfs_dirent*) ; 
 int /*<<< orphan*/  hpfs_brelse4 (struct quad_buffer_head*) ; 
 scalar_t__ hpfs_check_free_dnodes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpfs_delete_de (int /*<<< orphan*/ ,struct dnode*,struct hpfs_dirent*) ; 
 int /*<<< orphan*/  hpfs_error (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  hpfs_lock_creation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpfs_mark_4buffers_dirty (struct quad_buffer_head*) ; 
 int /*<<< orphan*/  hpfs_pos_del ; 
 int /*<<< orphan*/  hpfs_pos_subst ; 
 int /*<<< orphan*/  hpfs_unlock_creation (int /*<<< orphan*/ ) ; 
 scalar_t__ move_to_top (struct inode*,scalar_t__,scalar_t__) ; 

int hpfs_remove_dirent(struct inode *i, dnode_secno dno, struct hpfs_dirent *de,
		       struct quad_buffer_head *qbh, int depth)
{
	struct dnode *dnode = qbh->data;
	dnode_secno down = 0;
	int lock = 0;
	loff_t t;
	if (de->first || de->last) {
		hpfs_error(i->i_sb, "hpfs_remove_dirent: attempt to delete first or last dirent in dnode %08x", dno);
		hpfs_brelse4(qbh);
		return 1;
	}
	if (de->down) down = de_down_pointer(de);
	if (depth && (de->down || (de == dnode_first_de(dnode) && de_next_de(de)->last))) {
		lock = 1;
		hpfs_lock_creation(i->i_sb);
		if (hpfs_check_free_dnodes(i->i_sb, FREE_DNODES_DEL)) {
			hpfs_brelse4(qbh);
			hpfs_unlock_creation(i->i_sb);
			return 2;
		}
	}
	i->i_version++;
	for_all_poss(i, hpfs_pos_del, (t = get_pos(dnode, de)) + 1, 1);
	hpfs_delete_de(i->i_sb, dnode, de);
	hpfs_mark_4buffers_dirty(qbh);
	hpfs_brelse4(qbh);
	if (down) {
		dnode_secno a = move_to_top(i, down, dno);
		for_all_poss(i, hpfs_pos_subst, 5, t);
		if (a) delete_empty_dnode(i, a);
		if (lock) hpfs_unlock_creation(i->i_sb);
		return !a;
	}
	delete_empty_dnode(i, dno);
	if (lock) hpfs_unlock_creation(i->i_sb);
	return 0;
}