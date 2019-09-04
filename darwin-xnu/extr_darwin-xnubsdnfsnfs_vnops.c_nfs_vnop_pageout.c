#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vnode_t ;
typedef  size_t vm_offset_t ;
typedef  scalar_t__ upl_t ;
typedef  int /*<<< orphan*/  uio_t ;
typedef  int /*<<< orphan*/  uio_buf ;
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  size_t u_quad_t ;
typedef  int /*<<< orphan*/  thread_t ;
struct vnop_pageout_args {scalar_t__ a_pl; size_t a_size; size_t a_f_offset; size_t a_pl_offset; int a_flags; int /*<<< orphan*/  a_context; int /*<<< orphan*/  a_vp; } ;
struct nfsreq {int dummy; } ;
struct nfsmount {size_t nm_biosize; size_t nm_wsize; scalar_t__ nm_vers; scalar_t__ nm_stategenid; int /*<<< orphan*/  nm_state; TYPE_1__* nm_funcs; int /*<<< orphan*/  nm_lock; } ;
struct nfsbuf {scalar_t__ nb_dirtyend; size_t nb_dirtyoff; int /*<<< orphan*/  nb_flags; int /*<<< orphan*/  nb_lflags; } ;
typedef  int /*<<< orphan*/  req ;
typedef  size_t off_t ;
typedef  TYPE_2__* nfsnode_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
typedef  scalar_t__ daddr64_t ;
typedef  struct nfsreq** caddr_t ;
struct TYPE_18__ {int /*<<< orphan*/  pageouts; } ;
struct TYPE_17__ {size_t n_size; int n_flag; int n_error; int /*<<< orphan*/  n_numoutput; int /*<<< orphan*/  n_needcommitcnt; } ;
struct TYPE_16__ {int (* nf_write_rpc_async ) (TYPE_2__*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,struct nfsreq**) ;int (* nf_write_rpc_async_finish ) (TYPE_2__*,struct nfsreq*,int*,size_t*,int*) ;int (* nf_commit_rpc ) (TYPE_2__*,size_t,size_t,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_USER_ADDR_T (size_t) ; 
 int /*<<< orphan*/  CHECK_NEEDCOMMITCNT (TYPE_2__*) ; 
 int /*<<< orphan*/  CLR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  DUMP 131 
#define  DUMPANDLOG 130 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int ENXIO ; 
 int ERESTART ; 
 int /*<<< orphan*/  FSDBG (int,...) ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_VALID_CRED (int /*<<< orphan*/ ) ; 
 scalar_t__ KERN_SUCCESS ; 
 int MAXPAGINGREQS ; 
 size_t MIN (size_t,size_t) ; 
 int /*<<< orphan*/  NBAC_NOWAIT ; 
 size_t NBOFF (struct nfsbuf*) ; 
 int /*<<< orphan*/  NB_INVAL ; 
 int /*<<< orphan*/  NB_NEEDCOMMIT ; 
 int NFSERR_GRACE ; 
 int NFSERR_STALEWRITEVERF ; 
 int /*<<< orphan*/  NFS_DATA_LOCK_SHARED ; 
 int NFS_ELAST ; 
 scalar_t__ NFS_VER4 ; 
 int NFS_WRITE_FILESYNC ; 
 int NFS_WRITE_UNSTABLE ; 
 int /*<<< orphan*/  NP (TYPE_2__*,char*,...) ; 
 int NREVOKE ; 
 int NWRITEERR ; 
 int /*<<< orphan*/  OSAddAtomic64 (int,int /*<<< orphan*/ *) ; 
 size_t PAGE_MASK_64 ; 
 scalar_t__ PZERO ; 
#define  RETRY 129 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  SEVER 128 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct nfsbuf*,int /*<<< orphan*/ ) ; 
 int UIO_SIZEOF (int) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 int UPL_ABORT_DUMP_PAGES ; 
 int UPL_ABORT_FREE_ON_EMPTY ; 
 int UPL_COMMIT_CLEAR_DIRTY ; 
 int UPL_COMMIT_FREE_ON_EMPTY ; 
 int UPL_NOCOMMIT ; 
 TYPE_2__* VTONFS (int /*<<< orphan*/ ) ; 
 struct nfsmount* VTONMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct nfsreq**,int) ; 
 int* errorcount ; 
 int hz ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 size_t max (size_t,size_t) ; 
 size_t min (size_t,size_t) ; 
 int /*<<< orphan*/  nb_free ; 
 scalar_t__ nfs_buf_acquire (struct nfsbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_buf_delwri_push (int) ; 
 int /*<<< orphan*/  nfs_buf_drop (struct nfsbuf*) ; 
 struct nfsbuf* nfs_buf_incore (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/ * nfs_buf_mutex ; 
 int /*<<< orphan*/  nfs_buf_release (struct nfsbuf*,int) ; 
 int /*<<< orphan*/  nfs_buf_remfree (struct nfsbuf*) ; 
 int /*<<< orphan*/  nfs_data_lock_noupdate (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_data_unlock_noupdate (TYPE_2__*) ; 
 scalar_t__ nfs_mount_state_error_should_restart (int) ; 
 scalar_t__ nfs_mount_state_max_restarts (struct nfsmount*) ; 
 int nfs_mount_state_wait_for_recovery (struct nfsmount*) ; 
 int /*<<< orphan*/  nfs_need_recover (struct nfsmount*,int) ; 
 int /*<<< orphan*/  nfs_node_lock_force (TYPE_2__*) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_2__*) ; 
 char nfs_pageouterrorhandler (int) ; 
 int /*<<< orphan*/  nfs_request_async_cancel (struct nfsreq*) ; 
 int nfs_write_rpc2 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  nfsbufdelwri ; 
 int /*<<< orphan*/  nfsbufdelwricnt ; 
 TYPE_6__ nfsstats ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int /*<<< orphan*/  printf (char*,size_t) ; 
 size_t round_page_64 (size_t) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,struct nfsreq**) ; 
 int stub2 (TYPE_2__*,struct nfsreq*,int*,size_t*,int*) ; 
 int stub3 (TYPE_2__*,size_t,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tsleep (int /*<<< orphan*/ *,scalar_t__,char*,int) ; 
 int /*<<< orphan*/  ubc_getcred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubc_upl_abort (scalar_t__,int) ; 
 int /*<<< orphan*/  ubc_upl_abort_range (scalar_t__,size_t,size_t,int) ; 
 int /*<<< orphan*/  ubc_upl_commit_range (scalar_t__,size_t,size_t,int) ; 
 scalar_t__ ubc_upl_map (scalar_t__,size_t*) ; 
 int /*<<< orphan*/  ubc_upl_unmap (scalar_t__) ; 
 int /*<<< orphan*/  uio_addiov (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  uio_createwithbuffer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**,int) ; 
 size_t uio_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uio_reset (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_startwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_writedone (int /*<<< orphan*/ ) ; 

int
nfs_vnop_pageout(
	struct vnop_pageout_args /* {
		struct vnodeop_desc *a_desc;
		vnode_t a_vp;
		upl_t a_pl;
		vm_offset_t a_pl_offset;
		off_t a_f_offset;
		size_t a_size;
		int a_flags;
		vfs_context_t a_context;
	} */ *ap)
{
	vnode_t vp = ap->a_vp;
	upl_t pl = ap->a_pl;
	size_t size = ap->a_size;
	off_t f_offset = ap->a_f_offset;
	vm_offset_t pl_offset = ap->a_pl_offset;
	int flags = ap->a_flags;
	nfsnode_t np = VTONFS(vp);
	thread_t thd;
	kauth_cred_t cred;
	struct nfsbuf *bp;
	struct nfsmount *nmp = VTONMP(vp);
	daddr64_t lbn;
	int error = 0, iomode;
	off_t off, txoffset, rxoffset;
	vm_offset_t ioaddr, txaddr, rxaddr;
	uio_t auio;
	char uio_buf [ UIO_SIZEOF(1) ];
	int nofreeupl = flags & UPL_NOCOMMIT;
	size_t nmwsize, biosize, iosize, pgsize, txsize, rxsize, xsize, remsize;
	struct nfsreq *req[MAXPAGINGREQS];
	int nextsend, nextwait, wverfset, commit;
	uint64_t wverf, wverf2;
	uint32_t stategenid = 0, vrestart = 0, restart = 0, vrestarts = 0, restarts = 0;
	kern_return_t kret;

	FSDBG(323, f_offset, size, pl, pl_offset);

	if (pl == (upl_t)NULL)
		panic("nfs_pageout: no upl");

	if (size <= 0) {
		printf("nfs_pageout: invalid size %ld", size);
		if (!nofreeupl)
			ubc_upl_abort_range(pl, pl_offset, size, 0);
		return (EINVAL);
	}

	if (!nmp) {
		if (!nofreeupl)
			ubc_upl_abort(pl, UPL_ABORT_DUMP_PAGES|UPL_ABORT_FREE_ON_EMPTY);
		return (ENXIO);
	}
	biosize = nmp->nm_biosize;
	nmwsize = nmp->nm_wsize;

	nfs_data_lock_noupdate(np, NFS_DATA_LOCK_SHARED);

	/*
	 * Check to see whether the buffer is incore.
	 * If incore and not busy, invalidate it from the cache.
	 */
	for (iosize = 0; iosize < size; iosize += xsize) {
		off = f_offset + iosize;
		/* need make sure we do things on block boundaries */
		xsize = biosize - (off % biosize);
		if (off + xsize > f_offset + size)
			xsize = f_offset + size - off;
		lbn = (daddr64_t)(off / biosize);
		lck_mtx_lock(nfs_buf_mutex);
		if ((bp = nfs_buf_incore(np, lbn))) {
			FSDBG(323, off, bp, bp->nb_lflags, bp->nb_flags);
			if (nfs_buf_acquire(bp, NBAC_NOWAIT, 0, 0)) {
				lck_mtx_unlock(nfs_buf_mutex);
				nfs_data_unlock_noupdate(np);
				/* no panic. just tell vm we are busy */
				if (!nofreeupl)
					ubc_upl_abort_range(pl, pl_offset, size, 0);
				return (EBUSY);
			}
			if (bp->nb_dirtyend > 0) {
				/*
				 * if there's a dirty range in the buffer, check
				 * to see if it extends beyond the pageout region
				 *
				 * if the dirty region lies completely within the
				 * pageout region, we just invalidate the buffer
				 * because it's all being written out now anyway.
				 *
				 * if any of the dirty region lies outside the
				 * pageout region, we'll try to clip the dirty
				 * region to eliminate the portion that's being
				 * paged out.  If that's not possible, because
				 * the dirty region extends before and after the
				 * pageout region, then we'll just return EBUSY.
				 */
				off_t boff, start, end;
				boff = NBOFF(bp);
				start = off;
				end = off + xsize;
				/* clip end to EOF */
				if (end > (off_t)np->n_size)
					end = np->n_size;
				start -= boff;
				end -= boff;
				if ((bp->nb_dirtyoff < start) &&
				    (bp->nb_dirtyend > end)) {
				    /*
				     * not gonna be able to clip the dirty region
				     *
				     * But before returning the bad news, move the
				     * buffer to the start of the delwri list and
				     * give the list a push to try to flush the
				     * buffer out.
				     */
				    FSDBG(323, np, bp, 0xd00deebc, EBUSY);
				    nfs_buf_remfree(bp);
				    TAILQ_INSERT_HEAD(&nfsbufdelwri, bp, nb_free);
				    nfsbufdelwricnt++;
				    nfs_buf_drop(bp);
				    nfs_buf_delwri_push(1);
				    lck_mtx_unlock(nfs_buf_mutex);
				    nfs_data_unlock_noupdate(np);
				    if (!nofreeupl)
					    ubc_upl_abort_range(pl, pl_offset, size, 0);
				    return (EBUSY);
				}
				if ((bp->nb_dirtyoff < start) ||
				    (bp->nb_dirtyend > end)) {
				    /* clip dirty region, if necessary */
				    if (bp->nb_dirtyoff < start)
					bp->nb_dirtyend = min(bp->nb_dirtyend, start);
				    if (bp->nb_dirtyend > end)
					bp->nb_dirtyoff = max(bp->nb_dirtyoff, end);
				    FSDBG(323, bp, bp->nb_dirtyoff, bp->nb_dirtyend, 0xd00dee00);
				    /* we're leaving this block dirty */
				    nfs_buf_drop(bp);
				    lck_mtx_unlock(nfs_buf_mutex);
				    continue;
				}
			}
			nfs_buf_remfree(bp);
			lck_mtx_unlock(nfs_buf_mutex);
			SET(bp->nb_flags, NB_INVAL);
			nfs_node_lock_force(np);
			if (ISSET(bp->nb_flags, NB_NEEDCOMMIT)) {
				CLR(bp->nb_flags, NB_NEEDCOMMIT);
				np->n_needcommitcnt--;
				CHECK_NEEDCOMMITCNT(np);
			}
			nfs_node_unlock(np);
			nfs_buf_release(bp, 1);
		} else {
			lck_mtx_unlock(nfs_buf_mutex);
		}
	}

	thd = vfs_context_thread(ap->a_context);
	cred = ubc_getcred(vp);
	if (!IS_VALID_CRED(cred))
		cred = vfs_context_ucred(ap->a_context);

	nfs_node_lock_force(np);
	if (np->n_flag & NWRITEERR) {
		error = np->n_error;
		nfs_node_unlock(np);
		nfs_data_unlock_noupdate(np);
		if (!nofreeupl)
			ubc_upl_abort_range(pl, pl_offset, size,
					    UPL_ABORT_FREE_ON_EMPTY);
		return (error);
	}
	nfs_node_unlock(np);

	if (f_offset < 0 || f_offset >= (off_t)np->n_size ||
	    f_offset & PAGE_MASK_64 || size & PAGE_MASK_64) {
		nfs_data_unlock_noupdate(np);
		if (!nofreeupl)
			ubc_upl_abort_range(pl, pl_offset, size,
					    UPL_ABORT_FREE_ON_EMPTY);
		return (EINVAL);
	}

	kret = ubc_upl_map(pl, &ioaddr);
	if (kret != KERN_SUCCESS)
		panic("nfs_vnop_pageout: ubc_upl_map() failed with (%d)", kret);
	ioaddr += pl_offset;

	if ((u_quad_t)f_offset + size > np->n_size)
		xsize = np->n_size - f_offset;
	else
		xsize = size;

	pgsize = round_page_64(xsize);
	if ((size > pgsize) && !nofreeupl)
		ubc_upl_abort_range(pl, pl_offset + pgsize, size - pgsize,
				    UPL_ABORT_FREE_ON_EMPTY);

	/*
	 * check for partial page and clear the
	 * contents past end of the file before
	 * releasing it in the VM page cache
	 */
	if ((u_quad_t)f_offset < np->n_size && (u_quad_t)f_offset + size > np->n_size) {
		size_t io = np->n_size - f_offset;
		bzero((caddr_t)(ioaddr + io), size - io);
		FSDBG(321, np->n_size, f_offset, f_offset + io, size - io);
	}
	nfs_data_unlock_noupdate(np);

	auio = uio_createwithbuffer(1, 0, UIO_SYSSPACE, UIO_WRITE,
		&uio_buf, sizeof(uio_buf));

tryagain:
	if (nmp->nm_vers >= NFS_VER4)
		stategenid = nmp->nm_stategenid;
	wverf = wverf2 = wverfset = 0;
	txsize = rxsize = xsize;
	txoffset = rxoffset = f_offset;
	txaddr = rxaddr = ioaddr;
	commit = NFS_WRITE_FILESYNC;

	bzero(req, sizeof(req));
	nextsend = nextwait = 0;
	do {
		if (np->n_flag & NREVOKE) {
			error = EIO;
			break;
		}
		/* send requests while we need to and have available slots */
		while ((txsize > 0) && (req[nextsend] == NULL)) {
			iosize = MIN(nmwsize, txsize);
			uio_reset(auio, txoffset, UIO_SYSSPACE, UIO_WRITE);
			uio_addiov(auio, CAST_USER_ADDR_T(txaddr), iosize);
			FSDBG(323, uio_offset(auio), iosize, txaddr, txsize);
			OSAddAtomic64(1, &nfsstats.pageouts);
			nfs_node_lock_force(np);
			np->n_numoutput++;
			nfs_node_unlock(np);
			vnode_startwrite(vp);
			iomode = NFS_WRITE_UNSTABLE;
			if ((error = nmp->nm_funcs->nf_write_rpc_async(np, auio, iosize, thd, cred, iomode, NULL, &req[nextsend]))) {
				req[nextsend] = NULL;
				vnode_writedone(vp);
				nfs_node_lock_force(np);
				np->n_numoutput--;
				nfs_node_unlock(np);
				break;
			}
			txaddr += iosize;
			txoffset += iosize;
			txsize -= iosize;
			nextsend = (nextsend + 1) % MAXPAGINGREQS;
		}
		/* wait while we need to and break out if more requests to send */
		while ((rxsize > 0) && req[nextwait]) {
			iosize = remsize = MIN(nmwsize, rxsize);
			error = nmp->nm_funcs->nf_write_rpc_async_finish(np, req[nextwait], &iomode, &iosize, &wverf2);
			req[nextwait] = NULL;
			nextwait = (nextwait + 1) % MAXPAGINGREQS;
			vnode_writedone(vp);
			nfs_node_lock_force(np);
			np->n_numoutput--;
			nfs_node_unlock(np);
			if ((nmp->nm_vers >= NFS_VER4) && nfs_mount_state_error_should_restart(error)) {
				lck_mtx_lock(&nmp->nm_lock);
				if ((error != NFSERR_GRACE) && (stategenid == nmp->nm_stategenid)) {
					NP(np, "nfs_vnop_pageout: error %d, initiating recovery", error);
					nfs_need_recover(nmp, error);
				}
				lck_mtx_unlock(&nmp->nm_lock);
				restart = 1;
				goto cancel;
			}
			if (error) {
				FSDBG(323, rxoffset, rxsize, error, -1);
				break;
			}
			if (!wverfset) {
				wverf = wverf2;
				wverfset = 1;
			} else if (wverf != wverf2) {
				/* verifier changed, so we need to restart all the writes */
				vrestart = 1;
				goto cancel;
			}
			/* Retain the lowest commitment level returned. */
			if (iomode < commit)
				commit = iomode;
			rxaddr += iosize;	
			rxoffset += iosize;	
			rxsize -= iosize;
			remsize -= iosize;
			if (remsize > 0) {
				/* need to try sending the remainder */
				iosize = remsize;
				uio_reset(auio, rxoffset, UIO_SYSSPACE, UIO_WRITE);
				uio_addiov(auio, CAST_USER_ADDR_T(rxaddr), remsize);
				iomode = NFS_WRITE_UNSTABLE;
				error = nfs_write_rpc2(np, auio, thd, cred, &iomode, &wverf2);
				if ((nmp->nm_vers >= NFS_VER4) && nfs_mount_state_error_should_restart(error)) {
					NP(np, "nfs_vnop_pageout: restart: error %d", error);
					lck_mtx_lock(&nmp->nm_lock);
					if ((error != NFSERR_GRACE) && (stategenid == nmp->nm_stategenid)) {
						NP(np, "nfs_vnop_pageout: error %d, initiating recovery", error);
						nfs_need_recover(nmp, error);
					}
					lck_mtx_unlock(&nmp->nm_lock);
					restart = 1;
					goto cancel;
				}
				if (error) {
					FSDBG(323, rxoffset, rxsize, error, -1);
					break;
				}
				if (wverf != wverf2) {
					/* verifier changed, so we need to restart all the writes */
					vrestart = 1;
					goto cancel;
				}
				if (iomode < commit)
					commit = iomode;
				rxaddr += iosize;	
				rxoffset += iosize;	
				rxsize -= iosize;
			}
			if (txsize)
				break;
		}
	} while (!error && (txsize || rxsize));

	vrestart = 0;

	if (!error && (commit != NFS_WRITE_FILESYNC)) {
		error = nmp->nm_funcs->nf_commit_rpc(np, f_offset, xsize, cred, wverf);
		if (error == NFSERR_STALEWRITEVERF) {
			vrestart = 1;
			error = EIO;
		}
	}

	if (error) {
cancel:
		/* cancel any outstanding requests */
		while (req[nextwait]) {
			nfs_request_async_cancel(req[nextwait]);
			req[nextwait] = NULL;
			nextwait = (nextwait + 1) % MAXPAGINGREQS;
			vnode_writedone(vp);
			nfs_node_lock_force(np);
			np->n_numoutput--;
			nfs_node_unlock(np);
		}
		if (np->n_flag & NREVOKE) {
			error = EIO;
		} else {
			if (vrestart) {
				if (++vrestarts <= 100) /* guard against no progress */
					goto tryagain;
				NP(np, "nfs_pageout: too many restarts, aborting");
				FSDBG(323, f_offset, xsize, ERESTART, -1);
			}
			if (restart) {
				if (restarts <= nfs_mount_state_max_restarts(nmp)) { /* guard against no progress */
					if (error == NFSERR_GRACE)
						tsleep(&nmp->nm_state, (PZERO-1), "nfsgrace", 2*hz);
					if (!(error = nfs_mount_state_wait_for_recovery(nmp)))
						goto tryagain;
				} else {
					NP(np, "nfs_pageout: too many restarts, aborting");
					FSDBG(323, f_offset, xsize, ERESTART, -1);
				}
			}
		}
	}

	ubc_upl_unmap(pl);

	/*
	 * We've had several different solutions on what to do when the pageout
	 * gets an error. If we don't handle it, and return an error to the
	 * caller, vm, it will retry . This can end in endless looping
	 * between vm and here doing retries of the same page. Doing a dump
	 * back to vm, will get it out of vm's knowledge and we lose whatever
	 * data existed. This is risky, but in some cases necessary. For
	 * example, the initial fix here was to do that for ESTALE. In that case
	 * the server is telling us that the file is no longer the same. We
	 * would not want to keep paging out to that. We also saw some 151
	 * errors from Auspex server and NFSv3 can return errors higher than
	 * ELAST. Those along with NFS known server errors we will "dump" from
	 * vm.  Errors we don't expect to occur, we dump and log for further
	 * analysis. Errors that could be transient, networking ones,
	 * we let vm "retry". Lastly, errors that we retry, but may have potential
	 * to storm the network, we "retrywithsleep". "sever" will be used in
	 * in the future to dump all pages of object for cases like ESTALE.
	 * All this is the basis for the states returned and first guesses on
	 * error handling. Tweaking expected as more statistics are gathered.
	 * Note, in the long run we may need another more robust solution to
	 * have some kind of persistant store when the vm cannot dump nor keep
	 * retrying as a solution, but this would be a file architectural change
	 */
	if (!nofreeupl) { /* otherwise stacked file system has to handle this */
		if (error) {
			int abortflags = 0;
			char action = nfs_pageouterrorhandler(error);
			
			switch (action) {
				case DUMP:
					abortflags = UPL_ABORT_DUMP_PAGES|UPL_ABORT_FREE_ON_EMPTY;
					break;
				case DUMPANDLOG:
					abortflags = UPL_ABORT_DUMP_PAGES|UPL_ABORT_FREE_ON_EMPTY;
					if (error <= NFS_ELAST) {
						if ((errorcount[error] % 100) == 0)
							NP(np, "nfs_pageout: unexpected error %d. dumping vm page", error);
						errorcount[error]++;
					}
					break;
				case RETRY:
					abortflags = UPL_ABORT_FREE_ON_EMPTY;
					break;
				case SEVER: /* not implemented */
				default:
					NP(np, "nfs_pageout: action %d not expected", action);
					break;
			}

			ubc_upl_abort_range(pl, pl_offset, pgsize, abortflags);
			/* return error in all cases above */

		} else {
			ubc_upl_commit_range(pl, pl_offset, pgsize,
					     UPL_COMMIT_CLEAR_DIRTY |
					     UPL_COMMIT_FREE_ON_EMPTY);
		}
	}
	return (error);
}