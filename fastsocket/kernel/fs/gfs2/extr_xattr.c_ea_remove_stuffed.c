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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  i_ctime; } ;
struct gfs2_inode {TYPE_1__ i_inode; int /*<<< orphan*/  i_gl; } ;
struct gfs2_ea_location {struct buffer_head* el_bh; struct gfs2_ea_header* el_prev; struct gfs2_ea_header* el_ea; } ;
struct gfs2_ea_header {int /*<<< orphan*/  ea_type; int /*<<< orphan*/  ea_flags; int /*<<< orphan*/  ea_rec_len; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME ; 
 int /*<<< orphan*/  GFS2_EAFLAG_LAST ; 
 int /*<<< orphan*/  GFS2_EATYPE_UNUSED ; 
 scalar_t__ GFS2_EA_IS_LAST (struct gfs2_ea_header*) ; 
 scalar_t__ GFS2_EA_REC_LEN (struct gfs2_ea_header*) ; 
 int /*<<< orphan*/  GFS2_SB (TYPE_1__*) ; 
 scalar_t__ RES_DINODE ; 
 scalar_t__ RES_EATTR ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  gfs2_dinode_out (struct gfs2_inode*,int /*<<< orphan*/ ) ; 
 int gfs2_meta_inode_buffer (struct gfs2_inode*,struct buffer_head**) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int gfs2_trans_begin (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_end (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ea_remove_stuffed(struct gfs2_inode *ip, struct gfs2_ea_location *el)
{
	struct gfs2_ea_header *ea = el->el_ea;
	struct gfs2_ea_header *prev = el->el_prev;
	struct buffer_head *dibh;
	int error;

	error = gfs2_trans_begin(GFS2_SB(&ip->i_inode), RES_DINODE + RES_EATTR, 0);
	if (error)
		return error;

	gfs2_trans_add_meta(ip->i_gl, el->el_bh);

	if (prev) {
		u32 len;

		len = GFS2_EA_REC_LEN(prev) + GFS2_EA_REC_LEN(ea);
		prev->ea_rec_len = cpu_to_be32(len);

		if (GFS2_EA_IS_LAST(ea))
			prev->ea_flags |= GFS2_EAFLAG_LAST;
	} else {
		ea->ea_type = GFS2_EATYPE_UNUSED;
	}

	error = gfs2_meta_inode_buffer(ip, &dibh);
	if (!error) {
		ip->i_inode.i_ctime = CURRENT_TIME;
		gfs2_trans_add_meta(ip->i_gl, dibh);
		gfs2_dinode_out(ip, dibh->b_data);
		brelse(dibh);
	}

	gfs2_trans_end(GFS2_SB(&ip->i_inode));

	return error;
}