#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct address_space* i_mapping; int /*<<< orphan*/  i_mode; } ;
struct gfs2_inode {TYPE_3__ i_inode; int /*<<< orphan*/  i_flags; } ;
struct gfs2_glock {TYPE_1__* gl_sbd; int /*<<< orphan*/  gl_ail_count; struct gfs2_inode* gl_object; } ;
struct address_space {int dummy; } ;
struct TYPE_4__ {scalar_t__ sd_rindex_uptodate; int /*<<< orphan*/  sd_rindex; } ;

/* Variables and functions */
 int DIO_METADATA ; 
 struct gfs2_inode* GFS2_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIF_INVALID ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  forget_all_cached_acls (TYPE_3__*) ; 
 int /*<<< orphan*/  gfs2_assert_withdraw (TYPE_1__*,int) ; 
 int /*<<< orphan*/  gfs2_dir_hash_inval (struct gfs2_inode*) ; 
 struct address_space* gfs2_glock2aspace (struct gfs2_glock*) ; 
 int /*<<< orphan*/  gfs2_log_flush (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  truncate_inode_pages (struct address_space*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void inode_go_inval(struct gfs2_glock *gl, int flags)
{
	struct gfs2_inode *ip = gl->gl_object;

	gfs2_assert_withdraw(gl->gl_sbd, !atomic_read(&gl->gl_ail_count));

	if (flags & DIO_METADATA) {
		struct address_space *mapping = gfs2_glock2aspace(gl);
		truncate_inode_pages(mapping, 0);
		if (ip) {
			set_bit(GIF_INVALID, &ip->i_flags);
			forget_all_cached_acls(&ip->i_inode);
			gfs2_dir_hash_inval(ip);
		}
	}

	if (ip == GFS2_I(gl->gl_sbd->sd_rindex)) {
		gfs2_log_flush(gl->gl_sbd, NULL);
		gl->gl_sbd->sd_rindex_uptodate = 0;
	}
	if (ip && S_ISREG(ip->i_inode.i_mode))
		truncate_inode_pages(ip->i_inode.i_mapping, 0);
}