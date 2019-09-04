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
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int uint64_t ;
struct nameidata {int /*<<< orphan*/  ni_vp; } ;
struct attrlist {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;

/* Variables and functions */
 int /*<<< orphan*/  AUDITVNPATH1 ; 
 int /*<<< orphan*/  FOLLOW ; 
 int FSOPT_NOFOLLOW ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NOCRED ; 
 int /*<<< orphan*/  OP_GETATTR ; 
 int getattrlist_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct attrlist*,int /*<<< orphan*/ ,size_t,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nameiat (struct nameidata*,int) ; 
 int /*<<< orphan*/  nameidone (struct nameidata*) ; 
 int /*<<< orphan*/  vnode_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
getattrlistat_internal(vfs_context_t ctx, user_addr_t path,
    struct attrlist *alp, user_addr_t attributeBuffer, size_t bufferSize,
    uint64_t options, enum uio_seg segflg, enum uio_seg pathsegflg, int fd)
{
	struct nameidata nd;
	vnode_t vp;
	int32_t nameiflags;
	int error;

	nameiflags = 0;
	/*
	 * Look up the file.
	 */
	if (!(options & FSOPT_NOFOLLOW))
		nameiflags |= FOLLOW;

	nameiflags |= AUDITVNPATH1;
	NDINIT(&nd, LOOKUP, OP_GETATTR, nameiflags, pathsegflg,
	    path, ctx);

	error = nameiat(&nd, fd);

	if (error)
		return (error);

	vp = nd.ni_vp;

	error = getattrlist_internal(ctx, vp, alp, attributeBuffer,
	    bufferSize, options, segflg, NULL, NOCRED);
	
	/* Retain the namei reference until the getattrlist completes. */
	nameidone(&nd);
	vnode_put(vp);
	return (error);
}