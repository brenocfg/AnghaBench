#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  TYPE_1__* uio_t ;
typedef  int /*<<< orphan*/  uio_buf ;
typedef  int /*<<< orphan*/  thread_t ;
struct nfsmount {int nm_vers; int nm_biosize; scalar_t__ nm_readahead; } ;
struct nfsbuf {int nb_flags; int nb_dirtyend; scalar_t__ nb_validoff; int nb_validend; int nb_dirtyoff; void* nb_wcred; void* nb_rcred; scalar_t__ nb_data; scalar_t__ nb_valid; scalar_t__ nb_dirty; } ;
typedef  int off_t ;
typedef  TYPE_2__* nfsnode_t ;
typedef  void* kauth_cred_t ;
typedef  int int64_t ;
typedef  int daddr64_t ;
struct TYPE_31__ {int /*<<< orphan*/  biocache_reads; } ;
struct TYPE_30__ {int n_flag; int n_size; int n_lastread; int n_lastrahead; } ;
struct TYPE_29__ {scalar_t__ uio_segflg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_DOWN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAST_USER_ADDR_T (scalar_t__) ; 
 int /*<<< orphan*/  CLR (int,int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FSDBG (int,TYPE_2__*,int,int,int) ; 
 int /*<<< orphan*/  FSDBG_BOT (int,TYPE_2__*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  FSDBG_TOP (int,TYPE_2__*,int,scalar_t__,int) ; 
 int INT_MAX ; 
 int IO_NOCACHE ; 
 scalar_t__ ISSET (int,int) ; 
 scalar_t__ IS_VALID_CRED (void*) ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  NBLK_READ ; 
 scalar_t__ NBOFF (struct nfsbuf*) ; 
 scalar_t__ NBPGDIRTY (struct nfsbuf*,int) ; 
 int /*<<< orphan*/  NBPGVALID (struct nfsbuf*,int) ; 
 int /*<<< orphan*/  NBPGVALID_SET (struct nfsbuf*,int) ; 
 int /*<<< orphan*/  NB_ASYNC ; 
 int NB_CACHE ; 
 int NB_DONE ; 
 int NB_ERROR ; 
 int NB_INVAL ; 
 int NB_NCRDAHEAD ; 
 int /*<<< orphan*/  NB_NOCACHE ; 
 int /*<<< orphan*/  NB_READ ; 
 int /*<<< orphan*/  NFSTOV (TYPE_2__*) ; 
 int /*<<< orphan*/  NFS_BUF_MAP (struct nfsbuf*) ; 
 int /*<<< orphan*/  NFS_DATA_LOCK_SHARED ; 
 int /*<<< orphan*/  NGA_CACHED ; 
 int /*<<< orphan*/  NGA_UNCACHED ; 
 int NMODIFIED ; 
 int NNEEDINVALIDATE ; 
 int NUPDATESIZE ; 
 int /*<<< orphan*/  OSAddAtomic64 (int,int /*<<< orphan*/ *) ; 
 int PAGE_SIZE ; 
 int PAGE_SIZE_64 ; 
 int /*<<< orphan*/  SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIO_READ ; 
 int UIO_SIZEOF (int) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 scalar_t__ UIO_USERSPACE ; 
 scalar_t__ UIO_USERSPACE32 ; 
 scalar_t__ UIO_USERSPACE64 ; 
 scalar_t__ VREG ; 
 struct nfsmount* VTONMP (int /*<<< orphan*/ ) ; 
 int V_IGNORE_WRITEERR ; 
 int V_SAVE ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  caddr_t ; 
 int cluster_copy_ubc_data (int /*<<< orphan*/ ,TYPE_1__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_ref (void*) ; 
 int nfs_buf_get (TYPE_2__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfsbuf**) ; 
 int /*<<< orphan*/  nfs_buf_normalize_valid_range (TYPE_2__*,struct nfsbuf*) ; 
 int nfs_buf_read (struct nfsbuf*) ; 
 int nfs_buf_readahead (TYPE_2__*,int,int*,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  nfs_buf_release (struct nfsbuf*,int) ; 
 int nfs_buf_write (struct nfsbuf*) ; 
 int /*<<< orphan*/  nfs_data_lock (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_data_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  nfs_data_update_size (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int nfs_getattr (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfs_node_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  nfs_node_lock_force (TYPE_2__*) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_2__*) ; 
 int nfs_read_rpc (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int nfs_vinvalbuf (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 TYPE_9__ nfsstats ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int round_page (int) ; 
 int round_page_32 (int) ; 
 scalar_t__ trunc_page (int) ; 
 scalar_t__ trunc_page_32 (int) ; 
 int /*<<< orphan*/  uio_addiov (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* uio_createwithbuffer (int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  uio_curriovbase (TYPE_1__*) ; 
 int uio_offset (TYPE_1__*) ; 
 scalar_t__ uio_resid (TYPE_1__*) ; 
 int uiomove (scalar_t__,int,TYPE_1__*) ; 
 int /*<<< orphan*/  vfs_context_thread (int /*<<< orphan*/ ) ; 
 void* vfs_context_ucred (int /*<<< orphan*/ ) ; 
 int vnode_vtype (int /*<<< orphan*/ ) ; 

int
nfs_bioread(nfsnode_t np, uio_t uio, int ioflag, vfs_context_t ctx)
{
	vnode_t vp = NFSTOV(np);
	struct nfsbuf *bp = NULL;
	struct nfsmount *nmp = VTONMP(vp);
	daddr64_t lbn, rabn = 0, lastrabn, maxrabn = -1;
	off_t diff;
	int error = 0, n = 0, on = 0;
	int nfsvers, biosize, modified, readaheads = 0;
	thread_t thd;
	kauth_cred_t cred;
	int64_t io_resid;

	FSDBG_TOP(514, np, uio_offset(uio), uio_resid(uio), ioflag);

	nfsvers = nmp->nm_vers;
	biosize = nmp->nm_biosize;
	thd = vfs_context_thread(ctx);
	cred = vfs_context_ucred(ctx);

	if (vnode_vtype(vp) != VREG) {
		printf("nfs_bioread: type %x unexpected\n", vnode_vtype(vp));
		FSDBG_BOT(514, np, 0xd1e0016, 0, EINVAL);
		return (EINVAL);
	}

	/*
	 * For NFS, cache consistency can only be maintained approximately.
	 * Although RFC1094 does not specify the criteria, the following is
	 * believed to be compatible with the reference port.
	 * 
	 * If the file has changed since the last read RPC or you have
	 * written to the file, you may have lost data cache consistency
	 * with the server.  So, check for a change, and flush all of the
	 * file's data out of the cache.
	 * NB: This implies that cache data can be read when up to
	 * NFS_MAXATTRTIMO seconds out of date. If you find that you
	 * need current attributes, nfs_getattr() can be forced to fetch
	 * new attributes (via NATTRINVALIDATE() or NGA_UNCACHED).
	 */

	if (ISSET(np->n_flag, NUPDATESIZE))
		nfs_data_update_size(np, 0);

	if ((error = nfs_node_lock(np))) {
		FSDBG_BOT(514, np, 0xd1e0222, 0, error);
		return (error);
	}

	if (np->n_flag & NNEEDINVALIDATE) {
		np->n_flag &= ~NNEEDINVALIDATE;
		nfs_node_unlock(np);
		error = nfs_vinvalbuf(vp, V_SAVE|V_IGNORE_WRITEERR, ctx, 1);
		if (!error)
			error = nfs_node_lock(np);
		if (error) {
			FSDBG_BOT(514, np, 0xd1e0322, 0, error);
			return (error);
		}
	}

	modified = (np->n_flag & NMODIFIED);
	nfs_node_unlock(np);
	/* nfs_getattr() will check changed and purge caches */
	error = nfs_getattr(np, NULL, ctx, modified ? NGA_UNCACHED : NGA_CACHED);
	if (error) {
		FSDBG_BOT(514, np, 0xd1e0004, 0, error);
		return (error);
	}

	if (uio_resid(uio) == 0) {
		FSDBG_BOT(514, np, 0xd1e0001, 0, 0);
		return (0);
	}
	if (uio_offset(uio) < 0) {
		FSDBG_BOT(514, np, 0xd1e0002, 0, EINVAL);
		return (EINVAL);
	}

	/*
	 * set up readahead - which may be limited by:
	 * + current request length (for IO_NOCACHE)
	 * + readahead setting
	 * + file size
	 */
	if (nmp->nm_readahead > 0) {
		off_t end = uio_offset(uio) + uio_resid(uio);
		if (end > (off_t)np->n_size)
			end = np->n_size;
		rabn = uio_offset(uio) / biosize;
		maxrabn = (end - 1) / biosize;
		nfs_node_lock_force(np);
		if (!(ioflag & IO_NOCACHE) &&
		    (!rabn || (rabn == np->n_lastread) || (rabn == (np->n_lastread+1)))) {
			maxrabn += nmp->nm_readahead;
			if ((maxrabn * biosize) >= (off_t)np->n_size)
				maxrabn = ((off_t)np->n_size - 1)/biosize;
		}
		if (maxrabn < np->n_lastrahead)
			np->n_lastrahead = -1;
		if (rabn < np->n_lastrahead)
			rabn = np->n_lastrahead + 1;
		nfs_node_unlock(np);
	} else {
		rabn = maxrabn = 0;
	}

	do {

		nfs_data_lock(np, NFS_DATA_LOCK_SHARED);
		lbn = uio_offset(uio) / biosize;

		/*
		 * Copy directly from any cached pages without grabbing the bufs.
		 * (If we are NOCACHE and we've issued readahead requests, we need
		 * to grab the NB_NCRDAHEAD bufs to drop them.)
		 */
		if ((!(ioflag & IO_NOCACHE) || !readaheads) &&
		    ((uio->uio_segflg == UIO_USERSPACE32 ||
		      uio->uio_segflg == UIO_USERSPACE64 ||
		      uio->uio_segflg == UIO_USERSPACE))) {
			io_resid = uio_resid(uio);
			diff = np->n_size - uio_offset(uio);
			if (diff < io_resid)
				io_resid = diff;
			if (io_resid > 0) {
				int count = (io_resid > INT_MAX) ? INT_MAX : io_resid;
				error = cluster_copy_ubc_data(vp, uio, &count, 0);
				if (error) {
					nfs_data_unlock(np);
					FSDBG_BOT(514, np, uio_offset(uio), 0xcacefeed, error);
					return (error);
				}
			}
			/* count any biocache reads that we just copied directly */
			if (lbn != (uio_offset(uio)/biosize)) {
				OSAddAtomic64((uio_offset(uio)/biosize) - lbn, &nfsstats.biocache_reads);
				FSDBG(514, np, 0xcacefeed, uio_offset(uio), error);
			}
		}

		lbn = uio_offset(uio) / biosize;
		on = uio_offset(uio) % biosize;
		nfs_node_lock_force(np);
		np->n_lastread = (uio_offset(uio) - 1) / biosize;
		nfs_node_unlock(np);

		if ((uio_resid(uio) <= 0) || (uio_offset(uio) >= (off_t)np->n_size)) {
			nfs_data_unlock(np);
			FSDBG_BOT(514, np, uio_offset(uio), uio_resid(uio), 0xaaaaaaaa);
			return (0);
		}

		/* adjust readahead block number, if necessary */
		if (rabn < lbn)
			rabn = lbn;
		lastrabn = MIN(maxrabn, lbn + nmp->nm_readahead);
		if (rabn <= lastrabn) { /* start readaheads */
			error = nfs_buf_readahead(np, ioflag, &rabn, lastrabn, thd, cred);
			if (error) {
				nfs_data_unlock(np);
				FSDBG_BOT(514, np, 0xd1e000b, 1, error);
				return (error);
			}
			readaheads = 1;
		}

		OSAddAtomic64(1, &nfsstats.biocache_reads);

		/*
		 * If the block is in the cache and has the required data
		 * in a valid region, just copy it out.
		 * Otherwise, get the block and write back/read in,
		 * as required.
		 */
again:
		io_resid = uio_resid(uio);
		n = (io_resid > (biosize - on)) ? (biosize - on) : io_resid;
		diff = np->n_size - uio_offset(uio);
		if (diff < n)
			n = diff;

		error = nfs_buf_get(np, lbn, biosize, thd, NBLK_READ, &bp);
		if (error) {
			nfs_data_unlock(np);
			FSDBG_BOT(514, np, 0xd1e000c, 0, error);
			return (error);
		}

		if ((ioflag & IO_NOCACHE) && ISSET(bp->nb_flags, NB_CACHE)) {
			/*
			 * IO_NOCACHE found a cached buffer.
			 * Flush the buffer if it's dirty.
			 * Invalidate the data if it wasn't just read
			 * in as part of a "nocache readahead".
			 */
			if (bp->nb_dirty || (bp->nb_dirtyend > 0)) {
				/* so write the buffer out and try again */
				SET(bp->nb_flags, NB_NOCACHE);
				goto flushbuffer;
			}
			if (ISSET(bp->nb_flags, NB_NCRDAHEAD)) {
				CLR(bp->nb_flags, NB_NCRDAHEAD);
				SET(bp->nb_flags, NB_NOCACHE);
			}
		}

		/* if any pages are valid... */
		if (bp->nb_valid) {
			/* ...check for any invalid pages in the read range */
			int pg, firstpg, lastpg, dirtypg;
			dirtypg = firstpg = lastpg = -1;
			pg = on/PAGE_SIZE;
			while (pg <= (on + n - 1)/PAGE_SIZE) {
				if (!NBPGVALID(bp,pg)) {
					if (firstpg < 0)
						firstpg = pg;
					lastpg = pg;
				} else if (firstpg >= 0 && dirtypg < 0 && NBPGDIRTY(bp,pg))
					dirtypg = pg;
				pg++;
			}

			/* if there are no invalid pages, we're all set */
			if (firstpg < 0) {
				if (bp->nb_validoff < 0) {
					/* valid range isn't set up, so */
					/* set it to what we know is valid */
					bp->nb_validoff = trunc_page(on);
					bp->nb_validend = round_page(on+n);
					nfs_buf_normalize_valid_range(np, bp);
				}
				goto buffer_ready;
			}

			/* there are invalid pages in the read range */
			if (((dirtypg > firstpg) && (dirtypg < lastpg)) ||
			    (((firstpg*PAGE_SIZE) < bp->nb_dirtyend) && (((lastpg+1)*PAGE_SIZE) > bp->nb_dirtyoff))) {
				/* there are also dirty page(s) (or range) in the read range, */
				/* so write the buffer out and try again */
flushbuffer:
				CLR(bp->nb_flags, (NB_DONE | NB_ERROR | NB_INVAL));
				SET(bp->nb_flags, NB_ASYNC);
				if (!IS_VALID_CRED(bp->nb_wcred)) {
					kauth_cred_ref(cred);
					bp->nb_wcred = cred;
				}
				error = nfs_buf_write(bp);
				if (error) {
					nfs_data_unlock(np);
					FSDBG_BOT(514, np, 0xd1e000d, 0, error);
					return (error);
				}
				goto again;
			}
			if (!bp->nb_dirty && bp->nb_dirtyend <= 0 &&
			    (lastpg - firstpg + 1) > (biosize/PAGE_SIZE)/2) {
				/* we need to read in more than half the buffer and the */
				/* buffer's not dirty, so just fetch the whole buffer */
				bp->nb_valid = 0;
			} else {
				/* read the page range in */
				uio_t auio;
				char uio_buf[ UIO_SIZEOF(1) ];
				
				NFS_BUF_MAP(bp);
				auio = uio_createwithbuffer(1, (NBOFF(bp) + firstpg * PAGE_SIZE_64),
						UIO_SYSSPACE, UIO_READ, &uio_buf[0], sizeof(uio_buf));
				if (!auio) {
					error = ENOMEM;
				} else {
					uio_addiov(auio, CAST_USER_ADDR_T(bp->nb_data + (firstpg * PAGE_SIZE)),
							((lastpg - firstpg + 1) * PAGE_SIZE));
					error = nfs_read_rpc(np, auio, ctx);
				}
				if (error) {
					if (ioflag & IO_NOCACHE)
						SET(bp->nb_flags, NB_NOCACHE);
					nfs_buf_release(bp, 1);
					nfs_data_unlock(np);
					FSDBG_BOT(514, np, 0xd1e000e, 0, error);
					return (error);
				}
				/* Make sure that the valid range is set to cover this read. */
				bp->nb_validoff = trunc_page_32(on);
				bp->nb_validend = round_page_32(on+n);
				nfs_buf_normalize_valid_range(np, bp);
				if (uio_resid(auio) > 0) {
					/* if short read, must have hit EOF, */
					/* so zero the rest of the range */
					bzero(CAST_DOWN(caddr_t, uio_curriovbase(auio)), uio_resid(auio));
				}
				/* mark the pages (successfully read) as valid */
				for (pg=firstpg; pg <= lastpg; pg++)
					NBPGVALID_SET(bp,pg);
			}
		}
		/* if no pages are valid, read the whole block */
		if (!bp->nb_valid) {
			if (!IS_VALID_CRED(bp->nb_rcred) && IS_VALID_CRED(cred)) {
				kauth_cred_ref(cred);
				bp->nb_rcred = cred;
			}
			SET(bp->nb_flags, NB_READ);
			CLR(bp->nb_flags, (NB_DONE | NB_ERROR | NB_INVAL));
			error = nfs_buf_read(bp);
			if (ioflag & IO_NOCACHE)
				SET(bp->nb_flags, NB_NOCACHE);
			if (error) {
				nfs_data_unlock(np);
				nfs_buf_release(bp, 1);
				FSDBG_BOT(514, np, 0xd1e000f, 0, error);
				return (error);
			}
		}
buffer_ready:
		/* validate read range against valid range and clip */
		if (bp->nb_validend > 0) {
			diff = (on >= bp->nb_validend) ? 0 : (bp->nb_validend - on);
			if (diff < n)
				n = diff;
		}
		if (n > 0) {
			NFS_BUF_MAP(bp);
			error = uiomove(bp->nb_data + on, n, uio);
		}

		nfs_buf_release(bp, 1);
		nfs_data_unlock(np);
		nfs_node_lock_force(np);
		np->n_lastread = (uio_offset(uio) - 1) / biosize;
		nfs_node_unlock(np);
	} while (error == 0 && uio_resid(uio) > 0 && n > 0);
	FSDBG_BOT(514, np, uio_offset(uio), uio_resid(uio), error);
	return (error);
}