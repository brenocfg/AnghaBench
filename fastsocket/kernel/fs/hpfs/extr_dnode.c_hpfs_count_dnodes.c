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
struct quad_buffer_head {int dummy; } ;
struct hpfs_dirent {scalar_t__ last; int /*<<< orphan*/  first; scalar_t__ directory; scalar_t__ down; } ;
struct dnode {int up; scalar_t__ root_dnode; } ;
typedef  int dnode_secno ;
struct TYPE_2__ {scalar_t__ sb_chk; } ;

/* Variables and functions */
 int de_down_pointer (struct hpfs_dirent*) ; 
 struct hpfs_dirent* de_next_de (struct hpfs_dirent*) ; 
 struct hpfs_dirent* dnode_end_de (struct dnode*) ; 
 struct hpfs_dirent* dnode_first_de (struct dnode*) ; 
 int /*<<< orphan*/  hpfs_brelse4 (struct quad_buffer_head*) ; 
 int /*<<< orphan*/  hpfs_error (struct super_block*,char*,int,int,int) ; 
 struct dnode* hpfs_map_dnode (struct super_block*,int,struct quad_buffer_head*) ; 
 TYPE_1__* hpfs_sb (struct super_block*) ; 
 scalar_t__ hpfs_stop_cycles (struct super_block*,int,int*,int*,char*) ; 

void hpfs_count_dnodes(struct super_block *s, dnode_secno dno, int *n_dnodes,
		       int *n_subdirs, int *n_items)
{
	struct dnode *dnode;
	struct quad_buffer_head qbh;
	struct hpfs_dirent *de;
	dnode_secno ptr, odno = 0;
	int c1, c2 = 0;
	int d1, d2 = 0;
	go_down:
	if (n_dnodes) (*n_dnodes)++;
	if (hpfs_sb(s)->sb_chk)
		if (hpfs_stop_cycles(s, dno, &c1, &c2, "hpfs_count_dnodes #1")) return;
	ptr = 0;
	go_up:
	if (!(dnode = hpfs_map_dnode(s, dno, &qbh))) return;
	if (hpfs_sb(s)->sb_chk) if (odno && odno != -1 && dnode->up != odno)
		hpfs_error(s, "hpfs_count_dnodes: bad up pointer; dnode %08x, down %08x points to %08x", odno, dno, dnode->up);
	de = dnode_first_de(dnode);
	if (ptr) while(1) {
		if (de->down) if (de_down_pointer(de) == ptr) goto process_de;
		if (de->last) {
			hpfs_brelse4(&qbh);
			hpfs_error(s, "hpfs_count_dnodes: pointer to dnode %08x not found in dnode %08x, got here from %08x",
				ptr, dno, odno);
			return;
		}
		de = de_next_de(de);
	}
	next_de:
	if (de->down) {
		odno = dno;
		dno = de_down_pointer(de);
		hpfs_brelse4(&qbh);
		goto go_down;
	}
	process_de:
	if (!de->first && !de->last && de->directory && n_subdirs) (*n_subdirs)++;
	if (!de->first && !de->last && n_items) (*n_items)++;
	if ((de = de_next_de(de)) < dnode_end_de(dnode)) goto next_de;
	ptr = dno;
	dno = dnode->up;
	if (dnode->root_dnode) {
		hpfs_brelse4(&qbh);
		return;
	}
	hpfs_brelse4(&qbh);
	if (hpfs_sb(s)->sb_chk)
		if (hpfs_stop_cycles(s, ptr, &d1, &d2, "hpfs_count_dnodes #2")) return;
	odno = -1;
	goto go_up;
}