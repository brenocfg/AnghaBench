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
struct gfs2_inode {int /*<<< orphan*/  i_rw_mutex; TYPE_1__* i_res; } ;
struct TYPE_2__ {int /*<<< orphan*/  rs_node; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_rsrv_cachep ; 
 TYPE_1__* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_init_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int gfs2_rs_alloc(struct gfs2_inode *ip)
{
	int error = 0;

	down_write(&ip->i_rw_mutex);
	if (ip->i_res)
		goto out;

	ip->i_res = kmem_cache_zalloc(gfs2_rsrv_cachep, GFP_NOFS);
	if (!ip->i_res) {
		error = -ENOMEM;
		goto out;
	}

	rb_init_node(&ip->i_res->rs_node);
 out:
	up_write(&ip->i_rw_mutex);
	return error;
}