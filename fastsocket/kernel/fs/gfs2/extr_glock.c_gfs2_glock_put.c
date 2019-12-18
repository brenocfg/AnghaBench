#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* ls_ops; } ;
struct gfs2_sbd {TYPE_2__ sd_lockstruct; } ;
struct gfs2_glock {int /*<<< orphan*/  gl_holders; int /*<<< orphan*/  gl_hash; int /*<<< orphan*/  gl_list; int /*<<< orphan*/  gl_ref; struct gfs2_sbd* gl_sbd; } ;
struct address_space {scalar_t__ nrpages; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* lm_put_lock ) (struct gfs2_glock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GLOCK_BUG_ON (struct gfs2_glock*,int) ; 
 int /*<<< orphan*/  __gfs2_glock_remove_from_lru (struct gfs2_glock*) ; 
 scalar_t__ atomic_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct address_space* gfs2_glock2aspace (struct gfs2_glock*) ; 
 int /*<<< orphan*/  hlist_bl_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lru_lock ; 
 int /*<<< orphan*/  spin_lock_bucket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bucket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct gfs2_glock*) ; 
 int /*<<< orphan*/  trace_gfs2_glock_put (struct gfs2_glock*) ; 

void gfs2_glock_put(struct gfs2_glock *gl)
{
	struct gfs2_sbd *sdp = gl->gl_sbd;
	struct address_space *mapping = gfs2_glock2aspace(gl);

	if (atomic_dec_and_lock(&gl->gl_ref, &lru_lock)) {
		__gfs2_glock_remove_from_lru(gl);
		spin_unlock(&lru_lock);
		spin_lock_bucket(gl->gl_hash);
		hlist_bl_del_rcu(&gl->gl_list);
		spin_unlock_bucket(gl->gl_hash);
		GLOCK_BUG_ON(gl, !list_empty(&gl->gl_holders));
		GLOCK_BUG_ON(gl, mapping && mapping->nrpages);
		trace_gfs2_glock_put(gl);
		sdp->sd_lockstruct.ls_ops->lm_put_lock(gl);
	}
}