#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  scalar_t__ u_quad_t ;
struct vnop_setattr_args {struct vnode_attr* a_vap; int /*<<< orphan*/ * a_vp; int /*<<< orphan*/  a_context; } ;
struct vnode_attr {scalar_t__ va_data_size; int va_vaflags; } ;
struct TYPE_4__ {int nfsa_flags; } ;
struct nfsmount {int nm_vers; int nm_biosize; TYPE_3__* nm_funcs; TYPE_1__ nm_fsattr; } ;
struct TYPE_5__ {scalar_t__ nva_size; } ;
struct nfsbuf {scalar_t__ n_size; int n_flag; int nb_flags; int nb_dirtyend; int nb_dirtyoff; int nb_dirty; int n_error; TYPE_2__ n_vattr; int /*<<< orphan*/  nb_wcred; } ;
struct nfs_open_owner {int dummy; } ;
struct nfs_open_file {int nof_flags; int nof_access; } ;
struct nfs_dulookup {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  struct nfsbuf* nfsnode_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
typedef  int daddr64_t ;
struct TYPE_6__ {int (* nf_setattr_rpc ) (struct nfsbuf*,struct vnode_attr*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CLR (int,int) ; 
 int EINTR ; 
 int EIO ; 
 int EISDIR ; 
 int ENOMEM ; 
 int ENXIO ; 
 int EROFS ; 
 int /*<<< orphan*/  FSDBG (int,struct nfsbuf*,int,int,int) ; 
 int /*<<< orphan*/  FSDBG_BOT (int,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  FSDBG_TOP (int,scalar_t__,scalar_t__,scalar_t__,int) ; 
 scalar_t__ ISSET (int,int) ; 
 int /*<<< orphan*/  IS_VALID_CRED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NACCESSINVALIDATE (struct nfsbuf*) ; 
 int /*<<< orphan*/  NATTRINVALIDATE (struct nfsbuf*) ; 
 int /*<<< orphan*/  NBLK_READ ; 
 int NBOFF (struct nfsbuf*) ; 
 int NB_ASYNC ; 
 int NB_DONE ; 
 int NB_ERROR ; 
 int NB_INVAL ; 
 int NB_NOCACHE ; 
 int NB_READ ; 
 int NB_STABLE ; 
 int /*<<< orphan*/  NFS_DATA_LOCK_EXCLUSIVE ; 
 int NFS_FSFLAG_NAMED_ATTR ; 
 int NFS_OPEN_FILE_LOST ; 
 int NFS_OPEN_FILE_REOPEN ; 
 int NFS_OPEN_FILE_SETATTR ; 
 int NFS_OPEN_SHARE_ACCESS_WRITE ; 
 int /*<<< orphan*/  NFS_OPEN_SHARE_DENY_NONE ; 
 int NFS_VER4 ; 
 int /*<<< orphan*/  NGA_UNCACHED ; 
 int NMODIFIED ; 
 int NNEEDINVALIDATE ; 
 int /*<<< orphan*/  NP (struct nfsbuf*,char*,int,...) ; 
 int NREVOKE ; 
 int NUPDATESIZE ; 
 int NWRITEERR ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  SET (int,int) ; 
 int /*<<< orphan*/  VATTR_CLEAR_ACTIVE (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 scalar_t__ VATTR_IS_ACTIVE (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int VA_UTIMES_NULL ; 
#define  VBLK 132 
#define  VCHR 131 
#define  VDIR 130 
#define  VFIFO 129 
 int VREG ; 
#define  VSOCK 128 
 struct nfsbuf* VTONFS (int /*<<< orphan*/ *) ; 
 struct nfsmount* VTONMP (int /*<<< orphan*/ *) ; 
 int V_IGNORE_WRITEERR ; 
 int V_SAVE ; 
 int /*<<< orphan*/  kauth_cred_ref (int /*<<< orphan*/ ) ; 
 int nfs4_open (struct nfsbuf*,struct nfs_open_file*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfs4_reopen (struct nfs_open_file*,int /*<<< orphan*/ ) ; 
 int nfs_buf_get (struct nfsbuf*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nfsbuf**) ; 
 int /*<<< orphan*/  nfs_buf_is_incore (struct nfsbuf*,int) ; 
 int /*<<< orphan*/  nfs_buf_release (struct nfsbuf*,int) ; 
 int nfs_buf_write (struct nfsbuf*) ; 
 int nfs_close (struct nfsbuf*,struct nfs_open_file*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_data_lock (struct nfsbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_data_unlock (struct nfsbuf*) ; 
 int /*<<< orphan*/  nfs_dulookup_finish (struct nfs_dulookup*,struct nfsbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_dulookup_init (struct nfs_dulookup*,struct nfsbuf*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_dulookup_start (struct nfs_dulookup*,struct nfsbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_getattr (struct nfsbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 scalar_t__ nfs_mount_state_error_should_restart (int) ; 
 scalar_t__ nfs_mount_state_in_use_end (struct nfsmount*,int) ; 
 int nfs_mount_state_in_use_start (struct nfsmount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_node_clear_busy (struct nfsbuf*) ; 
 int nfs_node_lock (struct nfsbuf*) ; 
 int /*<<< orphan*/  nfs_node_lock_force (struct nfsbuf*) ; 
 scalar_t__ nfs_node_set_busy (struct nfsbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_node_unlock (struct nfsbuf*) ; 
 int /*<<< orphan*/  nfs_open_file_clear_busy (struct nfs_open_file*) ; 
 int nfs_open_file_find (struct nfsbuf*,struct nfs_open_owner*,struct nfs_open_file**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int nfs_open_file_set_busy (struct nfs_open_file*,int /*<<< orphan*/ ) ; 
 struct nfs_open_owner* nfs_open_owner_find (struct nfsmount*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfs_open_owner_rele (struct nfs_open_owner*) ; 
 int nfs_vinvalbuf (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int round_page_32 (int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int stub1 (struct nfsbuf*,struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int stub2 (struct nfsbuf*,struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubc_setsize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va_access_time ; 
 int /*<<< orphan*/  va_acl ; 
 int /*<<< orphan*/  va_data_size ; 
 int /*<<< orphan*/  va_gid ; 
 int /*<<< orphan*/  va_guuid ; 
 int /*<<< orphan*/  va_mode ; 
 int /*<<< orphan*/  va_modify_time ; 
 int /*<<< orphan*/  va_uid ; 
 int /*<<< orphan*/  va_uuuid ; 
 int /*<<< orphan*/  vfs_context_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 
 char* vnode_getname (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vnode_getparent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnode_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnode_putname (char const*) ; 
 scalar_t__ vnode_vfsisrdonly (int /*<<< orphan*/ *) ; 
 int vnode_vtype (int /*<<< orphan*/ *) ; 

int
nfs_vnop_setattr(
	struct vnop_setattr_args /* {
		struct vnodeop_desc *a_desc;
		vnode_t a_vp;
		struct vnode_attr *a_vap;
		vfs_context_t a_context;
	} */ *ap)
{
	vfs_context_t ctx = ap->a_context;
	vnode_t vp = ap->a_vp;
	nfsnode_t np = VTONFS(vp);
	struct nfsmount *nmp;
	struct vnode_attr *vap = ap->a_vap;
	int error = 0;
	int biosize, nfsvers, namedattrs;
	u_quad_t origsize, vapsize;
	struct nfs_dulookup dul;
	nfsnode_t dnp = NULL;
	int dul_in_progress = 0;
	vnode_t dvp = NULL;
	const char *vname = NULL;
	struct nfs_open_owner *noop = NULL;
	struct nfs_open_file *nofp = NULL;

	nmp = VTONMP(vp);
	if (nfs_mount_gone(nmp))
		return (ENXIO);
	nfsvers = nmp->nm_vers;
	namedattrs = (nmp->nm_fsattr.nfsa_flags & NFS_FSFLAG_NAMED_ATTR);
	biosize = nmp->nm_biosize;

	/* Disallow write attempts if the filesystem is mounted read-only. */
	if (vnode_vfsisrdonly(vp))
		return (EROFS);

	origsize = np->n_size;
	if (VATTR_IS_ACTIVE(vap, va_data_size)) {
		switch (vnode_vtype(vp)) {
		case VDIR:
			return (EISDIR);
		case VCHR:
		case VBLK:
		case VSOCK:
		case VFIFO:
			if (!VATTR_IS_ACTIVE(vap, va_modify_time) &&
			    !VATTR_IS_ACTIVE(vap, va_access_time) &&
			    !VATTR_IS_ACTIVE(vap, va_mode) &&
			    !VATTR_IS_ACTIVE(vap, va_uid) &&
			    !VATTR_IS_ACTIVE(vap, va_gid)) {
				return (0);
			}
			VATTR_CLEAR_ACTIVE(vap, va_data_size);
			break;
		default:
			/*
			 * Disallow write attempts if the filesystem is
			 * mounted read-only.
			 */
			if (vnode_vfsisrdonly(vp))
				return (EROFS);
			FSDBG_TOP(512, np->n_size, vap->va_data_size,
				  np->n_vattr.nva_size, np->n_flag);
			/* clear NNEEDINVALIDATE, if set */
			if ((error = nfs_node_lock(np)))
				return (error);
			if (np->n_flag & NNEEDINVALIDATE)
				np->n_flag &= ~NNEEDINVALIDATE;
			nfs_node_unlock(np);
			/* flush everything */
			error = nfs_vinvalbuf(vp, (vap->va_data_size ? V_SAVE : 0) , ctx, 1);
			if (error) {
				NP(np, "nfs_setattr: nfs_vinvalbuf %d", error);
				FSDBG_BOT(512, np->n_size, vap->va_data_size, np->n_vattr.nva_size, -1);
				return (error);
			}
			if (nfsvers >= NFS_VER4) {
				/* setting file size requires having the file open for write access */
				if (np->n_flag & NREVOKE)
					return (EIO);
				noop = nfs_open_owner_find(nmp, vfs_context_ucred(ctx), 1);
				if (!noop)
					return (ENOMEM);
restart:
				error = nfs_mount_state_in_use_start(nmp, vfs_context_thread(ctx));
				if (error)
					return (error);
				if (np->n_flag & NREVOKE) {
					nfs_mount_state_in_use_end(nmp, 0);
					return (EIO);
				}
				error = nfs_open_file_find(np, noop, &nofp, 0, 0, 1);
				if (!error && (nofp->nof_flags & NFS_OPEN_FILE_LOST))
					error = EIO;
				if (!error && (nofp->nof_flags & NFS_OPEN_FILE_REOPEN)) {
					nfs_mount_state_in_use_end(nmp, 0);
					error = nfs4_reopen(nofp, vfs_context_thread(ctx));
					nofp = NULL;
					if (!error)
						goto restart;
				}
				if (!error)
					error = nfs_open_file_set_busy(nofp, vfs_context_thread(ctx));
				if (error) {
					nfs_open_owner_rele(noop);
					return (error);
				}
				if (!(nofp->nof_access & NFS_OPEN_SHARE_ACCESS_WRITE)) {
					/* we don't have the file open for write access, so open it */
					error = nfs4_open(np, nofp, NFS_OPEN_SHARE_ACCESS_WRITE, NFS_OPEN_SHARE_DENY_NONE, ctx);
					if (!error)
						nofp->nof_flags |= NFS_OPEN_FILE_SETATTR;
					if (nfs_mount_state_error_should_restart(error)) {
						nfs_open_file_clear_busy(nofp);
						nofp = NULL;
						if (nfs_mount_state_in_use_end(nmp, error))
							goto restart;
					}
				}
			}
			nfs_data_lock(np, NFS_DATA_LOCK_EXCLUSIVE);
			if (np->n_size > vap->va_data_size) { /* shrinking? */
				daddr64_t obn, bn;
				int neweofoff, mustwrite;
				struct nfsbuf *bp;

				obn = (np->n_size - 1) / biosize;
				bn = vap->va_data_size / biosize;
				for ( ; obn >= bn; obn--) {
					if (!nfs_buf_is_incore(np, obn))
						continue;
					error = nfs_buf_get(np, obn, biosize, NULL, NBLK_READ, &bp);
					if (error)
						continue;
					if (obn != bn) {
						FSDBG(512, bp, bp->nb_flags, 0, obn);
						SET(bp->nb_flags, NB_INVAL);
						nfs_buf_release(bp, 1);
						continue;
					}
					mustwrite = 0;
					neweofoff = vap->va_data_size - NBOFF(bp);
					/* check for any dirty data before the new EOF */
					if ((bp->nb_dirtyend > 0) && (bp->nb_dirtyoff < neweofoff)) {
						/* clip dirty range to EOF */
						if (bp->nb_dirtyend > neweofoff) {
							bp->nb_dirtyend = neweofoff;
							if (bp->nb_dirtyoff >= bp->nb_dirtyend)
								bp->nb_dirtyoff = bp->nb_dirtyend = 0;
						}
						if ((bp->nb_dirtyend > 0) && (bp->nb_dirtyoff < neweofoff))
							mustwrite++;
					}
					bp->nb_dirty &= (1 << round_page_32(neweofoff)/PAGE_SIZE) - 1;
					if (bp->nb_dirty)
						mustwrite++;
					if (!mustwrite) {
						FSDBG(512, bp, bp->nb_flags, 0, obn);
						SET(bp->nb_flags, NB_INVAL);
						nfs_buf_release(bp, 1);
						continue;
					}
					/* gotta write out dirty data before invalidating */
					/* (NB_STABLE indicates that data writes should be FILESYNC) */
					/* (NB_NOCACHE indicates buffer should be discarded) */
					CLR(bp->nb_flags, (NB_DONE | NB_ERROR | NB_INVAL | NB_ASYNC | NB_READ));
					SET(bp->nb_flags, NB_STABLE | NB_NOCACHE);
					if (!IS_VALID_CRED(bp->nb_wcred)) {
						kauth_cred_t cred = vfs_context_ucred(ctx);
						kauth_cred_ref(cred);
						bp->nb_wcred = cred;
					}
					error = nfs_buf_write(bp);
					// Note: bp has been released
					if (error) {
						FSDBG(512, bp, 0xd00dee, 0xbad, error);
						nfs_node_lock_force(np);
						np->n_error = error;
						np->n_flag |= NWRITEERR;
						/*
						 * There was a write error and we need to
						 * invalidate attrs and flush buffers in
						 * order to sync up with the server.
						 * (if this write was extending the file,
						 * we may no longer know the correct size)
						 */
						NATTRINVALIDATE(np);
						nfs_node_unlock(np);
						nfs_data_unlock(np);
						nfs_vinvalbuf(vp, V_SAVE|V_IGNORE_WRITEERR, ctx, 1);
						nfs_data_lock(np, NFS_DATA_LOCK_EXCLUSIVE);
						error = 0;
					}
				}
			}
			if (vap->va_data_size != np->n_size)
				ubc_setsize(vp, (off_t)vap->va_data_size); /* XXX error? */
			origsize = np->n_size;
			np->n_size = np->n_vattr.nva_size = vap->va_data_size;
			nfs_node_lock_force(np);
			CLR(np->n_flag, NUPDATESIZE);
			nfs_node_unlock(np);
			FSDBG(512, np, np->n_size, np->n_vattr.nva_size, 0xf00d0001);
		}
	} else if (VATTR_IS_ACTIVE(vap, va_modify_time) ||
		    VATTR_IS_ACTIVE(vap, va_access_time) ||
		    (vap->va_vaflags & VA_UTIMES_NULL)) {
		if ((error = nfs_node_lock(np)))
			return (error);
		if ((np->n_flag & NMODIFIED) && (vnode_vtype(vp) == VREG)) {
			nfs_node_unlock(np);
			error = nfs_vinvalbuf(vp, V_SAVE, ctx, 1);
			if (error == EINTR)
				return (error);
		} else {
			nfs_node_unlock(np);
		}
	}
	if ((VATTR_IS_ACTIVE(vap, va_mode) || VATTR_IS_ACTIVE(vap, va_uid) || VATTR_IS_ACTIVE(vap, va_gid) ||
	     VATTR_IS_ACTIVE(vap, va_acl) || VATTR_IS_ACTIVE(vap, va_uuuid) || VATTR_IS_ACTIVE(vap, va_guuid)) &&
	    !(error = nfs_node_lock(np))) {
		NACCESSINVALIDATE(np);
		nfs_node_unlock(np);
		if (!namedattrs) {
			dvp = vnode_getparent(vp);
			vname = vnode_getname(vp);
			dnp = (dvp && vname) ? VTONFS(dvp) : NULL;
			if (dnp) {
				if (nfs_node_set_busy(dnp, vfs_context_thread(ctx))) {
					vnode_put(dvp);
					vnode_putname(vname);
				} else {
					nfs_dulookup_init(&dul, dnp, vname, strlen(vname), ctx);
					nfs_dulookup_start(&dul, dnp, ctx);
					dul_in_progress = 1;
				}
			} else {
				if (dvp)
					vnode_put(dvp);
				if (vname)
					vnode_putname(vname);
			}
		}
	}

	if (!error)
		error = nmp->nm_funcs->nf_setattr_rpc(np, vap, ctx);

	if (dul_in_progress) {
		nfs_dulookup_finish(&dul, dnp, ctx);
		nfs_node_clear_busy(dnp);
		vnode_put(dvp);
		vnode_putname(vname);
	}

	FSDBG_BOT(512, np->n_size, vap->va_data_size, np->n_vattr.nva_size, error);
	if (VATTR_IS_ACTIVE(vap, va_data_size)) {
		if (error && (origsize != np->n_size) &&
		    ((nfsvers < NFS_VER4) || !nfs_mount_state_error_should_restart(error))) {
			/* make every effort to resync file size w/ server... */
			/* (don't bother if we'll be restarting the operation) */
			int err; /* preserve "error" for return */
			np->n_size = np->n_vattr.nva_size = origsize;
			nfs_node_lock_force(np);
			CLR(np->n_flag, NUPDATESIZE);
			nfs_node_unlock(np);
			FSDBG(512, np, np->n_size, np->n_vattr.nva_size, 0xf00d0002);
			ubc_setsize(vp, (off_t)np->n_size); /* XXX check error */
			vapsize = vap->va_data_size;
			vap->va_data_size = origsize;
			err = nmp->nm_funcs->nf_setattr_rpc(np, vap, ctx);
			if (err)
				NP(np, "nfs_vnop_setattr: nfs%d_setattr_rpc %d %d", nfsvers, error, err);
			vap->va_data_size = vapsize;
		}
		nfs_node_lock_force(np);
		/*
		 * The size was just set.  If the size is already marked for update, don't
		 * trust the newsize (it may have been set while the setattr was in progress).
		 * Clear the update flag and make sure we fetch new attributes so we are sure
		 * we have the latest size.
		 */
		if (ISSET(np->n_flag, NUPDATESIZE)) {
			CLR(np->n_flag, NUPDATESIZE);
			NATTRINVALIDATE(np);
			nfs_node_unlock(np);
			nfs_getattr(np, NULL, ctx, NGA_UNCACHED);
		} else {
			nfs_node_unlock(np);
		}
		nfs_data_unlock(np);
		if (nfsvers >= NFS_VER4) {
			if (nofp) {
				/* don't close our setattr open if we'll be restarting... */
				if (!nfs_mount_state_error_should_restart(error) &&
				    (nofp->nof_flags & NFS_OPEN_FILE_SETATTR)) {
					int err = nfs_close(np, nofp, NFS_OPEN_SHARE_ACCESS_WRITE, NFS_OPEN_SHARE_DENY_NONE, ctx);
					if (err)
						NP(np, "nfs_vnop_setattr: close error: %d", err);
					nofp->nof_flags &= ~NFS_OPEN_FILE_SETATTR;
				}
				nfs_open_file_clear_busy(nofp);
				nofp = NULL;
			}
			if (nfs_mount_state_in_use_end(nmp, error))
				goto restart;
			nfs_open_owner_rele(noop);
		}
	}
	return (error);
}