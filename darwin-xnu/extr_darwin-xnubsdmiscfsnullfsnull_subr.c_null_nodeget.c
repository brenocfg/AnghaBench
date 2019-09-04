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
struct vnode {int dummy; } ;
struct mount {int dummy; } ;
struct componentname {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  VTONULL (struct vnode*) ; 
 int null_getnewvnode (struct mount*,struct vnode*,struct vnode*,struct vnode**,struct componentname*,int) ; 
 int null_hashget (struct mount*,struct vnode*,struct vnode**) ; 
 int null_hashins (struct mount*,int /*<<< orphan*/ ,struct vnode**) ; 
 int /*<<< orphan*/  vnode_put (struct vnode*) ; 
 int /*<<< orphan*/  vnode_recycle (struct vnode*) ; 
 int vnode_ref (struct vnode*) ; 
 int /*<<< orphan*/  vnode_rele (struct vnode*) ; 

int
null_nodeget(
    struct mount * mp, struct vnode * lowervp, struct vnode * dvp, struct vnode ** vpp, struct componentname * cnp, int root)
{
	struct vnode * vp;
	int error;

	/* Lookup the hash firstly. */
	error = null_hashget(mp, lowervp, vpp);
	/* ENOENT means it wasn't found, EIO is a failure we should bail from, 0 is it
	 * was found */
	if (error != ENOENT) {
		/* null_hashget checked the vid, so if we got something here its legit to
		 * the best of our knowledge*/
		/* if we found something then there is an iocount on vpp,
		   if we didn't find something then vpp shouldn't be used by the caller */
		return error;
	}

	/*
	 * We do not serialize vnode creation, instead we will check for
	 * duplicates later, when adding new vnode to hash.
	 */
	error = vnode_ref(lowervp); // take a ref on lowervp so we let the system know we care about it
	if(error)
	{
		// Failed to get a reference on the lower vp so bail. Lowervp may be gone already.
		return error;
	}

	error = null_getnewvnode(mp, lowervp, dvp, &vp, cnp, root);

	if (error) {
		vnode_rele(lowervp);
		return (error);
	}

	/*
	 * Atomically insert our new node into the hash or vget existing
	 * if someone else has beaten us to it.
	 */
	error = null_hashins(mp, VTONULL(vp), vpp);
	if (error || *vpp != NULL) {
		/* recycle will call reclaim which will get rid of the internals */
		vnode_recycle(vp);
		vnode_put(vp);
		/* if we found vpp, then null_hashins put an iocount on it */
		return error;
	}

	/* vp has an iocount from null_getnewvnode */
	*vpp = vp;

	return (0);
}