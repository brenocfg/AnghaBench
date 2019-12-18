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
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/ * uio_t ;
typedef  size_t uint32_t ;
typedef  TYPE_2__* kauth_filesec_t ;
struct TYPE_8__ {int /*<<< orphan*/  acl_entrycount; } ;
struct TYPE_9__ {size_t fsec_magic; TYPE_1__ fsec_acl; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_USER_ADDR_T (TYPE_2__*) ; 
 int EJUSTRETURN ; 
 int ENOATTR ; 
 int ENOENT ; 
 int ENOMEM ; 
 size_t KAUTH_ACL_MAX_ENTRIES ; 
 int /*<<< orphan*/  KAUTH_DEBUG (char*,...) ; 
 int /*<<< orphan*/  KAUTH_ENDIAN_HOST ; 
 size_t KAUTH_FILESEC_COUNT (size_t) ; 
 int /*<<< orphan*/  KAUTH_FILESEC_MAGIC ; 
 size_t KAUTH_FILESEC_NOACL ; 
 size_t KAUTH_FILESEC_SIZE (size_t) ; 
 int /*<<< orphan*/  KAUTH_FILESEC_VALID (size_t) ; 
 int /*<<< orphan*/  KAUTH_FILESEC_XATTR ; 
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  XATTR_NOSECURITY ; 
 int /*<<< orphan*/  kauth_filesec_acl_setendian (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* kauth_filesec_alloc (size_t) ; 
 int /*<<< orphan*/  kauth_filesec_free (TYPE_2__*) ; 
 size_t ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ uio_addiov (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * uio_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uio_free (int /*<<< orphan*/ *) ; 
 int vn_getxattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vnode_get_filesec(vnode_t vp, kauth_filesec_t *fsecp, vfs_context_t ctx)
{
	kauth_filesec_t fsec;
	uio_t	fsec_uio;
	size_t	fsec_size;
	size_t	xsize, rsize;
	int	error;
	uint32_t	host_fsec_magic;
	uint32_t	host_acl_entrycount;

	fsec = NULL;
	fsec_uio = NULL;

	/* find out how big the EA is */
	error = vn_getxattr(vp, KAUTH_FILESEC_XATTR, NULL, &xsize, XATTR_NOSECURITY, ctx);
	if (error != 0) {
		/* no EA, no filesec */
		if ((error == ENOATTR) || (error == ENOENT) || (error == EJUSTRETURN))
			error = 0;
		/* either way, we are done */
		goto out;
	}

	/*
	 * To be valid, a kauth_filesec_t must be large enough to hold a zero
	 * ACE entrly ACL, and if it's larger than that, it must have the right
	 * number of bytes such that it contains an atomic number of ACEs,
	 * rather than partial entries.  Otherwise, we ignore it.
	 */
	if (!KAUTH_FILESEC_VALID(xsize)) {
		KAUTH_DEBUG("    ERROR - Bogus kauth_fiilesec_t: %ld bytes", xsize);	
		error = 0;
		goto out;
	}
				
	/* how many entries would fit? */
	fsec_size = KAUTH_FILESEC_COUNT(xsize);
	if (fsec_size > KAUTH_ACL_MAX_ENTRIES) {
		KAUTH_DEBUG("    ERROR - Bogus (too large) kauth_fiilesec_t: %ld bytes", xsize);
		error = 0;
		goto out;
	}

	/* get buffer and uio */
	if (((fsec = kauth_filesec_alloc(fsec_size)) == NULL) ||
	    ((fsec_uio = uio_create(1, 0, UIO_SYSSPACE, UIO_READ)) == NULL) ||
	    uio_addiov(fsec_uio, CAST_USER_ADDR_T(fsec), xsize)) {
		KAUTH_DEBUG("    ERROR - could not allocate iov to read ACL");	
		error = ENOMEM;
		goto out;
	}

	/* read security attribute */
	rsize = xsize;
	if ((error = vn_getxattr(vp,
		 KAUTH_FILESEC_XATTR,
		 fsec_uio,
		 &rsize,
		 XATTR_NOSECURITY,
		 ctx)) != 0) {

		/* no attribute - no security data */
		if ((error == ENOATTR) || (error == ENOENT) || (error == EJUSTRETURN))
			error = 0;
		/* either way, we are done */
		goto out;
	}

	/*
	 * Validate security structure; the validation must take place in host
	 * byte order.  If it's corrupt, we will just ignore it.
	 */

	/* Validate the size before trying to convert it */
	if (rsize < KAUTH_FILESEC_SIZE(0)) {
		KAUTH_DEBUG("ACL - DATA TOO SMALL (%d)", rsize);
		goto out;
	}

	/* Validate the magic number before trying to convert it */
	host_fsec_magic = ntohl(KAUTH_FILESEC_MAGIC);
	if (fsec->fsec_magic != host_fsec_magic) {
		KAUTH_DEBUG("ACL - BAD MAGIC %x", host_fsec_magic);
		goto out;
	}

	/* Validate the entry count before trying to convert it. */
	host_acl_entrycount = ntohl(fsec->fsec_acl.acl_entrycount);
	if (host_acl_entrycount != KAUTH_FILESEC_NOACL) {
		if (host_acl_entrycount > KAUTH_ACL_MAX_ENTRIES) {
			KAUTH_DEBUG("ACL - BAD ENTRYCOUNT %x", host_acl_entrycount);
			goto out;
		}
	    	if (KAUTH_FILESEC_SIZE(host_acl_entrycount) > rsize) {
			KAUTH_DEBUG("ACL - BUFFER OVERFLOW (%d entries too big for %d)", host_acl_entrycount, rsize);
			goto out;
		}
	}

	kauth_filesec_acl_setendian(KAUTH_ENDIAN_HOST, fsec, NULL);

	*fsecp = fsec;
	fsec = NULL;
	error = 0;
out:
	if (fsec != NULL)
		kauth_filesec_free(fsec);
	if (fsec_uio != NULL)
		uio_free(fsec_uio);
	if (error)
		*fsecp = NULL;
	return(error);
}