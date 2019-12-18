#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_25__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_15__ ;

/* Type definitions */
typedef  TYPE_3__* vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uaddr ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct xdrbuf {int /*<<< orphan*/  xb_flags; } ;
struct vfstable {int vfc_flags; int /*<<< orphan*/  vfc_refcount; int /*<<< orphan*/  vfc_name; int /*<<< orphan*/  vfc_vfsops; struct vfstable* vfc_next; } ;
struct TYPE_30__ {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct nfs_dlmount {char const* ndm_mntfrom; scalar_t__ ndm_sotype; int /*<<< orphan*/  ndm_fhlen; int /*<<< orphan*/ * ndm_fh; TYPE_2__ ndm_saddr; scalar_t__ ndm_nfsv3; } ;
struct nameidata {TYPE_3__* ni_vp; } ;
struct mount {int dummy; } ;
struct filedesc {int /*<<< orphan*/ * fd_rdir; int /*<<< orphan*/  fd_cdir; } ;
typedef  TYPE_4__* proc_t ;
typedef  TYPE_5__* mount_t ;
struct TYPE_28__ {int /*<<< orphan*/  f_mntfromname; int /*<<< orphan*/  f_mntonname; int /*<<< orphan*/  f_owner; int /*<<< orphan*/  f_fstypename; } ;
struct TYPE_33__ {int mnt_segreadcnt; int mnt_segwritecnt; int mnt_flag; TYPE_3__* mnt_vnodecovered; TYPE_1__ mnt_vfsstat; int /*<<< orphan*/  mnt_op; struct vfstable* mnt_vtable; int /*<<< orphan*/  mnt_vnodelist; int /*<<< orphan*/  mnt_newvnodes; int /*<<< orphan*/  mnt_workerqueue; scalar_t__ mnt_authcache_ttl; void* mnt_realrootvp; scalar_t__ mnt_ioflags; int /*<<< orphan*/  mnt_maxwritecnt; int /*<<< orphan*/  mnt_maxreadcnt; } ;
struct TYPE_32__ {struct filedesc* p_fd; } ;
struct TYPE_31__ {TYPE_5__* v_mountedhere; } ;
struct TYPE_29__ {int /*<<< orphan*/  mnt_flag; } ;
struct TYPE_27__ {TYPE_25__* tqh_first; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  BUF_WRITE_DATA ; 
 int /*<<< orphan*/  CAST_USER_ADDR_T (char const*) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENOTDIR ; 
 int FOLLOW ; 
 int /*<<< orphan*/  FREE_ZONE (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LK_NOWAIT ; 
 int LOCKLEAF ; 
 int /*<<< orphan*/  LOOKUP ; 
 scalar_t__ MAXPATHLEN ; 
 int /*<<< orphan*/  MAXPHYS ; 
 int MAX_IPv4_STR_LEN ; 
 scalar_t__ MFSNAMELEN ; 
 int /*<<< orphan*/  MNT_ROOTFS ; 
 int MNT_VISFLAGMASK ; 
 int /*<<< orphan*/  MNT_WAIT ; 
 int /*<<< orphan*/  M_MOUNT ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NFS_ARGSVERSION_XDR ; 
 int /*<<< orphan*/  NFS_BITMAP_SET (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFS_BITMAP_ZERO (int*,int) ; 
 int NFS_MATTR_BITMAP_LEN ; 
 int /*<<< orphan*/  NFS_MATTR_FH ; 
 int /*<<< orphan*/  NFS_MATTR_FS_LOCATIONS ; 
 int /*<<< orphan*/  NFS_MATTR_MNTFLAGS ; 
 int /*<<< orphan*/  NFS_MATTR_NFS_PORT ; 
 int /*<<< orphan*/  NFS_MATTR_NFS_VERSION ; 
 int /*<<< orphan*/  NFS_MATTR_SOCKET_TYPE ; 
 int NFS_MFLAG_BITMAP_LEN ; 
 int /*<<< orphan*/  NFS_MFLAG_RESVPORT ; 
 int NFS_XDRARGS_VERSION_0 ; 
 void* NULLVP ; 
 int /*<<< orphan*/  OP_LOOKUP ; 
 scalar_t__ SOCK_DGRAM ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 scalar_t__ VDIR ; 
 scalar_t__ VFS_ROOT (TYPE_25__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int VNOP_FSYNC (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XB_CLEANUP ; 
 int XDRWORD ; 
 TYPE_5__* _MALLOC_ZONE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int buf_invalidateblks (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  copystr (char const*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_4__* current_proc () ; 
 char* inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 int /*<<< orphan*/  kauth_cred_getuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_mount_label_associate (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  mac_mount_label_destroy (TYPE_5__*) ; 
 int /*<<< orphan*/  mac_mount_label_init (TYPE_5__*) ; 
 int /*<<< orphan*/  mount_list_lock () ; 
 int /*<<< orphan*/  mount_list_unlock () ; 
 int /*<<< orphan*/  mount_lock_destroy (TYPE_5__*) ; 
 int /*<<< orphan*/  mount_lock_init (TYPE_5__*) ; 
 TYPE_15__ mountlist ; 
 int mountnfs (char*,TYPE_5__*,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int namei (struct nameidata*) ; 
 int /*<<< orphan*/  nameidone (struct nameidata*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rootvnode ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vfs_busy (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_unbusy (TYPE_5__*) ; 
 struct vfstable* vfsconf ; 
 int /*<<< orphan*/ * vnode_mountedhere (TYPE_3__*) ; 
 int /*<<< orphan*/  vnode_put (TYPE_3__*) ; 
 int vnode_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_rele (int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_vtype (TYPE_3__*) ; 
 int /*<<< orphan*/  xb_add_32 (int,struct xdrbuf*,int) ; 
 int /*<<< orphan*/  xb_add_bitmap (int,struct xdrbuf*,int*,int) ; 
 int /*<<< orphan*/  xb_add_fh (int,struct xdrbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xb_add_string (int,struct xdrbuf*,char*,int) ; 
 char* xb_buffer_base (struct xdrbuf*) ; 
 int /*<<< orphan*/  xb_build_done (int,struct xdrbuf*) ; 
 int /*<<< orphan*/  xb_cleanup (struct xdrbuf*) ; 
 int /*<<< orphan*/  xb_init (struct xdrbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xb_init_buffer (struct xdrbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xb_offset (struct xdrbuf*) ; 
 int xb_seek (struct xdrbuf*,int) ; 

__attribute__((used)) static int
nfs_mount_diskless_private(
	struct nfs_dlmount *ndmntp,
	const char *mntname,
	int mntflag,
	vnode_t *vpp,
	mount_t *mpp,
	vfs_context_t ctx)
{
	mount_t mp;
	int error, numcomps;
	proc_t procp;
	struct vfstable *vfsp;
	struct nameidata nd;
	vnode_t vp;
	char *xdrbuf = NULL, *p, *cp, *frompath, *endserverp;
	char uaddr[MAX_IPv4_STR_LEN];
	struct xdrbuf xb;
	uint32_t mattrs[NFS_MATTR_BITMAP_LEN];
	uint32_t mflags_mask[NFS_MFLAG_BITMAP_LEN], mflags[NFS_MFLAG_BITMAP_LEN];
	uint32_t argslength_offset, attrslength_offset, end_offset;

	procp = current_proc(); /* XXX */
	xb_init(&xb, 0);

	{
	/*
	 * mimic main()!. Temporarily set up rootvnode and other stuff so
	 * that namei works. Need to undo this because main() does it, too
	 */
		struct filedesc *fdp;	/* pointer to file descriptor state */
		fdp = procp->p_fd;
		mountlist.tqh_first->mnt_flag |= MNT_ROOTFS;

		/* Get the vnode for '/'. Set fdp->fd_cdir to reference it. */
		if (VFS_ROOT(mountlist.tqh_first, &rootvnode, NULL))
			panic("cannot find root vnode");
		error = vnode_ref(rootvnode);
		if (error) {
			printf("nfs_mountroot: vnode_ref() failed on root vnode!\n");
			goto out;
		}
		fdp->fd_cdir = rootvnode;
		fdp->fd_rdir = NULL;
	}

	/*
	 * Get vnode to be covered
	 */
	NDINIT(&nd, LOOKUP, OP_LOOKUP, FOLLOW | LOCKLEAF, UIO_SYSSPACE,
	    CAST_USER_ADDR_T(mntname), ctx);
	if ((error = namei(&nd))) {
		printf("nfs_mountroot: private namei failed!\n");
		goto out;
	}
	{
		/* undo vnode_ref() in mimic main()! */
		vnode_rele(rootvnode);
	}
	nameidone(&nd);
	vp = nd.ni_vp;

	if ((error = VNOP_FSYNC(vp, MNT_WAIT, ctx)) ||
	    (error = buf_invalidateblks(vp, BUF_WRITE_DATA, 0, 0))) {
		vnode_put(vp);
		goto out;
	}
	if (vnode_vtype(vp) != VDIR) {
		vnode_put(vp);
		error = ENOTDIR;
		goto out;
	}
	for (vfsp = vfsconf; vfsp; vfsp = vfsp->vfc_next)
		if (!strncmp(vfsp->vfc_name, "nfs", sizeof(vfsp->vfc_name)))
			break;
	if (vfsp == NULL) {
		printf("nfs_mountroot: private NFS not configured\n");
		vnode_put(vp);
		error = ENODEV;
		goto out;
	}
	if (vnode_mountedhere(vp) != NULL) {
		vnode_put(vp);
		error = EBUSY;
		goto out;
	}

	/*
	 * Allocate and initialize the filesystem.
	 */
	mp = _MALLOC_ZONE((u_int32_t)sizeof(struct mount), M_MOUNT, M_WAITOK);
	if (!mp) {
		printf("nfs_mountroot: unable to allocate mount structure\n");
		vnode_put(vp);
		error = ENOMEM;
		goto out;
	}
	bzero((char *)mp, sizeof(struct mount));

	/* Initialize the default IO constraints */
	mp->mnt_maxreadcnt = mp->mnt_maxwritecnt = MAXPHYS;
	mp->mnt_segreadcnt = mp->mnt_segwritecnt = 32;
	mp->mnt_ioflags = 0;
	mp->mnt_realrootvp = NULLVP;
	mp->mnt_authcache_ttl = 0; /* Allways go to our lookup */

	mount_lock_init(mp);
	TAILQ_INIT(&mp->mnt_vnodelist);
	TAILQ_INIT(&mp->mnt_workerqueue);
	TAILQ_INIT(&mp->mnt_newvnodes);
	(void)vfs_busy(mp, LK_NOWAIT);
	TAILQ_INIT(&mp->mnt_vnodelist);
	mount_list_lock();
	vfsp->vfc_refcount++;
	mount_list_unlock();
	mp->mnt_vtable = vfsp;
	mp->mnt_op = vfsp->vfc_vfsops;
	// mp->mnt_stat.f_type = vfsp->vfc_typenum;
	mp->mnt_flag = mntflag;
	mp->mnt_flag |= vfsp->vfc_flags & MNT_VISFLAGMASK;
	strncpy(mp->mnt_vfsstat.f_fstypename, vfsp->vfc_name, MFSNAMELEN-1);
	vp->v_mountedhere = mp;
	mp->mnt_vnodecovered = vp;
	vp = NULLVP;
	mp->mnt_vfsstat.f_owner = kauth_cred_getuid(kauth_cred_get());
	(void) copystr(mntname, mp->mnt_vfsstat.f_mntonname, MAXPATHLEN - 1, 0);
	(void) copystr(ndmntp->ndm_mntfrom, mp->mnt_vfsstat.f_mntfromname, MAXPATHLEN - 1, 0);
#if CONFIG_MACF
	mac_mount_label_init(mp);
	mac_mount_label_associate(ctx, mp);
#endif

	/* find the server-side path being mounted */
	frompath = ndmntp->ndm_mntfrom;
	if (*frompath == '[') {  /* skip IPv6 literal address */
		while (*frompath && (*frompath != ']'))
			frompath++;
		if (*frompath == ']')
			frompath++;
	}
	while (*frompath && (*frompath != ':'))
		frompath++;
	endserverp = frompath;
	while (*frompath && (*frompath == ':'))
		frompath++;
	/* count fs location path components */
	p = frompath;
	while (*p && (*p == '/'))
		p++;
	numcomps = 0;
	while (*p) {
		numcomps++;
		while (*p && (*p != '/'))
			p++;
		while (*p && (*p == '/'))
			p++;
	}

	/* convert address to universal address string */
	if (inet_ntop(AF_INET, &ndmntp->ndm_saddr.sin_addr, uaddr, sizeof(uaddr)) != uaddr) {
		printf("nfs_mountroot: bad address\n");
		error = EINVAL;
		goto out;
	}

	/* prepare mount attributes */
	NFS_BITMAP_ZERO(mattrs, NFS_MATTR_BITMAP_LEN);
	NFS_BITMAP_SET(mattrs, NFS_MATTR_NFS_VERSION);
	NFS_BITMAP_SET(mattrs, NFS_MATTR_SOCKET_TYPE);
	NFS_BITMAP_SET(mattrs, NFS_MATTR_NFS_PORT);
	NFS_BITMAP_SET(mattrs, NFS_MATTR_FH);
	NFS_BITMAP_SET(mattrs, NFS_MATTR_FS_LOCATIONS);
	NFS_BITMAP_SET(mattrs, NFS_MATTR_MNTFLAGS);

	/* prepare mount flags */
	NFS_BITMAP_ZERO(mflags_mask, NFS_MFLAG_BITMAP_LEN);
	NFS_BITMAP_ZERO(mflags, NFS_MFLAG_BITMAP_LEN);
	NFS_BITMAP_SET(mflags_mask, NFS_MFLAG_RESVPORT);
	NFS_BITMAP_SET(mflags, NFS_MFLAG_RESVPORT);

	/* build xdr buffer */
	xb_init_buffer(&xb, NULL, 0);
	xb_add_32(error, &xb, NFS_ARGSVERSION_XDR);
	argslength_offset = xb_offset(&xb);
	xb_add_32(error, &xb, 0); // args length
	xb_add_32(error, &xb, NFS_XDRARGS_VERSION_0);
	xb_add_bitmap(error, &xb, mattrs, NFS_MATTR_BITMAP_LEN);
	attrslength_offset = xb_offset(&xb);
	xb_add_32(error, &xb, 0); // attrs length
	xb_add_32(error, &xb, ndmntp->ndm_nfsv3 ? 3 : 2); // NFS version
	xb_add_string(error, &xb, ((ndmntp->ndm_sotype == SOCK_DGRAM) ? "udp" : "tcp"), 3);
	xb_add_32(error, &xb, ntohs(ndmntp->ndm_saddr.sin_port)); // NFS port
	xb_add_fh(error, &xb, &ndmntp->ndm_fh[0], ndmntp->ndm_fhlen);
	/* fs location */
	xb_add_32(error, &xb, 1); /* fs location count */
	xb_add_32(error, &xb, 1); /* server count */
	xb_add_string(error, &xb, ndmntp->ndm_mntfrom, (endserverp - ndmntp->ndm_mntfrom)); /* server name */
	xb_add_32(error, &xb, 1); /* address count */
	xb_add_string(error, &xb, uaddr, strlen(uaddr)); /* address */
	xb_add_32(error, &xb, 0); /* empty server info */
	xb_add_32(error, &xb, numcomps); /* pathname component count */
	p = frompath;
	while (*p && (*p == '/'))
		p++;
	while (*p) {
		cp = p;
		while (*p && (*p != '/'))
			p++;
		xb_add_string(error, &xb, cp, (p - cp)); /* component */
		if (error)
			break;
		while (*p && (*p == '/'))
			p++;
	}
	xb_add_32(error, &xb, 0); /* empty fsl info */
	xb_add_32(error, &xb, mntflag); /* MNT flags */
	xb_build_done(error, &xb);

	/* update opaque counts */
	end_offset = xb_offset(&xb);
	if (!error) {
		error = xb_seek(&xb, argslength_offset);
		xb_add_32(error, &xb, end_offset - argslength_offset + XDRWORD/*version*/);
	}
	if (!error) {
		error = xb_seek(&xb, attrslength_offset);
		xb_add_32(error, &xb, end_offset - attrslength_offset - XDRWORD/*don't include length field*/);
	}
	if (error) {
		printf("nfs_mountroot: error %d assembling mount args\n", error);
		goto out;
	}
	/* grab the assembled buffer */
	xdrbuf = xb_buffer_base(&xb);
	xb.xb_flags &= ~XB_CLEANUP;

	/* do the mount */
	if ((error = mountnfs(xdrbuf, mp, ctx, &vp))) {
		printf("nfs_mountroot: mount %s failed: %d\n", mntname, error);
		vnode_put(mp->mnt_vnodecovered);
		mount_list_lock();
		vfsp->vfc_refcount--;
		mount_list_unlock();
		vfs_unbusy(mp);
		mount_lock_destroy(mp);
#if CONFIG_MACF
		mac_mount_label_destroy(mp);
#endif
		FREE_ZONE(mp, sizeof (struct mount), M_MOUNT);
		goto out;
	}

	*mpp = mp;
	*vpp = vp;
out:
	xb_cleanup(&xb);
	return (error);
}