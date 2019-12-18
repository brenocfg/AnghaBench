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
typedef  int /*<<< orphan*/  vfs_context_t ;
struct vnode {scalar_t__ v_type; } ;
struct componentname {int cn_flags; char* cn_nameptr; scalar_t__ cn_nameiop; int /*<<< orphan*/  cn_context; } ;

/* Variables and functions */
 scalar_t__ DELETE ; 
 int EISDIR ; 
 int EJUSTRETURN ; 
 int ENOENT ; 
 int ENOTDIR ; 
 int EROFS ; 
 int FOLLOW ; 
 int ISSYMLINK ; 
 int LOCKPARENT ; 
 scalar_t__ LOOKUP ; 
 int MAKEENTRY ; 
 int NOCACHE ; 
 int RDONLY ; 
 scalar_t__ RENAME ; 
 int SAVESTART ; 
 scalar_t__ VDIR ; 
 scalar_t__ VLNK ; 
 int VNOP_LOOKUP (struct vnode*,struct vnode**,struct componentname*,int /*<<< orphan*/ ) ; 
 int WANTPARENT ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ vnode_get (struct vnode*) ; 
 int /*<<< orphan*/  vnode_put (struct vnode*) ; 

int
relookup(struct vnode *dvp, struct vnode **vpp, struct componentname *cnp)
{
	struct vnode *dp = NULL;		/* the directory we are searching */
	int wantparent;			/* 1 => wantparent or lockparent flag */
	int rdonly;			/* lookup read-only flag bit */
	int error = 0;
#ifdef NAMEI_DIAGNOSTIC
	int i, newhash;			/* DEBUG: check name hash */
	char *cp;			/* DEBUG: check name ptr/len */
#endif
	vfs_context_t ctx = cnp->cn_context;;

	/*
	 * Setup: break out flag bits into variables.
	 */
	wantparent = cnp->cn_flags & (LOCKPARENT|WANTPARENT);
	rdonly = cnp->cn_flags & RDONLY;
	cnp->cn_flags &= ~ISSYMLINK;

	if (cnp->cn_flags & NOCACHE)
	        cnp->cn_flags &= ~MAKEENTRY;
	else
	        cnp->cn_flags |= MAKEENTRY;

	dp = dvp;

	/*
	 * Check for degenerate name (e.g. / or "")
	 * which is a way of talking about a directory,
	 * e.g. like "/." or ".".
	 */
	if (cnp->cn_nameptr[0] == '\0') {
		if (cnp->cn_nameiop != LOOKUP || wantparent) {
			error = EISDIR;
			goto bad;
		}
		if (dp->v_type != VDIR) {
			error = ENOTDIR;
			goto bad;
		}
		if ( (vnode_get(dp)) ) {
		        error = ENOENT;
			goto bad;
		}
		*vpp = dp;

		if (cnp->cn_flags & SAVESTART)
			panic("lookup: SAVESTART");
		return (0);
	}
	/*
	 * We now have a segment name to search for, and a directory to search.
	 */
	if ( (error = VNOP_LOOKUP(dp, vpp, cnp, ctx)) ) {
		if (error != EJUSTRETURN)
			goto bad;
#if DIAGNOSTIC
		if (*vpp != NULL)
			panic("leaf should be empty");
#endif
		/*
		 * If creating and at end of pathname, then can consider
		 * allowing file to be created.
		 */
		if (rdonly) {
			error = EROFS;
			goto bad;
		}
		/*
		 * We return with ni_vp NULL to indicate that the entry
		 * doesn't currently exist, leaving a pointer to the
		 * (possibly locked) directory inode in ndp->ni_dvp.
		 */
		return (0);
	}
	dp = *vpp;

#if DIAGNOSTIC
	/*
	 * Check for symbolic link
	 */
	if (dp->v_type == VLNK && (cnp->cn_flags & FOLLOW))
		panic ("relookup: symlink found.\n");
#endif

	/*
	 * Disallow directory write attempts on read-only file systems.
	 */
	if (rdonly &&
	    (cnp->cn_nameiop == DELETE || cnp->cn_nameiop == RENAME)) {
		error = EROFS;
		goto bad2;
	}
	/* ASSERT(dvp == ndp->ni_startdir) */
	
	return (0);

bad2:
	vnode_put(dp);
bad:	
	*vpp = NULL;

	return (error);
}