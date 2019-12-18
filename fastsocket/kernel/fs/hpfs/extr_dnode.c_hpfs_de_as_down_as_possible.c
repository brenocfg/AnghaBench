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
struct quad_buffer_head {scalar_t__ data; } ;
struct hpfs_dirent {int /*<<< orphan*/  down; } ;
struct dnode {scalar_t__ up; } ;
typedef  scalar_t__ dnode_secno ;
struct TYPE_2__ {scalar_t__ sb_chk; } ;

/* Variables and functions */
 scalar_t__ de_down_pointer (struct hpfs_dirent*) ; 
 int /*<<< orphan*/  hpfs_brelse4 (struct quad_buffer_head*) ; 
 int /*<<< orphan*/  hpfs_error (struct super_block*,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 TYPE_1__* hpfs_sb (struct super_block*) ; 
 scalar_t__ hpfs_stop_cycles (struct super_block*,scalar_t__,int*,int*,char*) ; 
 struct hpfs_dirent* map_nth_dirent (struct super_block*,scalar_t__,int,struct quad_buffer_head*,int /*<<< orphan*/ *) ; 

dnode_secno hpfs_de_as_down_as_possible(struct super_block *s, dnode_secno dno)
{
	struct quad_buffer_head qbh;
	dnode_secno d = dno;
	dnode_secno up = 0;
	struct hpfs_dirent *de;
	int c1, c2 = 0;

	again:
	if (hpfs_sb(s)->sb_chk)
		if (hpfs_stop_cycles(s, d, &c1, &c2, "hpfs_de_as_down_as_possible"))
			return d;
	if (!(de = map_nth_dirent(s, d, 1, &qbh, NULL))) return dno;
	if (hpfs_sb(s)->sb_chk)
		if (up && ((struct dnode *)qbh.data)->up != up)
			hpfs_error(s, "hpfs_de_as_down_as_possible: bad up pointer; dnode %08x, down %08x points to %08x", up, d, ((struct dnode *)qbh.data)->up);
	if (!de->down) {
		hpfs_brelse4(&qbh);
		return d;
	}
	up = d;
	d = de_down_pointer(de);
	hpfs_brelse4(&qbh);
	goto again;
}