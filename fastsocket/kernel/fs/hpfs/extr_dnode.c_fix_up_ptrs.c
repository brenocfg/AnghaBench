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
struct hpfs_dirent {scalar_t__ down; } ;
struct dnode {scalar_t__ self; scalar_t__ up; scalar_t__ root_dnode; } ;
typedef  scalar_t__ dnode_secno ;

/* Variables and functions */
 int /*<<< orphan*/  de_down_pointer (struct hpfs_dirent*) ; 
 struct hpfs_dirent* de_next_de (struct hpfs_dirent*) ; 
 struct hpfs_dirent* dnode_end_de (struct dnode*) ; 
 struct hpfs_dirent* dnode_first_de (struct dnode*) ; 
 int /*<<< orphan*/  hpfs_brelse4 (struct quad_buffer_head*) ; 
 struct dnode* hpfs_map_dnode (struct super_block*,int /*<<< orphan*/ ,struct quad_buffer_head*) ; 
 int /*<<< orphan*/  hpfs_mark_4buffers_dirty (struct quad_buffer_head*) ; 

__attribute__((used)) static void fix_up_ptrs(struct super_block *s, struct dnode *d)
{
	struct hpfs_dirent *de;
	struct hpfs_dirent *de_end = dnode_end_de(d);
	dnode_secno dno = d->self;
	for (de = dnode_first_de(d); de < de_end; de = de_next_de(de))
		if (de->down) {
			struct quad_buffer_head qbh;
			struct dnode *dd;
			if ((dd = hpfs_map_dnode(s, de_down_pointer(de), &qbh))) {
				if (dd->up != dno || dd->root_dnode) {
					dd->up = dno;
					dd->root_dnode = 0;
					hpfs_mark_4buffers_dirty(&qbh);
				}
				hpfs_brelse4(&qbh);
			}
		}
}