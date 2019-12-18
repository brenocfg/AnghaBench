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
struct gfs2_inode {int /*<<< orphan*/  i_inode; } ;
struct gfs2_ea_location {scalar_t__ el_ea; scalar_t__ el_prev; int /*<<< orphan*/  el_bh; } ;

/* Variables and functions */
 scalar_t__ GFS2_EA2NEXT (scalar_t__) ; 
 int /*<<< orphan*/  GFS2_SB (int /*<<< orphan*/ *) ; 
 int ea_remove_unstuffed (struct gfs2_inode*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_assert_withdraw (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ea_set_remove_unstuffed(struct gfs2_inode *ip,
				   struct gfs2_ea_location *el)
{
	if (el->el_prev && GFS2_EA2NEXT(el->el_prev) != el->el_ea) {
		el->el_prev = GFS2_EA2NEXT(el->el_prev);
		gfs2_assert_withdraw(GFS2_SB(&ip->i_inode),
				     GFS2_EA2NEXT(el->el_prev) == el->el_ea);
	}

	return ea_remove_unstuffed(ip, el->el_bh, el->el_ea, el->el_prev, 0);
}