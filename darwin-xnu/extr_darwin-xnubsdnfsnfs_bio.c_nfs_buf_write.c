#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/ * thread_t ;
struct nfsmount {TYPE_4__* nm_funcs; } ;
struct TYPE_16__ {scalar_t__ le_next; } ;
struct nfsbuf {int nb_flags; int nb_lflags; int nb_error; scalar_t__ nb_dirtyoff; scalar_t__ nb_dirtyend; int nb_dirty; int nb_offio; int nb_endio; TYPE_1__ nb_vnbufs; scalar_t__ nb_bufsize; int /*<<< orphan*/  nb_verf; int /*<<< orphan*/  nb_wcred; int /*<<< orphan*/  nb_rcred; TYPE_6__* nb_np; } ;
typedef  TYPE_5__* proc_t ;
typedef  scalar_t__ off_t ;
typedef  TYPE_6__* nfsnode_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
struct TYPE_22__ {int /*<<< orphan*/  write_bios; } ;
struct TYPE_21__ {scalar_t__ n_size; int n_flag; int n_bflag; int /*<<< orphan*/  n_cleanblkhd; int /*<<< orphan*/  n_needcommitcnt; int /*<<< orphan*/  n_numoutput; } ;
struct TYPE_20__ {TYPE_3__* p_stats; } ;
struct TYPE_19__ {int (* nf_commit_rpc ) (TYPE_6__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_17__ {int /*<<< orphan*/  ru_oublock; } ;
struct TYPE_18__ {TYPE_2__ p_ru; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_NEEDCOMMITCNT (TYPE_6__*) ; 
 int /*<<< orphan*/  CLR (int,int) ; 
 int EIO ; 
 int /*<<< orphan*/  FSDBG_BOT (int,struct nfsbuf*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  FSDBG_TOP (int,struct nfsbuf*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int ISSET (int,int) ; 
 scalar_t__ IS_VALID_CRED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct nfsbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct nfsbuf*,int /*<<< orphan*/ ) ; 
 int NBFLUSHINPROG ; 
 int NBINVALINPROG ; 
 int NBL_BUSY ; 
 scalar_t__ NBOFF (struct nfsbuf*) ; 
 scalar_t__ NBPGDIRTY (struct nfsbuf*,int) ; 
 int NB_ASYNC ; 
 int NB_DELWRI ; 
 int NB_DONE ; 
 int NB_ERROR ; 
 int NB_META ; 
 int NB_NEEDCOMMIT ; 
 int NB_PAGELIST ; 
 int NB_READ ; 
 int NB_STABLE ; 
 int NB_WRITEINPROG ; 
 int /*<<< orphan*/  NFSBUFCNTCHK () ; 
 int NFSERR_STALEWRITEVERF ; 
 scalar_t__ NFSNOLIST ; 
 struct nfsmount* NFSTONMP (TYPE_6__*) ; 
 int /*<<< orphan*/  NFSTOV (TYPE_6__*) ; 
 int /*<<< orphan*/  NFS_BUF_MAP (struct nfsbuf*) ; 
 int NFS_WRITE_FILESYNC ; 
 int NFS_WRITE_UNSTABLE ; 
 int NNEEDINVALIDATE ; 
 int /*<<< orphan*/  OSAddAtomic64 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSIncrementAtomicLong (int /*<<< orphan*/ *) ; 
 int PAGE_MASK ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  SET (int,int) ; 
 scalar_t__ UBCINFOEXISTS (int /*<<< orphan*/ ) ; 
 int V_IGNORE_WRITEERR ; 
 int V_SAVE ; 
 TYPE_5__* current_proc () ; 
 int /*<<< orphan*/ * current_thread () ; 
 int /*<<< orphan*/  kauth_cred_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nb_vnbufs ; 
 int /*<<< orphan*/  nfs_buf_check_write_verifier (TYPE_6__*,struct nfsbuf*) ; 
 int /*<<< orphan*/  nfs_buf_iodone (struct nfsbuf*) ; 
 int nfs_buf_iowait (struct nfsbuf*) ; 
 int /*<<< orphan*/  nfs_buf_mutex ; 
 int /*<<< orphan*/  nfs_buf_release (struct nfsbuf*,int) ; 
 int /*<<< orphan*/  nfs_buf_upl_check (struct nfsbuf*) ; 
 int nfs_buf_upl_setup (struct nfsbuf*) ; 
 int nfs_buf_write_dirty_pages (struct nfsbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nfs_buf_write_rpc (struct nfsbuf*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 int /*<<< orphan*/  nfs_nbdwrite ; 
 int /*<<< orphan*/  nfs_node_lock_force (TYPE_6__*) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_6__*) ; 
 int /*<<< orphan*/  nfs_vinvalbuf2 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_8__ nfsstats ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int round_page_32 (int) ; 
 int stub1 (TYPE_6__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int trunc_page_32 (int) ; 
 int /*<<< orphan*/  vnode_startwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

int
nfs_buf_write(struct nfsbuf *bp)
{
	int error = 0, oldflags, async;
	nfsnode_t np;
	thread_t thd;
	kauth_cred_t cred;
	proc_t p = current_proc();
	int iomode, doff, dend, firstpg, lastpg;
	uint32_t pagemask;

	FSDBG_TOP(553, bp, NBOFF(bp), bp->nb_flags, 0);

	if (!ISSET(bp->nb_lflags, NBL_BUSY))
		panic("nfs_buf_write: buffer is not busy???");

	np = bp->nb_np;
	async = ISSET(bp->nb_flags, NB_ASYNC);
	oldflags = bp->nb_flags;

	CLR(bp->nb_flags, (NB_READ|NB_DONE|NB_ERROR|NB_DELWRI));
	if (ISSET(oldflags, NB_DELWRI)) {
		lck_mtx_lock(nfs_buf_mutex);
		nfs_nbdwrite--;
		NFSBUFCNTCHK();
		lck_mtx_unlock(nfs_buf_mutex);
		wakeup(&nfs_nbdwrite);
	}

	/* move to clean list */
	if (ISSET(oldflags, (NB_ASYNC|NB_DELWRI))) {
		lck_mtx_lock(nfs_buf_mutex);
		if (bp->nb_vnbufs.le_next != NFSNOLIST)
			LIST_REMOVE(bp, nb_vnbufs);
		LIST_INSERT_HEAD(&np->n_cleanblkhd, bp, nb_vnbufs);
		lck_mtx_unlock(nfs_buf_mutex);
	}
	nfs_node_lock_force(np);
	np->n_numoutput++;
	nfs_node_unlock(np);
	vnode_startwrite(NFSTOV(np));

	if (p && p->p_stats)
		OSIncrementAtomicLong(&p->p_stats->p_ru.ru_oublock);

	cred = bp->nb_wcred;
	if (!IS_VALID_CRED(cred) && ISSET(bp->nb_flags, NB_READ))
		cred = bp->nb_rcred;  /* shouldn't really happen, but... */
	if (IS_VALID_CRED(cred))
		kauth_cred_ref(cred);
	thd = async ? NULL : current_thread();

	/* We need to make sure the pages are locked before doing I/O.  */
	if (!ISSET(bp->nb_flags, NB_META)) {
		if (UBCINFOEXISTS(NFSTOV(np))) {
			if (!ISSET(bp->nb_flags, NB_PAGELIST)) {
				error = nfs_buf_upl_setup(bp);
				if (error) {
					printf("nfs_buf_write: upl create failed %d\n", error);
					SET(bp->nb_flags, NB_ERROR);
					bp->nb_error = error = EIO;
					nfs_buf_iodone(bp);
					goto out;
				}
				nfs_buf_upl_check(bp);
			}
		} else {
			/* We should never be in nfs_buf_write() with no UBCINFO. */
			printf("nfs_buf_write: ubcinfo already gone\n");
			SET(bp->nb_flags, NB_ERROR);
			bp->nb_error = error = EIO;
			nfs_buf_iodone(bp);
			goto out;
		}
	}

	/* If NB_NEEDCOMMIT is set, a commit RPC may do the trick. */
	if (ISSET(bp->nb_flags, NB_NEEDCOMMIT))
		nfs_buf_check_write_verifier(np, bp);
	if (ISSET(bp->nb_flags, NB_NEEDCOMMIT)) {
		struct nfsmount *nmp = NFSTONMP(np);
		if (nfs_mount_gone(nmp)) {
			SET(bp->nb_flags, NB_ERROR);
			bp->nb_error = error = EIO;
			nfs_buf_iodone(bp);
			goto out;
		}
		SET(bp->nb_flags, NB_WRITEINPROG);
		error = nmp->nm_funcs->nf_commit_rpc(np, NBOFF(bp) + bp->nb_dirtyoff,
				bp->nb_dirtyend - bp->nb_dirtyoff, bp->nb_wcred, bp->nb_verf);
		CLR(bp->nb_flags, NB_WRITEINPROG);
		if (error) {
			if (error != NFSERR_STALEWRITEVERF) {
				SET(bp->nb_flags, NB_ERROR);
				bp->nb_error = error;
			}
			nfs_buf_iodone(bp);
			goto out;
		}
		bp->nb_dirtyoff = bp->nb_dirtyend = 0;
		CLR(bp->nb_flags, NB_NEEDCOMMIT);
		nfs_node_lock_force(np);
		np->n_needcommitcnt--;
		CHECK_NEEDCOMMITCNT(np);
		nfs_node_unlock(np);
	}
	if (!error && (bp->nb_dirtyend > 0)) {
		/* sanity check the dirty range */
		if (NBOFF(bp) + bp->nb_dirtyend > (off_t) np->n_size) {
			bp->nb_dirtyend = np->n_size - NBOFF(bp);
			if (bp->nb_dirtyoff >= bp->nb_dirtyend)
				bp->nb_dirtyoff = bp->nb_dirtyend = 0;
		}
	}
	if (!error && (bp->nb_dirtyend > 0)) {
		/* there's a dirty range that needs to be written out */
		NFS_BUF_MAP(bp);

		doff = bp->nb_dirtyoff;
		dend = bp->nb_dirtyend;

		/* if doff page is dirty, move doff to start of page */
		if (NBPGDIRTY(bp, doff / PAGE_SIZE))
			doff -= doff & PAGE_MASK;
		/* try to expand write range to include preceding dirty pages */
		if (!(doff & PAGE_MASK))
			while ((doff > 0) && NBPGDIRTY(bp, (doff - 1) / PAGE_SIZE))
				doff -= PAGE_SIZE;
		/* if dend page is dirty, move dend to start of next page */
		if ((dend & PAGE_MASK) && NBPGDIRTY(bp, dend / PAGE_SIZE))
			dend = round_page_32(dend);
		/* try to expand write range to include trailing dirty pages */
		if (!(dend & PAGE_MASK))
			while ((dend < (int)bp->nb_bufsize) && NBPGDIRTY(bp, dend / PAGE_SIZE))
				dend += PAGE_SIZE;
		/* make sure to keep dend clipped to EOF */
		if ((NBOFF(bp) + dend) > (off_t) np->n_size)
			dend = np->n_size - NBOFF(bp);
		/* calculate range of complete pages being written */
		firstpg = round_page_32(doff) / PAGE_SIZE;
		lastpg = (trunc_page_32(dend) - 1) / PAGE_SIZE;
		/* calculate mask for that page range */
		pagemask = ((1 << (lastpg + 1)) - 1) & ~((1 << firstpg) - 1);

		/*
		 * compare page mask to nb_dirty; if there are other dirty pages
		 * then write FILESYNC; otherwise, write UNSTABLE if async and
		 * not needcommit/stable; otherwise write FILESYNC
		 */
		if (bp->nb_dirty & ~pagemask)
			iomode = NFS_WRITE_FILESYNC;
		else if ((bp->nb_flags & (NB_ASYNC | NB_NEEDCOMMIT | NB_STABLE)) == NB_ASYNC)
			iomode = NFS_WRITE_UNSTABLE;
		else
			iomode = NFS_WRITE_FILESYNC;

		/* write the whole contiguous dirty range */
		bp->nb_offio = doff;
		bp->nb_endio = dend;

		OSAddAtomic64(1, &nfsstats.write_bios);

		SET(bp->nb_flags, NB_WRITEINPROG);
		error = nfs_buf_write_rpc(bp, iomode, thd, cred);
		/*
		 * For async I/O, the callbacks will finish up the
		 * write and push out any dirty pages.  Otherwise,
		 * the write has already been finished and any dirty
		 * pages pushed out.
		 */
	} else {
		if (!error && bp->nb_dirty) /* write out any dirty pages */
			error = nfs_buf_write_dirty_pages(bp, thd, cred);
		nfs_buf_iodone(bp);
	}
	/* note: bp is still valid only for !async case */
out:
	if (!async) {
		error = nfs_buf_iowait(bp);
		/* move to clean list */
		if (oldflags & NB_DELWRI) {
			lck_mtx_lock(nfs_buf_mutex);
			if (bp->nb_vnbufs.le_next != NFSNOLIST)
				LIST_REMOVE(bp, nb_vnbufs);
			LIST_INSERT_HEAD(&np->n_cleanblkhd, bp, nb_vnbufs);
			lck_mtx_unlock(nfs_buf_mutex);
		}
		FSDBG_BOT(553, bp, NBOFF(bp), bp->nb_flags, error);
		nfs_buf_release(bp, 1);
		/* check if we need to invalidate (and we can) */
		if ((np->n_flag & NNEEDINVALIDATE) &&
		    !(np->n_bflag & (NBINVALINPROG|NBFLUSHINPROG))) {
			int invalidate = 0;
			nfs_node_lock_force(np);
			if (np->n_flag & NNEEDINVALIDATE) {
				invalidate = 1;
				np->n_flag &= ~NNEEDINVALIDATE;
			}
			nfs_node_unlock(np);
			if (invalidate) {
				/*
				 * There was a write error and we need to
				 * invalidate attrs and flush buffers in
				 * order to sync up with the server.
				 * (if this write was extending the file,
				 * we may no longer know the correct size)
				 *
				 * But we couldn't call vinvalbuf while holding
				 * the buffer busy.  So we call vinvalbuf() after
				 * releasing the buffer.
				 */
				nfs_vinvalbuf2(NFSTOV(np), V_SAVE|V_IGNORE_WRITEERR, thd, cred, 1);
			}
		}
	}

	if (IS_VALID_CRED(cred))
		kauth_cred_unref(&cred);
	return (error);
}