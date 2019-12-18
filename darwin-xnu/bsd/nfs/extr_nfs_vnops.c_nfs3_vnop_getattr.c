#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct vnop_getattr_args {TYPE_5__* a_vp; int /*<<< orphan*/  a_context; struct vnode_attr* a_vap; } ;
struct TYPE_11__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_10__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_9__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct vnode_attr {int va_active; TYPE_4__ va_change_time; TYPE_3__ va_modify_time; TYPE_2__ va_access_time; int /*<<< orphan*/  va_flags; } ;
struct nfsmount {int nm_vers; } ;
struct TYPE_8__ {int /*<<< orphan*/  specdata2; int /*<<< orphan*/  specdata1; } ;
struct nfs_vattr {int /*<<< orphan*/ * nva_timensec; int /*<<< orphan*/ * nva_timesec; int /*<<< orphan*/  nva_bytes; int /*<<< orphan*/  nva_size; int /*<<< orphan*/  nva_fileid; int /*<<< orphan*/  nva_nlink; int /*<<< orphan*/  nva_gid; int /*<<< orphan*/  nva_uid; TYPE_1__ nva_rawdev; int /*<<< orphan*/  nva_mode; int /*<<< orphan*/  nva_type; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_12__ {char* v_name; } ;

/* Variables and functions */
 int NFS3_SUPPORTED_VATTRS ; 
 size_t NFSTIME_ACCESS ; 
 size_t NFSTIME_CHANGE ; 
 size_t NFSTIME_MODIFY ; 
 int /*<<< orphan*/  NFS_VNOP_DBG (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NGA_CACHED ; 
 scalar_t__ VATTR_IS_ACTIVE (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VATTR_RETURN (struct vnode_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VATTR_SET_SUPPORTED (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VA_64BITOBJIDS ; 
 scalar_t__ VM_KERNEL_ADDRPERM (TYPE_5__*) ; 
 int /*<<< orphan*/  VTONFS (TYPE_5__*) ; 
 struct nfsmount* VTONMP (TYPE_5__*) ; 
 int /*<<< orphan*/  makedev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfs_getattr (int /*<<< orphan*/ ,struct nfs_vattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_iosize ; 
 int /*<<< orphan*/  va_access_time ; 
 int /*<<< orphan*/  va_change_time ; 
 int /*<<< orphan*/  va_data_alloc ; 
 int /*<<< orphan*/  va_data_size ; 
 int /*<<< orphan*/  va_fileid ; 
 int /*<<< orphan*/  va_gid ; 
 int /*<<< orphan*/  va_iosize ; 
 int /*<<< orphan*/  va_mode ; 
 int /*<<< orphan*/  va_modify_time ; 
 int /*<<< orphan*/  va_name ; 
 int /*<<< orphan*/  va_nlink ; 
 int /*<<< orphan*/  va_rdev ; 
 int /*<<< orphan*/  va_type ; 
 int /*<<< orphan*/  va_uid ; 

int
nfs3_vnop_getattr(
	struct vnop_getattr_args /* {
		struct vnodeop_desc *a_desc;
		vnode_t a_vp;
		struct vnode_attr *a_vap;
		vfs_context_t a_context;
	} */ *ap)
{
	int error;
	struct nfs_vattr nva;
	struct vnode_attr *vap = ap->a_vap;
	struct nfsmount *nmp;
	dev_t rdev;

	/*
	 * Lets don't go over the wire if we don't support any of the attributes.
	 * Just fall through at the VFS layer and let it cons up what it needs.
	 */
	/* Return the io size no matter what, since we don't go over the wire for this */
	VATTR_RETURN(vap, va_iosize, nfs_iosize);
	if ((vap->va_active & NFS3_SUPPORTED_VATTRS) == 0)
		return (0);

	if (VATTR_IS_ACTIVE(ap->a_vap, va_name))
	    NFS_VNOP_DBG("Getting attrs for 0x%llx, vname is %s\n", 
	          (uint64_t)VM_KERNEL_ADDRPERM(ap->a_vp),
	          ap->a_vp->v_name ? ap->a_vp->v_name : "empty");
	error = nfs_getattr(VTONFS(ap->a_vp), &nva, ap->a_context, NGA_CACHED);
	if (error)
		return (error);

	/* copy nva to *a_vap */
	nmp = VTONMP(ap->a_vp);
	vap->va_flags |= nmp ? (nmp->nm_vers > 2 ? VA_64BITOBJIDS : 0) : 0;
	VATTR_RETURN(vap, va_type, nva.nva_type);
	VATTR_RETURN(vap, va_mode, nva.nva_mode);
	rdev = makedev(nva.nva_rawdev.specdata1, nva.nva_rawdev.specdata2);
	VATTR_RETURN(vap, va_rdev, rdev);
	VATTR_RETURN(vap, va_uid, nva.nva_uid);
	VATTR_RETURN(vap, va_gid, nva.nva_gid);
	VATTR_RETURN(vap, va_nlink, nva.nva_nlink);
	VATTR_RETURN(vap, va_fileid, nva.nva_fileid);
	VATTR_RETURN(vap, va_data_size, nva.nva_size);
	VATTR_RETURN(vap, va_data_alloc, nva.nva_bytes);
	vap->va_access_time.tv_sec = nva.nva_timesec[NFSTIME_ACCESS];
	vap->va_access_time.tv_nsec = nva.nva_timensec[NFSTIME_ACCESS];
	VATTR_SET_SUPPORTED(vap, va_access_time);
	vap->va_modify_time.tv_sec = nva.nva_timesec[NFSTIME_MODIFY];
	vap->va_modify_time.tv_nsec = nva.nva_timensec[NFSTIME_MODIFY];
	VATTR_SET_SUPPORTED(vap, va_modify_time);
	vap->va_change_time.tv_sec = nva.nva_timesec[NFSTIME_CHANGE];
	vap->va_change_time.tv_nsec = nva.nva_timensec[NFSTIME_CHANGE];
	VATTR_SET_SUPPORTED(vap, va_change_time);

	// VATTR_RETURN(vap, va_encoding, 0xffff /* kTextEncodingUnknown */);
	return (error);
}