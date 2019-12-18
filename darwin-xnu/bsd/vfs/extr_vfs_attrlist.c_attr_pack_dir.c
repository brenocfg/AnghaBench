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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct vnode_attr {int /*<<< orphan*/  va_total_size; int /*<<< orphan*/  va_data_size; int /*<<< orphan*/  va_iosize; int /*<<< orphan*/  va_total_alloc; int /*<<< orphan*/  va_data_alloc; scalar_t__ va_nchildren; scalar_t__ va_dirlinkcount; } ;
struct vnode {int v_flag; TYPE_1__* v_resolve; } ;
struct attrlist {int dirattr; } ;
struct TYPE_4__ {int dirattr; } ;
struct _attrlist_buf {TYPE_2__ actual; } ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_3__ {int vr_flags; } ;

/* Variables and functions */
 int ATTR_DIR_ALLOCSIZE ; 
 int ATTR_DIR_DATALENGTH ; 
 int ATTR_DIR_ENTRYCOUNT ; 
 int ATTR_DIR_IOBLOCKSIZE ; 
 int ATTR_DIR_LINKCOUNT ; 
 int ATTR_DIR_MOUNTSTATUS ; 
 int /*<<< orphan*/  ATTR_PACK4 (struct _attrlist_buf,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATTR_PACK8 (struct _attrlist_buf,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIR_MNTSTATUS_MNTPOINT ; 
 int /*<<< orphan*/  DIR_MNTSTATUS_TRIGGER ; 
 scalar_t__ VATTR_IS_SUPPORTED (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int VNT_NO_DIRECT_MOUNT ; 
 int VROOT ; 
 int /*<<< orphan*/  va_data_alloc ; 
 int /*<<< orphan*/  va_data_size ; 
 int /*<<< orphan*/  va_iosize ; 
 int /*<<< orphan*/  va_total_alloc ; 
 int /*<<< orphan*/  va_total_size ; 
 scalar_t__ vnode_mountedhere (struct vnode*) ; 

__attribute__((used)) static errno_t
attr_pack_dir(struct vnode *vp, struct attrlist *alp, struct _attrlist_buf *abp,
    struct vnode_attr *vap, int return_valid, int pack_invalid)
{
	if (alp->dirattr & ATTR_DIR_LINKCOUNT) {  /* full count of entries */
		ATTR_PACK4((*abp), (uint32_t)vap->va_dirlinkcount);
		abp->actual.dirattr |= ATTR_DIR_LINKCOUNT;
	}
	if (alp->dirattr & ATTR_DIR_ENTRYCOUNT) {
		ATTR_PACK4((*abp), (uint32_t)vap->va_nchildren);
		abp->actual.dirattr |= ATTR_DIR_ENTRYCOUNT;
	}
	if (alp->dirattr & ATTR_DIR_MOUNTSTATUS) {
		uint32_t mntstat;

		if (vp) {
			/*
			 * The vnode that is passed down may either be a
			 * top level vnode of a mount stack or a mounted
			 * on vnode. In either case, the directory should
			 * be reported as a mount point.
			 */
			if ((vp->v_flag & VROOT) ||  vnode_mountedhere(vp)) {
				mntstat = DIR_MNTSTATUS_MNTPOINT;
			} else {
				mntstat = 0;
			}
#if CONFIG_TRIGGERS
			/*
			 * Report back on active vnode triggers
			 * that can directly trigger a mount
			 */
			if (vp->v_resolve &&
			    !(vp->v_resolve->vr_flags & VNT_NO_DIRECT_MOUNT)) {
				mntstat |= DIR_MNTSTATUS_TRIGGER;
			}
#endif
		} else {
			mntstat = 0;
		}

		ATTR_PACK4((*abp), mntstat);
		abp->actual.dirattr |= ATTR_DIR_MOUNTSTATUS;
	}
	if (alp->dirattr & ATTR_DIR_ALLOCSIZE) {
		if (VATTR_IS_SUPPORTED(vap, va_data_alloc)) {
			ATTR_PACK8((*abp), vap->va_data_alloc);
			abp->actual.dirattr |= ATTR_DIR_ALLOCSIZE;
		} else if (VATTR_IS_SUPPORTED(vap, va_total_alloc)) {
			ATTR_PACK8((*abp), vap->va_total_alloc);
			abp->actual.dirattr |= ATTR_DIR_ALLOCSIZE;
		} else if (!return_valid || pack_invalid) {
			uint64_t zero_val = 0;
			ATTR_PACK8((*abp), zero_val);
		}
	}
	if (alp->dirattr & ATTR_DIR_IOBLOCKSIZE) {
		if (VATTR_IS_SUPPORTED(vap, va_iosize)) {
			ATTR_PACK4((*abp), vap->va_iosize);
			abp->actual.dirattr |= ATTR_DIR_IOBLOCKSIZE;
		} else if (!return_valid || pack_invalid) {
			ATTR_PACK4((*abp), 0);
		}
	}
	/*
	 * If the filesystem does not support datalength
	 * or dataallocsize, then we infer that totalsize and
	 * totalalloc are substitutes.
	 */
	if (alp->dirattr & ATTR_DIR_DATALENGTH) {
		if (VATTR_IS_SUPPORTED(vap, va_data_size)) {
			ATTR_PACK8((*abp), vap->va_data_size);
			abp->actual.dirattr |= ATTR_DIR_DATALENGTH;
		} else if (VATTR_IS_SUPPORTED(vap, va_total_size)) {
			ATTR_PACK8((*abp), vap->va_total_size);
			abp->actual.dirattr |= ATTR_DIR_DATALENGTH;
		} else if (!return_valid || pack_invalid) {
			uint64_t zero_val = 0;
			ATTR_PACK8((*abp), zero_val);
		}
	}

	return 0;
}