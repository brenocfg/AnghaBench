#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct uthread {int uu_defer_reclaims; TYPE_1__* uu_vreclaims; } ;
struct namecache {int dummy; } ;
typedef  int /*<<< orphan*/ * kauth_cred_t ;
struct TYPE_12__ {int v_flag; scalar_t__ v_type; scalar_t__ v_kusecount; char const* v_name; int v_iocount; scalar_t__ v_usecount; int v_lflag; struct TYPE_12__* v_defer_reclaimlist; struct TYPE_12__* v_parent; int /*<<< orphan*/  v_nclinks; scalar_t__ v_cred_timestamp; scalar_t__ v_authorized_actions; int /*<<< orphan*/ * v_cred; int /*<<< orphan*/  v_ncchildren; int /*<<< orphan*/  v_nc_generation; } ;

/* Variables and functions */
 scalar_t__ IS_VALID_CRED (int /*<<< orphan*/ *) ; 
 struct namecache* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NAME_CACHE_LOCK () ; 
 int /*<<< orphan*/  NAME_CACHE_UNLOCK () ; 
 int /*<<< orphan*/ * NOCRED ; 
 TYPE_1__* NULLVP ; 
 struct namecache* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 scalar_t__ VDIR ; 
 int VISNAMEDSTREAM ; 
 int VL_DEAD ; 
 int VL_MARKTERM ; 
 int VL_TERMINATE ; 
 int VNODE_UPDATE_CACHE ; 
 int VNODE_UPDATE_NAME ; 
 int VNODE_UPDATE_PARENT ; 
 int VNODE_UPDATE_PURGE ; 
 scalar_t__ VREG ; 
 int /*<<< orphan*/  cache_delete (struct namecache*,int) ; 
 int /*<<< orphan*/  current_thread () ; 
 struct uthread* get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ **) ; 
 int strlen (char const*) ; 
 char* vfs_addname (char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_removename (char const*) ; 
 int /*<<< orphan*/  vnode_lock_convert (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_lock_spin (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_put (TYPE_1__*) ; 
 scalar_t__ vnode_ref (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_rele (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_rele_internal (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vnode_unlock (TYPE_1__*) ; 

void
vnode_update_identity(vnode_t vp, vnode_t dvp, const char *name, int name_len, uint32_t name_hashval, int flags)
{
	struct	namecache *ncp;
        vnode_t	old_parentvp = NULLVP;
	int isstream = (vp->v_flag & VISNAMEDSTREAM);
	int kusecountbumped = 0;
	kauth_cred_t tcred = NULL;
	const char *vname = NULL;
	const char *tname = NULL;

	if (flags & VNODE_UPDATE_PARENT) {
	        if (dvp && vnode_ref(dvp) != 0) {
			dvp = NULLVP;
		}
		/* Don't count a stream's parent ref during unmounts */
		if (isstream && dvp && (dvp != vp) && (dvp != vp->v_parent) && (dvp->v_type == VREG)) {
			vnode_lock_spin(dvp);
			++dvp->v_kusecount;
			kusecountbumped = 1;
			vnode_unlock(dvp);
		}
	} else {
	        dvp = NULLVP;
	}
	if ( (flags & VNODE_UPDATE_NAME) ) {
		if (name != vp->v_name) {
			if (name && *name) {
				if (name_len == 0)
					name_len = strlen(name);
			        tname = vfs_addname(name, name_len, name_hashval, 0);
			}
		} else
			flags &= ~VNODE_UPDATE_NAME;
	}
	if ( (flags & (VNODE_UPDATE_PURGE | VNODE_UPDATE_PARENT | VNODE_UPDATE_CACHE | VNODE_UPDATE_NAME)) ) {

		NAME_CACHE_LOCK();

		if ( (flags & VNODE_UPDATE_PURGE) ) {

			if (vp->v_parent)
				vp->v_parent->v_nc_generation++;

			while ( (ncp = LIST_FIRST(&vp->v_nclinks)) )
				cache_delete(ncp, 1);

			while ( (ncp = TAILQ_FIRST(&vp->v_ncchildren)) )
				cache_delete(ncp, 1);

			/*
			 * Use a temp variable to avoid kauth_cred_unref() while NAME_CACHE_LOCK is held
			 */
			tcred = vp->v_cred;
			vp->v_cred = NOCRED;
			vp->v_authorized_actions = 0;
			vp->v_cred_timestamp = 0;
		}
		if ( (flags & VNODE_UPDATE_NAME) ) {
			vname = vp->v_name;
			vp->v_name = tname;
		}
		if (flags & VNODE_UPDATE_PARENT) {
			if (dvp != vp && dvp != vp->v_parent) {
				old_parentvp = vp->v_parent;
				vp->v_parent = dvp;
				dvp = NULLVP;

				if (old_parentvp)
					flags |= VNODE_UPDATE_CACHE;
			}
		}
		if (flags & VNODE_UPDATE_CACHE) {
			while ( (ncp = LIST_FIRST(&vp->v_nclinks)) )
				cache_delete(ncp, 1);
		}
		NAME_CACHE_UNLOCK();
	
		if (vname != NULL)
			vfs_removename(vname);

		if (IS_VALID_CRED(tcred))
			kauth_cred_unref(&tcred);
	}
	if (dvp != NULLVP) {
		/* Back-out the ref we took if we lost a race for vp->v_parent. */
		if (kusecountbumped) {
			vnode_lock_spin(dvp);
			if (dvp->v_kusecount > 0)
				--dvp->v_kusecount;  
			vnode_unlock(dvp);
		}
	        vnode_rele(dvp);
	}
	if (old_parentvp) {
	        struct  uthread *ut;

		if (isstream) {
		        vnode_lock_spin(old_parentvp);
			if ((old_parentvp->v_type != VDIR) && (old_parentvp->v_kusecount > 0))
				--old_parentvp->v_kusecount;
			vnode_unlock(old_parentvp);
		}
	        ut = get_bsdthread_info(current_thread());

		/*
		 * indicated to vnode_rele that it shouldn't do a
		 * vnode_reclaim at this time... instead it will
		 * chain the vnode to the uu_vreclaims list...
		 * we'll be responsible for calling vnode_reclaim
		 * on each of the vnodes in this list...
		 */
		ut->uu_defer_reclaims = 1;
		ut->uu_vreclaims = NULLVP;

	        while ( (vp = old_parentvp) != NULLVP ) {
	  
		        vnode_lock_spin(vp);
			vnode_rele_internal(vp, 0, 0, 1);

			/*
			 * check to see if the vnode is now in the state
			 * that would have triggered a vnode_reclaim in vnode_rele
			 * if it is, we save it's parent pointer and then NULL
			 * out the v_parent field... we'll drop the reference
			 * that was held on the next iteration of this loop...
			 * this short circuits a potential deep recursion if we
			 * have a long chain of parents in this state... 
			 * we'll sit in this loop until we run into
			 * a parent in this chain that is not in this state
			 *
			 * make our check and the vnode_rele atomic
			 * with respect to the current vnode we're working on
			 * by holding the vnode lock
			 * if vnode_rele deferred the vnode_reclaim and has put
			 * this vnode on the list to be reaped by us, than
			 * it has left this vnode with an iocount == 1
			 */
			if ( (vp->v_iocount == 1) && (vp->v_usecount == 0) &&
			     ((vp->v_lflag & (VL_MARKTERM | VL_TERMINATE | VL_DEAD)) == VL_MARKTERM)) {
			        /*
				 * vnode_rele wanted to do a vnode_reclaim on this vnode
				 * it should be sitting on the head of the uu_vreclaims chain
				 * pull the parent pointer now so that when we do the
				 * vnode_reclaim for each of the vnodes in the uu_vreclaims
				 * list, we won't recurse back through here
				 *
				 * need to do a convert here in case vnode_rele_internal
				 * returns with the lock held in the spin mode... it 
				 * can drop and retake the lock under certain circumstances
				 */
			        vnode_lock_convert(vp);

			        NAME_CACHE_LOCK();
				old_parentvp = vp->v_parent;
				vp->v_parent = NULLVP;
				NAME_CACHE_UNLOCK();
			} else {
			        /*
				 * we're done... we ran into a vnode that isn't
				 * being terminated
				 */
			        old_parentvp = NULLVP;
			}
			vnode_unlock(vp);
		}
		ut->uu_defer_reclaims = 0;

		while ( (vp = ut->uu_vreclaims) != NULLVP) {
		        ut->uu_vreclaims = vp->v_defer_reclaimlist;
			
			/*
			 * vnode_put will drive the vnode_reclaim if
			 * we are still the only reference on this vnode
			 */
			vnode_put(vp);
		}
	}
}