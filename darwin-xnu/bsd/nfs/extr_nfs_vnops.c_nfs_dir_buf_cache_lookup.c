#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/  u_int64_t ;
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  thread_t ;
struct nfsmount {int dummy; } ;
struct nfsbuflists {int dummy; } ;
struct nfsbuf {int /*<<< orphan*/  nb_lblkno; } ;
struct nfs_vattr {int dummy; } ;
struct componentname {int cn_namelen; char* cn_nameptr; } ;
typedef  TYPE_1__* nfsnode_t ;
struct TYPE_16__ {int /*<<< orphan*/  fh_len; int /*<<< orphan*/  fh_data; } ;
typedef  TYPE_2__ fhandle_t ;
typedef  int /*<<< orphan*/  daddr64_t ;
struct TYPE_15__ {scalar_t__ n_attrstamp; int /*<<< orphan*/  n_xid; int /*<<< orphan*/  n_auth; int /*<<< orphan*/  n_lastdbl; int /*<<< orphan*/  n_cleanblkhd; } ;

/* Variables and functions */
 int ENXIO ; 
 int ESRCH ; 
 struct nfsbuf* LIST_FIRST (struct nfsbuflists*) ; 
 int /*<<< orphan*/  LIST_INSERT_AFTER (struct nfsbuf*,struct nfsbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct nfsbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct nfsbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NBAC_NOWAIT ; 
 int /*<<< orphan*/  NBI_CLEAN ; 
 int NBLK_ONLYVALID ; 
 int NBLK_READ ; 
 int /*<<< orphan*/  NDBS_PURGE ; 
 int /*<<< orphan*/  NDBS_UPDATE ; 
 int /*<<< orphan*/  NFSTOMP (TYPE_1__*) ; 
 struct nfsmount* NFSTONMP (TYPE_1__*) ; 
 int /*<<< orphan*/  NFS_DIRBLKSIZ ; 
 int /*<<< orphan*/  NGA_CACHED ; 
 int /*<<< orphan*/  NG_MAKEENTRY ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nb_vnbufs ; 
 scalar_t__ nfs_buf_acquire (struct nfsbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_buf_drop (struct nfsbuf*) ; 
 int nfs_buf_get (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct nfsbuf**) ; 
 int /*<<< orphan*/  nfs_buf_itercomplete (TYPE_1__*,struct nfsbuflists*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_buf_iterprepare (TYPE_1__*,struct nfsbuflists*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_buf_mutex ; 
 int /*<<< orphan*/  nfs_buf_refget (struct nfsbuf*) ; 
 int /*<<< orphan*/  nfs_buf_refrele (struct nfsbuf*) ; 
 int /*<<< orphan*/  nfs_buf_release (struct nfsbuf*,int /*<<< orphan*/ ) ; 
 int nfs_dir_buf_search (struct nfsbuf*,struct componentname*,TYPE_2__*,struct nfs_vattr*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_getattr (TYPE_1__*,struct nfs_vattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 int nfs_nget (int /*<<< orphan*/ ,TYPE_1__*,struct componentname*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfs_vattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  vfs_context_thread (int /*<<< orphan*/ ) ; 

int
nfs_dir_buf_cache_lookup(nfsnode_t dnp, nfsnode_t *npp, struct componentname *cnp, vfs_context_t ctx, int purge)
{
	nfsnode_t newnp;
	struct nfsmount *nmp;
	int error = 0, i, found = 0, count = 0;
	u_int64_t xid;
	struct nfs_vattr nvattr;
	fhandle_t fh;
	time_t attrstamp = 0;
	thread_t thd = vfs_context_thread(ctx);
	struct nfsbuf *bp, *lastbp, *foundbp;
	struct nfsbuflists blist;
	daddr64_t lbn, nextlbn;
	int dotunder = (cnp->cn_namelen > 2) && (cnp->cn_nameptr[0] == '.') && (cnp->cn_nameptr[1] == '_');

	nmp = NFSTONMP(dnp);
	if (nfs_mount_gone(nmp))
		return (ENXIO);
	if (!purge)
		*npp = NULL;

	/* first check most recent buffer (and next one too) */
	lbn = dnp->n_lastdbl;
	for (i=0; i < 2; i++) {
		if ((error = nfs_buf_get(dnp, lbn, NFS_DIRBLKSIZ, thd, NBLK_READ|NBLK_ONLYVALID, &bp)))
			return (error);
		if (!bp)
			break;
		count++;
		error = nfs_dir_buf_search(bp, cnp, &fh, &nvattr, &xid, &attrstamp, &nextlbn, purge ? NDBS_PURGE : 0);
		nfs_buf_release(bp, 0);
		if (error == ESRCH) {
			error = 0;
		} else {
			found = 1;
			break;
		}
		lbn = nextlbn;
	}

	lck_mtx_lock(nfs_buf_mutex);
	if (found) {
		dnp->n_lastdbl = lbn;
		goto done;
	}

	/*
	 * Scan the list of buffers, keeping them in order.
	 * Note that itercomplete inserts each of the remaining buffers
	 * into the head of list (thus reversing the elements).  So, we
	 * make sure to iterate through all buffers, inserting them after
	 * each other, to keep them in order.
	 * Also note: the LIST_INSERT_AFTER(lastbp) is only safe because
	 * we don't drop nfs_buf_mutex.
	 */
	if (!nfs_buf_iterprepare(dnp, &blist, NBI_CLEAN)) {
		lastbp = foundbp = NULL;
		while ((bp = LIST_FIRST(&blist))) {
			LIST_REMOVE(bp, nb_vnbufs);
			if (!lastbp)
				LIST_INSERT_HEAD(&dnp->n_cleanblkhd, bp, nb_vnbufs);
			else
				LIST_INSERT_AFTER(lastbp, bp, nb_vnbufs);
			lastbp = bp;
			if (error || found)
				continue;
			if (!purge && dotunder && (count > 100)) /* don't waste too much time looking for ._ files */
				continue;
			nfs_buf_refget(bp);
			lbn = bp->nb_lblkno;
			if (nfs_buf_acquire(bp, NBAC_NOWAIT, 0, 0)) {
				/* just skip this buffer */
				nfs_buf_refrele(bp);
				continue;
			}
			nfs_buf_refrele(bp);
			count++;
			error = nfs_dir_buf_search(bp, cnp, &fh, &nvattr, &xid, &attrstamp, NULL, purge ? NDBS_PURGE : 0);
			if (error == ESRCH) {
				error = 0;
			} else {
				found = 1;
				foundbp = bp;
			}
			nfs_buf_drop(bp);
		}
		if (found) {
			LIST_REMOVE(foundbp, nb_vnbufs);
			LIST_INSERT_HEAD(&dnp->n_cleanblkhd, foundbp, nb_vnbufs);
			dnp->n_lastdbl = foundbp->nb_lblkno;
		}
		nfs_buf_itercomplete(dnp, &blist, NBI_CLEAN);
	}
done:
	lck_mtx_unlock(nfs_buf_mutex);

	if (!error && found && !purge) {
		error = nfs_nget(NFSTOMP(dnp), dnp, cnp, fh.fh_data, fh.fh_len,
				&nvattr, &xid, dnp->n_auth, NG_MAKEENTRY, &newnp);
		if (error)
			return (error);
		newnp->n_attrstamp = attrstamp;
		*npp = newnp;
		nfs_node_unlock(newnp);
		/* check if the dir buffer's attrs are out of date */
		if (!nfs_getattr(newnp, &nvattr, ctx, NGA_CACHED) &&
		    (newnp->n_attrstamp != attrstamp)) {
			/* they are, so update them */
			error = nfs_buf_get(dnp, lbn, NFS_DIRBLKSIZ, thd, NBLK_READ|NBLK_ONLYVALID, &bp);
			if (!error && bp) {
				attrstamp = newnp->n_attrstamp;
				xid = newnp->n_xid;
				nfs_dir_buf_search(bp, cnp, &fh, &nvattr, &xid, &attrstamp, NULL, NDBS_UPDATE);
				nfs_buf_release(bp, 0);
			}
			error = 0;
		}
	}

	return (error);
}