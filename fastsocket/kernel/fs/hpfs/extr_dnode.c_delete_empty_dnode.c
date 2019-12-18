#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct quad_buffer_head {int dummy; } ;
struct inode {int i_size; int i_blocks; void* i_ino; int /*<<< orphan*/  i_sb; } ;
struct hpfs_inode_info {void* i_dno; } ;
struct hpfs_dirent {int down; int length; int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; int /*<<< orphan*/  last; } ;
struct TYPE_5__ {TYPE_1__* external; } ;
struct fnode {TYPE_2__ u; } ;
struct dnode {int first_free; int root_dnode; void* up; } ;
struct buffer_head {int dummy; } ;
typedef  int loff_t ;
typedef  void* dnode_secno ;
struct TYPE_6__ {int sb_chk; } ;
struct TYPE_4__ {void* disk_secno; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 void* de_down_pointer (struct hpfs_dirent*) ; 
 struct hpfs_dirent* de_next_de (struct hpfs_dirent*) ; 
 struct hpfs_dirent* dnode_end_de (struct dnode*) ; 
 struct hpfs_dirent* dnode_first_de (struct dnode*) ; 
 struct hpfs_dirent* dnode_last_de (struct dnode*) ; 
 struct hpfs_dirent* dnode_pre_last_de (struct dnode*) ; 
 int /*<<< orphan*/  for_all_poss (struct inode*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  hpfs_add_to_dnode (struct inode*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hpfs_dirent*,void*) ; 
 int /*<<< orphan*/  hpfs_brelse4 (struct quad_buffer_head*) ; 
 int /*<<< orphan*/  hpfs_delete_de (int /*<<< orphan*/ ,struct dnode*,struct hpfs_dirent*) ; 
 int /*<<< orphan*/  hpfs_error (int /*<<< orphan*/ ,char*,void*,...) ; 
 int /*<<< orphan*/  hpfs_free_dnode (int /*<<< orphan*/ ,void*) ; 
 struct hpfs_inode_info* hpfs_i (struct inode*) ; 
 struct dnode* hpfs_map_dnode (int /*<<< orphan*/ ,void*,struct quad_buffer_head*) ; 
 struct fnode* hpfs_map_fnode (int /*<<< orphan*/ ,void*,struct buffer_head**) ; 
 int /*<<< orphan*/  hpfs_mark_4buffers_dirty (struct quad_buffer_head*) ; 
 int /*<<< orphan*/  hpfs_pos_del ; 
 int /*<<< orphan*/  hpfs_pos_subst ; 
 TYPE_3__* hpfs_sb (int /*<<< orphan*/ ) ; 
 scalar_t__ hpfs_stop_cycles (int /*<<< orphan*/ ,void*,int*,int*,char*) ; 
 int /*<<< orphan*/  kfree (struct hpfs_dirent*) ; 
 struct hpfs_dirent* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  memcpy (struct hpfs_dirent*,struct hpfs_dirent*,int) ; 
 int /*<<< orphan*/  memmove (struct hpfs_dirent*,char*,int) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static void delete_empty_dnode(struct inode *i, dnode_secno dno)
{
	struct hpfs_inode_info *hpfs_inode = hpfs_i(i);
	struct quad_buffer_head qbh;
	struct dnode *dnode;
	dnode_secno down, up, ndown;
	int p;
	struct hpfs_dirent *de;
	int c1, c2 = 0;
	try_it_again:
	if (hpfs_stop_cycles(i->i_sb, dno, &c1, &c2, "delete_empty_dnode")) return;
	if (!(dnode = hpfs_map_dnode(i->i_sb, dno, &qbh))) return;
	if (dnode->first_free > 56) goto end;
	if (dnode->first_free == 52 || dnode->first_free == 56) {
		struct hpfs_dirent *de_end;
		int root = dnode->root_dnode;
		up = dnode->up;
		de = dnode_first_de(dnode);
		down = de->down ? de_down_pointer(de) : 0;
		if (hpfs_sb(i->i_sb)->sb_chk) if (root && !down) {
			hpfs_error(i->i_sb, "delete_empty_dnode: root dnode %08x is empty", dno);
			goto end;
		}
		hpfs_brelse4(&qbh);
		hpfs_free_dnode(i->i_sb, dno);
		i->i_size -= 2048;
		i->i_blocks -= 4;
		if (root) {
			struct fnode *fnode;
			struct buffer_head *bh;
			struct dnode *d1;
			struct quad_buffer_head qbh1;
			if (hpfs_sb(i->i_sb)->sb_chk)
			    if (up != i->i_ino) {
				hpfs_error(i->i_sb,
					"bad pointer to fnode, dnode %08x, pointing to %08x, should be %08lx",
					dno, up, (unsigned long)i->i_ino);
				return;
			    }
			if ((d1 = hpfs_map_dnode(i->i_sb, down, &qbh1))) {
				d1->up = up;
				d1->root_dnode = 1;
				hpfs_mark_4buffers_dirty(&qbh1);
				hpfs_brelse4(&qbh1);
			}
			if ((fnode = hpfs_map_fnode(i->i_sb, up, &bh))) {
				fnode->u.external[0].disk_secno = down;
				mark_buffer_dirty(bh);
				brelse(bh);
			}
			hpfs_inode->i_dno = down;
			for_all_poss(i, hpfs_pos_subst, ((loff_t)dno << 4) | 1, (loff_t) 12);
			return;
		}
		if (!(dnode = hpfs_map_dnode(i->i_sb, up, &qbh))) return;
		p = 1;
		de_end = dnode_end_de(dnode);
		for (de = dnode_first_de(dnode); de < de_end; de = de_next_de(de), p++)
			if (de->down) if (de_down_pointer(de) == dno) goto fnd;
		hpfs_error(i->i_sb, "delete_empty_dnode: pointer to dnode %08x not found in dnode %08x", dno, up);
		goto end;
		fnd:
		for_all_poss(i, hpfs_pos_subst, ((loff_t)dno << 4) | 1, ((loff_t)up << 4) | p);
		if (!down) {
			de->down = 0;
			de->length -= 4;
			dnode->first_free -= 4;
			memmove(de_next_de(de), (char *)de_next_de(de) + 4,
				(char *)dnode + dnode->first_free - (char *)de_next_de(de));
		} else {
			struct dnode *d1;
			struct quad_buffer_head qbh1;
			*(dnode_secno *) ((void *) de + de->length - 4) = down;
			if ((d1 = hpfs_map_dnode(i->i_sb, down, &qbh1))) {
				d1->up = up;
				hpfs_mark_4buffers_dirty(&qbh1);
				hpfs_brelse4(&qbh1);
			}
		}
	} else {
		hpfs_error(i->i_sb, "delete_empty_dnode: dnode %08x, first_free == %03x", dno, dnode->first_free);
		goto end;
	}

	if (!de->last) {
		struct hpfs_dirent *de_next = de_next_de(de);
		struct hpfs_dirent *de_cp;
		struct dnode *d1;
		struct quad_buffer_head qbh1;
		if (!de_next->down) goto endm;
		ndown = de_down_pointer(de_next);
		if (!(de_cp = kmalloc(de->length, GFP_NOFS))) {
			printk("HPFS: out of memory for dtree balancing\n");
			goto endm;
		}
		memcpy(de_cp, de, de->length);
		hpfs_delete_de(i->i_sb, dnode, de);
		hpfs_mark_4buffers_dirty(&qbh);
		hpfs_brelse4(&qbh);
		for_all_poss(i, hpfs_pos_subst, ((loff_t)up << 4) | p, 4);
		for_all_poss(i, hpfs_pos_del, ((loff_t)up << 4) | p, 1);
		if (de_cp->down) if ((d1 = hpfs_map_dnode(i->i_sb, de_down_pointer(de_cp), &qbh1))) {
			d1->up = ndown;
			hpfs_mark_4buffers_dirty(&qbh1);
			hpfs_brelse4(&qbh1);
		}
		hpfs_add_to_dnode(i, ndown, de_cp->name, de_cp->namelen, de_cp, de_cp->down ? de_down_pointer(de_cp) : 0);
		/*printk("UP-TO-DNODE: %08x (ndown = %08x, down = %08x, dno = %08x)\n", up, ndown, down, dno);*/
		dno = up;
		kfree(de_cp);
		goto try_it_again;
	} else {
		struct hpfs_dirent *de_prev = dnode_pre_last_de(dnode);
		struct hpfs_dirent *de_cp;
		struct dnode *d1;
		struct quad_buffer_head qbh1;
		dnode_secno dlp;
		if (!de_prev) {
			hpfs_error(i->i_sb, "delete_empty_dnode: empty dnode %08x", up);
			hpfs_mark_4buffers_dirty(&qbh);
			hpfs_brelse4(&qbh);
			dno = up;
			goto try_it_again;
		}
		if (!de_prev->down) goto endm;
		ndown = de_down_pointer(de_prev);
		if ((d1 = hpfs_map_dnode(i->i_sb, ndown, &qbh1))) {
			struct hpfs_dirent *del = dnode_last_de(d1);
			dlp = del->down ? de_down_pointer(del) : 0;
			if (!dlp && down) {
				if (d1->first_free > 2044) {
					if (hpfs_sb(i->i_sb)->sb_chk >= 2) {
						printk("HPFS: warning: unbalanced dnode tree, see hpfs.txt 4 more info\n");
						printk("HPFS: warning: terminating balancing operation\n");
					}
					hpfs_brelse4(&qbh1);
					goto endm;
				}
				if (hpfs_sb(i->i_sb)->sb_chk >= 2) {
					printk("HPFS: warning: unbalanced dnode tree, see hpfs.txt 4 more info\n");
					printk("HPFS: warning: goin'on\n");
				}
				del->length += 4;
				del->down = 1;
				d1->first_free += 4;
			}
			if (dlp && !down) {
				del->length -= 4;
				del->down = 0;
				d1->first_free -= 4;
			} else if (down)
				*(dnode_secno *) ((void *) del + del->length - 4) = down;
		} else goto endm;
		if (!(de_cp = kmalloc(de_prev->length, GFP_NOFS))) {
			printk("HPFS: out of memory for dtree balancing\n");
			hpfs_brelse4(&qbh1);
			goto endm;
		}
		hpfs_mark_4buffers_dirty(&qbh1);
		hpfs_brelse4(&qbh1);
		memcpy(de_cp, de_prev, de_prev->length);
		hpfs_delete_de(i->i_sb, dnode, de_prev);
		if (!de_prev->down) {
			de_prev->length += 4;
			de_prev->down = 1;
			dnode->first_free += 4;
		}
		*(dnode_secno *) ((void *) de_prev + de_prev->length - 4) = ndown;
		hpfs_mark_4buffers_dirty(&qbh);
		hpfs_brelse4(&qbh);
		for_all_poss(i, hpfs_pos_subst, ((loff_t)up << 4) | (p - 1), 4);
		for_all_poss(i, hpfs_pos_subst, ((loff_t)up << 4) | p, ((loff_t)up << 4) | (p - 1));
		if (down) if ((d1 = hpfs_map_dnode(i->i_sb, de_down_pointer(de), &qbh1))) {
			d1->up = ndown;
			hpfs_mark_4buffers_dirty(&qbh1);
			hpfs_brelse4(&qbh1);
		}
		hpfs_add_to_dnode(i, ndown, de_cp->name, de_cp->namelen, de_cp, dlp);
		dno = up;
		kfree(de_cp);
		goto try_it_again;
	}
	endm:
	hpfs_mark_4buffers_dirty(&qbh);
	end:
	hpfs_brelse4(&qbh);
}