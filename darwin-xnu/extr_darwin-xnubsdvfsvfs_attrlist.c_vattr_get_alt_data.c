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
typedef  scalar_t__ vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
struct vnode_attr {int /*<<< orphan*/  va_fileid; int /*<<< orphan*/  va_parentid; } ;
struct attrlist {int commonattr; int fileattr; int dirattr; } ;

/* Variables and functions */
 int ATTR_CMN_FILEID ; 
 int ATTR_CMN_NAME ; 
 int ATTR_CMN_OBJID ; 
 int ATTR_CMN_OBJPERMANENTID ; 
 int ATTR_CMN_PARENTID ; 
 int ATTR_CMN_PAROBJID ; 
 int ATTR_CMN_SCRIPT ; 
 int ATTR_DIR_LINKCOUNT ; 
 int ATTR_FILE_DATAALLOCSIZE ; 
 int ATTR_FILE_DATALENGTH ; 
 scalar_t__ NULLVP ; 
 int /*<<< orphan*/  VATTR_CLEAR_ACTIVE (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VATTR_INIT (struct vnode_attr*) ; 
 scalar_t__ VATTR_IS_SUPPORTED (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VATTR_RETURN (struct vnode_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VATTR_SET_SUPPORTED (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VATTR_WANTED (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va_data_alloc ; 
 int /*<<< orphan*/  va_data_size ; 
 int /*<<< orphan*/  va_dirlinkcount ; 
 int /*<<< orphan*/  va_encoding ; 
 int /*<<< orphan*/  va_fileid ; 
 int /*<<< orphan*/  va_linkid ; 
 int /*<<< orphan*/  va_name ; 
 int /*<<< orphan*/  va_parentid ; 
 scalar_t__ vnode_getattr (scalar_t__,struct vnode_attr*,int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_getparent (scalar_t__) ; 
 int /*<<< orphan*/  vnode_put (scalar_t__) ; 

__attribute__((used)) static void
vattr_get_alt_data(vnode_t vp, struct attrlist *alp, struct vnode_attr *vap,
    int return_valid, int is_bulk, vfs_context_t ctx)
{
	/*
	 * There are a couple of special cases.
	 * If we are after object IDs, we can make do with va_fileid.
	 */
	if ((alp->commonattr &
	    (ATTR_CMN_OBJID | ATTR_CMN_OBJPERMANENTID | ATTR_CMN_FILEID)) &&
	    !VATTR_IS_SUPPORTED(vap, va_linkid)) {
		/* forget we wanted this */
		VATTR_CLEAR_ACTIVE(vap, va_linkid);
	}
	
	/*
	 * Many filesystems don't know their parent object id.
	 * If necessary, attempt to derive it from the vnode.
	 */
	if ((alp->commonattr & (ATTR_CMN_PAROBJID | ATTR_CMN_PARENTID)) &&
	    !VATTR_IS_SUPPORTED(vap, va_parentid) && vp && !is_bulk) {
		vnode_t	dvp;

		if ((dvp = vnode_getparent(vp)) != NULLVP) {
			struct vnode_attr lva;

			VATTR_INIT(&lva);
			VATTR_WANTED(&lva, va_fileid);
			if (vnode_getattr(dvp, &lva, ctx) == 0 &&
			    VATTR_IS_SUPPORTED(vap, va_fileid)) {
				vap->va_parentid = lva.va_fileid;
				VATTR_SET_SUPPORTED(vap, va_parentid);
			}
			vnode_put(dvp);
		}
	}
	/*
	 * And we can report datasize/alloc from total.
	 */
	if ((alp->fileattr & ATTR_FILE_DATALENGTH) &&
	    !VATTR_IS_SUPPORTED(vap, va_data_size)) {
		VATTR_CLEAR_ACTIVE(vap, va_data_size);
	}

	if ((alp->fileattr & ATTR_FILE_DATAALLOCSIZE) &&
	    !VATTR_IS_SUPPORTED(vap, va_data_alloc)) {
		VATTR_CLEAR_ACTIVE(vap, va_data_alloc);
	}

	/*
	 * If we don't have an encoding, go with UTF-8
	 */
	if ((alp->commonattr & ATTR_CMN_SCRIPT) &&
	    !VATTR_IS_SUPPORTED(vap, va_encoding) && !return_valid) {
		VATTR_RETURN(vap, va_encoding,
		    0x7e /* kTextEncodingMacUnicode */);
	}

	/*
	 * If we don't have a name, we'll get one from the vnode or
	 * mount point.
	 */
	if ((alp->commonattr & ATTR_CMN_NAME) &&
	    !VATTR_IS_SUPPORTED(vap, va_name)) {
		VATTR_CLEAR_ACTIVE(vap, va_name);
	}

	/* If va_dirlinkcount isn't supported use a default of 1. */
	if ((alp->dirattr & ATTR_DIR_LINKCOUNT) &&
	    !VATTR_IS_SUPPORTED(vap, va_dirlinkcount)) {
		VATTR_RETURN(vap, va_dirlinkcount, 1);
	}
}