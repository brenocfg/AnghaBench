#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct vnode_attr {int /*<<< orphan*/  va_flags; } ;
struct timeval {scalar_t__ tv_sec; } ;
struct nfsmount {int nm_vers; int /*<<< orphan*/  nm_mountp; } ;
struct nfs_vattr {int /*<<< orphan*/  nva_nlink; int /*<<< orphan*/  nva_gid; int /*<<< orphan*/  nva_uid; int /*<<< orphan*/  nva_mode; int /*<<< orphan*/  nva_fileid; } ;
typedef  TYPE_2__* nfsnode_t ;
struct TYPE_8__ {int /*<<< orphan*/ * val; } ;
struct TYPE_10__ {TYPE_1__ f_fsid; } ;
struct TYPE_9__ {scalar_t__ n_evtstamp; int /*<<< orphan*/  n_events; } ;

/* Variables and functions */
 struct nfsmount* NFSTONMP (TYPE_2__*) ; 
 int /*<<< orphan*/  NFSTOV (TYPE_2__*) ; 
 int /*<<< orphan*/  VATTR_INIT (struct vnode_attr*) ; 
 int /*<<< orphan*/  VATTR_RETURN (struct vnode_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VA_64BITOBJIDS ; 
 int /*<<< orphan*/  microuptime (struct timeval*) ; 
 int /*<<< orphan*/  nfs_getattrcache (TYPE_2__*,struct nfs_vattr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va_fileid ; 
 int /*<<< orphan*/  va_fsid ; 
 int /*<<< orphan*/  va_gid ; 
 int /*<<< orphan*/  va_mode ; 
 int /*<<< orphan*/  va_nlink ; 
 int /*<<< orphan*/  va_uid ; 
 int /*<<< orphan*/  vfs_get_notify_attributes (struct vnode_attr*) ; 
 TYPE_3__* vfs_statfs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnode_attr*) ; 

void
nfs_vnode_notify(nfsnode_t np, uint32_t events)
{
	struct nfsmount *nmp = NFSTONMP(np);
	struct nfs_vattr nvattr;
	struct vnode_attr vattr, *vap = NULL;
	struct timeval now;

	microuptime(&now);
	if ((np->n_evtstamp == now.tv_sec) || !nmp) {
		/* delay sending this notify */
		np->n_events |= events;
		return;
	}
	events |= np->n_events;
	np->n_events = 0;
	np->n_evtstamp = now.tv_sec;

	vfs_get_notify_attributes(&vattr);
	if (!nfs_getattrcache(np, &nvattr, 0)) {
		vap = &vattr;
		VATTR_INIT(vap);

		vap->va_flags |= nmp->nm_vers > 2 ? VA_64BITOBJIDS : 0;
		VATTR_RETURN(vap, va_fsid, vfs_statfs(nmp->nm_mountp)->f_fsid.val[0]);
		VATTR_RETURN(vap, va_fileid, nvattr.nva_fileid);
		VATTR_RETURN(vap, va_mode, nvattr.nva_mode);
		VATTR_RETURN(vap, va_uid, nvattr.nva_uid);
		VATTR_RETURN(vap, va_gid, nvattr.nva_gid);
		VATTR_RETURN(vap, va_nlink, nvattr.nva_nlink);
	}
	vnode_notify(NFSTOV(np), events, vap);
}