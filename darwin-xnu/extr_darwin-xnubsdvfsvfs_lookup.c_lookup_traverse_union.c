#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
struct nameidata {TYPE_2__* ni_vp; TYPE_2__* ni_dvp; } ;
struct TYPE_9__ {int v_flag; TYPE_1__* v_mount; struct TYPE_9__* v_parent; } ;
struct TYPE_8__ {TYPE_2__* mnt_vnodecovered; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_USER_ADDR_T (char*) ; 
 int ENAMETOOLONG ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  LOOKUP ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* NULLVP ; 
 int /*<<< orphan*/  OP_LOOKUP ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  USEDVP ; 
 int VROOT ; 
 scalar_t__ kalloc (int) ; 
 int /*<<< orphan*/  kfree (char*,int) ; 
 int namei (struct nameidata*) ; 
 int /*<<< orphan*/  nameidone (struct nameidata*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int strlen (char const*) ; 
 char* vnode_getname (TYPE_2__*) ; 
 scalar_t__ vnode_getwithref (TYPE_2__*) ; 
 int /*<<< orphan*/  vnode_putname (char const*) ; 

int
lookup_traverse_union(vnode_t dvp, vnode_t *new_dvp, vfs_context_t ctx)
{
	char *path = NULL, *pp;
	const char *name, *np;
	int len;
	int error = 0;
	struct nameidata nd;
	vnode_t vp = dvp;

	*new_dvp = NULL;

	if (vp && vp->v_flag & VROOT) {
		*new_dvp = vp->v_mount->mnt_vnodecovered;
		if (vnode_getwithref(*new_dvp))
			return ENOENT;
		return 0;
	}

	path = (char *) kalloc(MAXPATHLEN);
	if (path == NULL) {
		error = ENOMEM;
		goto done;
	}

	/*
	 * Walk back up to the mountpoint following the
	 * v_parent chain and build a slash-separated path.
	 * Then lookup that path starting with the covered vnode.
	 */
	pp = path + (MAXPATHLEN - 1);
	*pp = '\0';

	while (1) {
		name = vnode_getname(vp);
		if (name == NULL) {
			printf("lookup_traverse_union: null parent name: .%s\n", pp);
			error = ENOENT;
			goto done;
		}
		len = strlen(name);
		if ((len + 1) > (pp - path)) {		// Enough space for this name ?
			error = ENAMETOOLONG;
			vnode_putname(name);
			goto done;
		}
		for (np = name + len; len > 0; len--)	// Copy name backwards
			*--pp = *--np;
		vnode_putname(name);
		vp = vp->v_parent;
		if (vp == NULLVP || vp->v_flag & VROOT)
			break;
		*--pp = '/';
	}

	/* Evaluate the path in the underlying mount */
	NDINIT(&nd, LOOKUP, OP_LOOKUP, USEDVP, UIO_SYSSPACE, CAST_USER_ADDR_T(pp), ctx);
	nd.ni_dvp = dvp->v_mount->mnt_vnodecovered;
	error = namei(&nd);
	if (error == 0)
		*new_dvp = nd.ni_vp;
	nameidone(&nd);
done:
	if (path)
		kfree(path, MAXPATHLEN);
	return error;
}