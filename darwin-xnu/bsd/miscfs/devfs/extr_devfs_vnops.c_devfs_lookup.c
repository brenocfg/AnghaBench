#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vfs_context_t ;
struct vnop_lookup_args {struct vnode** a_vpp; struct vnode* a_dvp; struct componentname* a_cnp; } ;
struct vnode {int dummy; } ;
struct proc {int dummy; } ;
struct componentname {int cn_flags; int cn_nameiop; char* cn_nameptr; size_t cn_namelen; int /*<<< orphan*/  cn_context; } ;
struct TYPE_7__ {scalar_t__ dn_type; } ;
typedef  TYPE_1__ devnode_t ;
struct TYPE_8__ {TYPE_1__* de_dnp; } ;
typedef  TYPE_2__ devdirent_t ;

/* Variables and functions */
 int CREATE ; 
 int DELETE ; 
 int /*<<< orphan*/  DEVFS_LOCK () ; 
 int /*<<< orphan*/  DEVFS_UNLOCK () ; 
 scalar_t__ DEV_DIR ; 
 int EAGAIN ; 
 int EISDIR ; 
 int EJUSTRETURN ; 
 int ENOENT ; 
 int ENOTDIR ; 
 int ISDOTDOT ; 
 int ISLASTCN ; 
 int LOCKPARENT ; 
 int RENAME ; 
 TYPE_1__* VTODN (struct vnode*) ; 
 int WANTPARENT ; 
 TYPE_2__* dev_findname (TYPE_1__*,char*) ; 
 int devfs_dntovn (TYPE_1__*,struct vnode**,struct proc*) ; 
 struct proc* vfs_context_proc (int /*<<< orphan*/ ) ; 
 int vnode_get (struct vnode*) ; 
 int /*<<< orphan*/  vnode_put (struct vnode*) ; 

__attribute__((used)) static int
devfs_lookup(struct vnop_lookup_args *ap)
        /*struct vnop_lookup_args {
                struct vnode * a_dvp; directory vnode ptr
                struct vnode ** a_vpp; where to put the result
                struct componentname * a_cnp; the name we want
		vfs_context_t a_context;
        };*/
{
	struct componentname *cnp = ap->a_cnp;
	vfs_context_t ctx = cnp->cn_context;
	struct proc *p = vfs_context_proc(ctx);
	struct vnode *dir_vnode = ap->a_dvp;
	struct vnode **result_vnode = ap->a_vpp;
	devnode_t *   dir_node;       /* the directory we are searching */
	devnode_t *   node = NULL;       /* the node we are searching for */
	devdirent_t * nodename;
	int flags = cnp->cn_flags;
	int op = cnp->cn_nameiop;       /* LOOKUP, CREATE, RENAME, or DELETE */
	int wantparent = flags & (LOCKPARENT|WANTPARENT);
	int error = 0;
	char	heldchar;	/* the char at the end of the name componet */

retry:

	*result_vnode = NULL; /* safe not sorry */ /*XXX*/

	/*  okay to look at directory vnodes ourside devfs lock as they are not aliased */
	dir_node = VTODN(dir_vnode);

	/*
	 * Make sure that our node is a directory as well.
	 */
	if (dir_node->dn_type != DEV_DIR) {
		return (ENOTDIR);
	}

	DEVFS_LOCK();
	/*
	 * temporarily terminate string component
	 */
	heldchar = cnp->cn_nameptr[cnp->cn_namelen];
	cnp->cn_nameptr[cnp->cn_namelen] = '\0';

	nodename = dev_findname(dir_node, cnp->cn_nameptr);
	/*
	 * restore saved character
	 */
	cnp->cn_nameptr[cnp->cn_namelen] = heldchar;

	if (nodename) {
	        /* entry exists */
	        node = nodename->de_dnp;

		/* Do potential vnode allocation here inside the lock 
		 * to make sure that our device node has a non-NULL dn_vn
		 * associated with it.  The device node might otherwise
		 * get deleted out from under us (see devfs_dn_free()).
		 */
		error = devfs_dntovn(node, result_vnode, p);
	}
	DEVFS_UNLOCK();

	if (error) {
	        if (error == EAGAIN)
		        goto retry;
		return error;
	}
	if (!nodename) {
		/*
		 * we haven't called devfs_dntovn if we get here
		 * we have not taken a reference on the node.. no
		 * vnode_put is necessary on these error returns
		 *
		 * If it doesn't exist and we're not the last component,
		 * or we're at the last component, but we're not creating
		 * or renaming, return ENOENT.
		 */
        	if (!(flags & ISLASTCN) || !(op == CREATE || op == RENAME)) {
			return ENOENT;
		}
		/*
		 * We return with the directory locked, so that
		 * the parameters we set up above will still be
		 * valid if we actually decide to add a new entry.
		 * We return ni_vp == NULL to indicate that the entry
		 * does not currently exist; we leave a pointer to
		 * the (locked) directory vnode in namei_data->ni_dvp.
		 *
		 * NB - if the directory is unlocked, then this
		 * information cannot be used.
		 */
		return (EJUSTRETURN);
	}
	/*
	 * from this point forward, we need to vnode_put the reference
	 * picked up in devfs_dntovn if we decide to return an error
	 */

	/*
	 * If deleting, and at end of pathname, return
	 * parameters which can be used to remove file.
	 * If the wantparent flag isn't set, we return only
	 * the directory (in namei_data->ni_dvp), otherwise we go
	 * on and lock the node, being careful with ".".
	 */
	if (op == DELETE && (flags & ISLASTCN)) {

		/*
		 * we are trying to delete '.'.  What does this mean? XXX
		 */
		if (dir_node == node) {
		        if (*result_vnode) {
			        vnode_put(*result_vnode);
			        *result_vnode = NULL;
			}				
			if ( ((error = vnode_get(dir_vnode)) == 0) ) {
			        *result_vnode = dir_vnode;
			}
			return (error);
		}
		return (0);
	}

	/*
	 * If rewriting (RENAME), return the vnode and the
	 * information required to rewrite the present directory
	 * Must get node of directory entry to verify it's a
	 * regular file, or empty directory.
	 */
	if (op == RENAME && wantparent && (flags & ISLASTCN)) {

		/*
		 * Careful about locking second node.
		 * This can only occur if the target is ".".
		 */
		if (dir_node == node) {
		        error = EISDIR;
			goto drop_ref;
		}
		return (0);
	}

	/*
	 * Step through the translation in the name.  We do not unlock the
	 * directory because we may need it again if a symbolic link
	 * is relative to the current directory.  Instead we save it
	 * unlocked as "saved_dir_node" XXX.  We must get the target
	 * node before unlocking
	 * the directory to insure that the node will not be removed
	 * before we get it.  We prevent deadlock by always fetching
	 * nodes from the root, moving down the directory tree. Thus
	 * when following backward pointers ".." we must unlock the
	 * parent directory before getting the requested directory.
	 * There is a potential race condition here if both the current
	 * and parent directories are removed before the lock for the
	 * node associated with ".." returns.  We hope that this occurs
	 * infrequently since we cannot avoid this race condition without
	 * implementing a sophisticated deadlock detection algorithm.
	 * Note also that this simple deadlock detection scheme will not
	 * work if the file system has any hard links other than ".."
	 * that point backwards in the directory structure.
	 */
	if ((flags & ISDOTDOT) == 0 && dir_node == node) {
	        if (*result_vnode) {
		        vnode_put(*result_vnode);
		        *result_vnode = NULL;
		}
		if ( (error = vnode_get(dir_vnode)) ) {
			return (error);
		}
		*result_vnode = dir_vnode;
	}
	return (0);

drop_ref:
	if (*result_vnode) {
	        vnode_put(*result_vnode);
		*result_vnode = NULL;
	}
	return (error);
}