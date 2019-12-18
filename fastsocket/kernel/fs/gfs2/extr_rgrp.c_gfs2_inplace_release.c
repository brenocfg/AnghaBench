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
struct gfs2_inode {struct gfs2_blkreserv* i_res; } ;
struct TYPE_2__ {scalar_t__ gh_gl; } ;
struct gfs2_blkreserv {TYPE_1__ rs_rgd_gh; } ;

/* Variables and functions */
 int /*<<< orphan*/  gfs2_glock_dq_uninit (TYPE_1__*) ; 

void gfs2_inplace_release(struct gfs2_inode *ip)
{
	struct gfs2_blkreserv *rs = ip->i_res;

	if (rs->rs_rgd_gh.gh_gl)
		gfs2_glock_dq_uninit(&rs->rs_rgd_gh);
}