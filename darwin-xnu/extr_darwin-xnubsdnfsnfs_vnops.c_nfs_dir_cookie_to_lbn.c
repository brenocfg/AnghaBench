#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct nfsmount {int dummy; } ;
struct nfsdmap {int mru; int* next; TYPE_1__* cookies; } ;
struct nfsbuflists {int dummy; } ;
struct nfsbuf {scalar_t__ nb_lblkno; scalar_t__ nb_data; } ;
struct nfs_dir_buf_header {int ndbh_count; } ;
struct direntry {scalar_t__ d_seekoff; } ;
typedef  TYPE_2__* nfsnode_t ;
typedef  int int8_t ;
struct TYPE_12__ {int /*<<< orphan*/  direofcache_misses; int /*<<< orphan*/  direofcache_hits; } ;
struct TYPE_11__ {scalar_t__ n_eofcookie; int /*<<< orphan*/  n_cleanblkhd; struct nfsdmap* n_cookiecache; } ;
struct TYPE_10__ {scalar_t__ key; scalar_t__ lbn; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENXIO ; 
 struct nfsbuf* LIST_FIRST (struct nfsbuflists*) ; 
 int /*<<< orphan*/  LIST_INSERT_AFTER (struct nfsbuf*,struct nfsbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct nfsbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct nfsbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NBAC_NOWAIT ; 
 int /*<<< orphan*/  NBI_CLEAN ; 
 struct nfsmount* NFSTONMP (TYPE_2__*) ; 
 struct direntry* NFS_DIRENTRY_NEXT (struct direntry*) ; 
 struct direntry* NFS_DIR_BUF_FIRST_DIRENTRY (struct nfsbuf*) ; 
 int NFS_DIR_COOKIE_SAME32 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  OSAddAtomic64 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nb_vnbufs ; 
 scalar_t__ nfs_buf_acquire (struct nfsbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_buf_drop (struct nfsbuf*) ; 
 int /*<<< orphan*/  nfs_buf_itercomplete (TYPE_2__*,struct nfsbuflists*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_buf_iterprepare (TYPE_2__*,struct nfsbuflists*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_buf_mutex ; 
 int /*<<< orphan*/  nfs_buf_refget (struct nfsbuf*) ; 
 int /*<<< orphan*/  nfs_buf_refrele (struct nfsbuf*) ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 scalar_t__ nfs_node_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_2__*) ; 
 TYPE_3__ nfsstats ; 

int
nfs_dir_cookie_to_lbn(nfsnode_t dnp, uint64_t cookie, int *ptc, uint64_t *lbnp)
{
	struct nfsdmap *ndcc = dnp->n_cookiecache;
	int8_t eofptc, found;
	int i, iptc;
	struct nfsmount *nmp;
	struct nfsbuf *bp, *lastbp;
	struct nfsbuflists blist;
	struct direntry *dp, *dpptc;
	struct nfs_dir_buf_header *ndbhp;

	if (!cookie) {  /* initial cookie */
		*lbnp = 0;
		*ptc = 0;
		return (0);
	}

	if (nfs_node_lock(dnp))
		return (ENOENT);

	if (cookie == dnp->n_eofcookie) { /* EOF cookie */
		nfs_node_unlock(dnp);
		OSAddAtomic64(1, &nfsstats.direofcache_hits);
		*ptc = 0;
		return (-1);
	}
	/* note if cookie is a 32-bit match with the EOF cookie */
	eofptc = *ptc ? NFS_DIR_COOKIE_SAME32(cookie, dnp->n_eofcookie) : 0;
	iptc = -1;

	/* search the list for the cookie */
	for (i = ndcc ? ndcc->mru : -1; i >= 0; i = ndcc->next[i]) {
		if (ndcc->cookies[i].key == cookie) {
			/* found a match for this cookie */
			*lbnp = ndcc->cookies[i].lbn;
			nfs_node_unlock(dnp);
			OSAddAtomic64(1, &nfsstats.direofcache_hits);
			*ptc = 0;
			return (0);
		}
		/* check for 32-bit match */
		if (*ptc && (iptc == -1) && NFS_DIR_COOKIE_SAME32(ndcc->cookies[i].key, cookie))
			iptc = i;
	}
	/* exact match not found */
	if (eofptc) {
		/* but 32-bit match hit the EOF cookie */
		nfs_node_unlock(dnp);
		OSAddAtomic64(1, &nfsstats.direofcache_hits);
		return (-1);
	}
	if (iptc >= 0) {
		/* but 32-bit match got a hit */
		*lbnp = ndcc->cookies[iptc].lbn;
		nfs_node_unlock(dnp);
		OSAddAtomic64(1, &nfsstats.direofcache_hits);
		return (0);
	}
	nfs_node_unlock(dnp);

	/*
	 * No match found in the cookie cache... hmm...
	 * Let's search the directory's buffers for the cookie.
	 */
	nmp = NFSTONMP(dnp);
	if (nfs_mount_gone(nmp))
		return (ENXIO);
	dpptc = NULL;
	found = 0;

	lck_mtx_lock(nfs_buf_mutex);
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
		lastbp = NULL;
		while ((bp = LIST_FIRST(&blist))) {
			LIST_REMOVE(bp, nb_vnbufs);
			if (!lastbp)
				LIST_INSERT_HEAD(&dnp->n_cleanblkhd, bp, nb_vnbufs);
			else
				LIST_INSERT_AFTER(lastbp, bp, nb_vnbufs);
			lastbp = bp;
			if (found)
				continue;
			nfs_buf_refget(bp);
			if (nfs_buf_acquire(bp, NBAC_NOWAIT, 0, 0)) {
				/* just skip this buffer */
				nfs_buf_refrele(bp);
				continue;
			}
			nfs_buf_refrele(bp);

			/* scan the buffer for the cookie */
			ndbhp = (struct nfs_dir_buf_header*)bp->nb_data;
			dp = NFS_DIR_BUF_FIRST_DIRENTRY(bp);
			dpptc = NULL;
			for (i=0; (i < ndbhp->ndbh_count) && (cookie != dp->d_seekoff); i++) {
				if (*ptc && !dpptc && NFS_DIR_COOKIE_SAME32(cookie, dp->d_seekoff)) {
					dpptc = dp;
					iptc = i;
				}
				dp = NFS_DIRENTRY_NEXT(dp);
			}
			if ((i == ndbhp->ndbh_count) && dpptc) {
				/* found only a PTC match */
				dp = dpptc;
				i = iptc;
			} else if (i < ndbhp->ndbh_count) {
				*ptc = 0;
			}
			if (i < (ndbhp->ndbh_count-1)) {
				/* next entry is *in* this buffer: return this block */
				*lbnp = bp->nb_lblkno;
				found = 1;
			} else if (i == (ndbhp->ndbh_count-1)) {
				/* next entry refers to *next* buffer: return next block */
				*lbnp = dp->d_seekoff;
				found = 1;
			}
			nfs_buf_drop(bp);
		}
		nfs_buf_itercomplete(dnp, &blist, NBI_CLEAN);
	}
	lck_mtx_unlock(nfs_buf_mutex);
	if (found) {
		OSAddAtomic64(1, &nfsstats.direofcache_hits);
		return (0);
	}

	/* still not found... oh well, just start a new block */
	*lbnp = cookie;
	OSAddAtomic64(1, &nfsstats.direofcache_misses);
	return (0);
}