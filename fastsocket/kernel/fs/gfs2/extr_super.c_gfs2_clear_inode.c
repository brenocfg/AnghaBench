#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  gh_flags; TYPE_1__* gh_gl; } ;
struct gfs2_inode {TYPE_3__ i_iopen_gh; TYPE_2__* i_gl; } ;
struct TYPE_6__ {int /*<<< orphan*/  gl_work; int /*<<< orphan*/ * gl_object; } ;
struct TYPE_5__ {int /*<<< orphan*/ * gl_object; } ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 int /*<<< orphan*/  GL_NOCACHE ; 
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_dir_hash_inval (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_glock_add_to_lru (TYPE_2__*) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (TYPE_3__*) ; 
 int /*<<< orphan*/  gfs2_glock_put (TYPE_2__*) ; 
 int /*<<< orphan*/  gfs2_ordered_del_inode (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_rs_delete (struct gfs2_inode*) ; 

__attribute__((used)) static void gfs2_clear_inode(struct inode *inode)
{
	struct gfs2_inode *ip = GFS2_I(inode);

	gfs2_dir_hash_inval(ip);
	gfs2_rs_delete(ip);
	gfs2_ordered_del_inode(ip);
	ip->i_gl->gl_object = NULL;
	flush_delayed_work(&ip->i_gl->gl_work);
	gfs2_glock_add_to_lru(ip->i_gl);
	gfs2_glock_put(ip->i_gl);
	ip->i_gl = NULL;
	if (ip->i_iopen_gh.gh_gl) {
		ip->i_iopen_gh.gh_gl->gl_object = NULL;
		ip->i_iopen_gh.gh_flags |= GL_NOCACHE;
		gfs2_glock_dq_uninit(&ip->i_iopen_gh);
	}
}