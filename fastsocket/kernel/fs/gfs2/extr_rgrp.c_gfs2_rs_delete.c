#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_writecount; } ;
struct gfs2_inode {int /*<<< orphan*/  i_rw_mutex; TYPE_1__* i_res; struct inode i_inode; } ;
struct TYPE_3__ {int /*<<< orphan*/  rs_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_rs_deltree (TYPE_1__*) ; 
 int /*<<< orphan*/  gfs2_rsrv_cachep ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void gfs2_rs_delete(struct gfs2_inode *ip)
{
	struct inode *inode = &ip->i_inode;

	down_write(&ip->i_rw_mutex);
	if (ip->i_res && atomic_read(&inode->i_writecount) <= 1) {
		gfs2_rs_deltree(ip->i_res);
		BUG_ON(ip->i_res->rs_free);
		kmem_cache_free(gfs2_rsrv_cachep, ip->i_res);
		ip->i_res = NULL;
	}
	up_write(&ip->i_rw_mutex);
}