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
typedef  int /*<<< orphan*/ * vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
struct vnode_attr {TYPE_2__* va_acl; } ;
typedef  TYPE_2__* kauth_acl_t ;
struct TYPE_8__ {int acl_flags; unsigned int acl_entrycount; TYPE_1__* acl_ace; } ;
struct TYPE_7__ {int ace_flags; } ;

/* Variables and functions */
 int ENOMEM ; 
 int KAUTH_ACE_DIRECTORY_INHERIT ; 
 int KAUTH_ACE_FILE_INHERIT ; 
 int KAUTH_ACE_INHERITED ; 
 int KAUTH_ACE_INHERIT_CONTROL_FLAGS ; 
 int KAUTH_ACE_LIMIT_INHERIT ; 
 int KAUTH_ACE_ONLY_INHERIT ; 
 int KAUTH_ACL_NO_INHERIT ; 
 int /*<<< orphan*/  KAUTH_DEBUG (char*,...) ; 
 unsigned int KAUTH_FILESEC_NOACL ; 
 int /*<<< orphan*/  VATTR_INIT (struct vnode_attr*) ; 
 scalar_t__ VATTR_IS_SUPPORTED (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VATTR_WANTED (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 TYPE_2__* kauth_acl_alloc (int) ; 
 int /*<<< orphan*/  kauth_acl_free (TYPE_2__*) ; 
 int /*<<< orphan*/  va_acl ; 
 int /*<<< orphan*/  vfs_authopaque (int /*<<< orphan*/ ) ; 
 int vnode_getattr (int /*<<< orphan*/ *,struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_mount (int /*<<< orphan*/ *) ; 

int
kauth_acl_inherit(vnode_t dvp, kauth_acl_t initial, kauth_acl_t *product, int isdir, vfs_context_t ctx)
{
	int	entries, error, index;
	unsigned int i;
	struct vnode_attr dva;
	kauth_acl_t inherit, result;

	/*
	 * Fetch the ACL from the directory.  This should never fail.
	 * Note that we don't manage inheritance when the remote server is
	 * doing authorization, since this means server enforcement of
	 * inheritance semantics; we just want to compose the initial
	 * ACL and any inherited ACE entries from the container object.
	 *
	 * XXX TODO: <rdar://3634665> wants a "umask ACL" from the process.
	 */
	inherit = NULL;
	/*
	 * If there is no initial ACL, or there is, and the initial ACLs
	 * flags do not request "no inheritance", then we inherit.  This allows
	 * initial object creation via open_extended() and mkdir_extended()
	 * to reject inheritance for themselves and for inferior nodes by
	 * specifying a non-NULL inital ACL which has the KAUTH_ACL_NO_INHERIT
	 * flag set in the flags field.
	 */
	if ((initial == NULL || !(initial->acl_flags & KAUTH_ACL_NO_INHERIT)) &&
	    (dvp != NULL) && !vfs_authopaque(vnode_mount(dvp))) {
		VATTR_INIT(&dva);
		VATTR_WANTED(&dva, va_acl);
		if ((error = vnode_getattr(dvp, &dva, ctx)) != 0) {
			KAUTH_DEBUG("    ERROR - could not get parent directory ACL for inheritance");
			return(error);
		}
		if (VATTR_IS_SUPPORTED(&dva, va_acl))
			inherit = dva.va_acl;
	}

	/*
	 * Compute the number of entries in the result ACL by scanning the
	 * input lists.
	 */
	entries = 0;
	if (inherit != NULL) {
		for (i = 0; i < inherit->acl_entrycount; i++) {
			if (inherit->acl_ace[i].ace_flags & (isdir ? KAUTH_ACE_DIRECTORY_INHERIT : KAUTH_ACE_FILE_INHERIT))
				entries++;
		}
	}

	if (initial == NULL) {
		/*
		 * XXX 3634665 TODO: if the initial ACL is not specfied by
		 * XXX the caller, fetch the umask ACL from the process,
		 * and use it in place of "initial".
		 */
	}

	if (initial != NULL) {
		if (initial->acl_entrycount != KAUTH_FILESEC_NOACL)
			entries += initial->acl_entrycount;
		else
			initial = NULL;
	}

	/*
	 * If there is no initial ACL, and no inheritable entries, the
	 * object should be created with no ACL at all.
	 * Note that this differs from the case where the initial ACL
	 * is empty, in which case the object must also have an empty ACL.
	 */
	if ((entries == 0) && (initial == NULL)) {
		*product = NULL;
		error = 0;
		goto out;
	}
	
	/*
	 * Allocate the result buffer.
	 */
	if ((result = kauth_acl_alloc(entries)) == NULL) {
		KAUTH_DEBUG("    ERROR - could not allocate %d-entry result buffer for inherited ACL", entries);
		error = ENOMEM;
		goto out;
	}

	/*
	 * Composition is simply:
	 *  - initial direct ACEs
	 *  - inherited ACEs from new parent
	 */
	index = 0;
	if (initial != NULL) {
		for (i = 0; i < initial->acl_entrycount; i++) {
			if (!(initial->acl_ace[i].ace_flags & KAUTH_ACE_INHERITED)) {
				result->acl_ace[index++] = initial->acl_ace[i];
			}
		}
		KAUTH_DEBUG("    INHERIT - applied %d of %d initial entries", index, initial->acl_entrycount);
	}
	if (inherit != NULL) {
		for (i = 0; i < inherit->acl_entrycount; i++) {
			/*
			 * Inherit onto this object?  We inherit only if
			 * the target object is a container object and the
			 * KAUTH_ACE_DIRECTORY_INHERIT bit is set, OR if
			 * if the target object is not a container, and
			 * the KAUTH_ACE_FILE_INHERIT bit is set.
			 */
			if (inherit->acl_ace[i].ace_flags & (isdir ? KAUTH_ACE_DIRECTORY_INHERIT : KAUTH_ACE_FILE_INHERIT)) {
				result->acl_ace[index] = inherit->acl_ace[i];
				result->acl_ace[index].ace_flags |= KAUTH_ACE_INHERITED;
				result->acl_ace[index].ace_flags &= ~KAUTH_ACE_ONLY_INHERIT;
				/*
				 * We do not re-inherit inheritance flags
				 * if the ACE from the container has a
				 * KAUTH_ACE_LIMIT_INHERIT, OR if the new
				 * object is not itself a container (since
				 * inheritance is always container-based).
				 */
				if ((result->acl_ace[index].ace_flags & KAUTH_ACE_LIMIT_INHERIT) || !isdir) {
					result->acl_ace[index].ace_flags &=
					    ~(KAUTH_ACE_INHERIT_CONTROL_FLAGS);
				}
				index++;
			}
		}
	}
	result->acl_entrycount = index;
	*product = result;
	KAUTH_DEBUG("    INHERIT - product ACL has %d entries", index);
	error = 0;
out:
	if (inherit != NULL)
		kauth_acl_free(inherit);
	return(error);
}