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
struct quad_buffer_head {int dummy; } ;
struct hpfs_dirent {scalar_t__ down; scalar_t__ last; int /*<<< orphan*/  first; } ;
struct dnode {int dummy; } ;
typedef  int dnode_secno ;

/* Variables and functions */
 int de_down_pointer (struct hpfs_dirent*) ; 
 struct hpfs_dirent* de_next_de (struct hpfs_dirent*) ; 
 struct hpfs_dirent* dnode_first_de (struct dnode*) ; 
 int /*<<< orphan*/  hpfs_brelse4 (struct quad_buffer_head*) ; 
 int /*<<< orphan*/  hpfs_error (struct super_block*,char*,int) ; 
 int /*<<< orphan*/  hpfs_free_dnode (struct super_block*,int) ; 
 struct dnode* hpfs_map_dnode (struct super_block*,int,struct quad_buffer_head*) ; 

void hpfs_remove_dtree(struct super_block *s, dnode_secno dno)
{
	struct quad_buffer_head qbh;
	struct dnode *dnode;
	struct hpfs_dirent *de;
	dnode_secno d1, d2, rdno = dno;
	while (1) {
		if (!(dnode = hpfs_map_dnode(s, dno, &qbh))) return;
		de = dnode_first_de(dnode);
		if (de->last) {
			if (de->down) d1 = de_down_pointer(de);
			else goto error;
			hpfs_brelse4(&qbh);
			hpfs_free_dnode(s, dno);
			dno = d1;
		} else break;
	}
	if (!de->first) goto error;
	d1 = de->down ? de_down_pointer(de) : 0;
	de = de_next_de(de);
	if (!de->last) goto error;
	d2 = de->down ? de_down_pointer(de) : 0;
	hpfs_brelse4(&qbh);
	hpfs_free_dnode(s, dno);
	do {
		while (d1) {
			if (!(dnode = hpfs_map_dnode(s, dno = d1, &qbh))) return;
			de = dnode_first_de(dnode);
			if (!de->last) goto error;
			d1 = de->down ? de_down_pointer(de) : 0;
			hpfs_brelse4(&qbh);
			hpfs_free_dnode(s, dno);
		}
		d1 = d2;
		d2 = 0;
	} while (d1);
	return;
	error:
	hpfs_brelse4(&qbh);
	hpfs_free_dnode(s, dno);
	hpfs_error(s, "directory %08x is corrupted or not empty", rdno);
}