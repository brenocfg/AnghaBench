#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timeval {scalar_t__ tv_sec; } ;
struct nfsbuffreehead {int dummy; } ;
struct TYPE_2__ {scalar_t__ le_next; } ;
struct nfsbuf {scalar_t__ nb_timestamp; int /*<<< orphan*/  nb_bufsize; scalar_t__ nb_data; int /*<<< orphan*/  nb_flags; int /*<<< orphan*/  nb_wcred; int /*<<< orphan*/  nb_rcred; int /*<<< orphan*/ * nb_np; TYPE_1__ nb_vnbufs; scalar_t__ nb_refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (struct nfsbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSDBG (int,scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_VALID_CRED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct nfsbuf*,int /*<<< orphan*/ ) ; 
 int LRU_FREEUP_FRAC_ON_TIMER ; 
 int LRU_TO_FREEUP ; 
 int META_FREEUP_FRAC_ON_TIMER ; 
 int META_TO_FREEUP ; 
 int /*<<< orphan*/  M_TEMP ; 
 scalar_t__ NBUFSTAMPVALID (struct nfsbuf*) ; 
 int /*<<< orphan*/  NB_META ; 
 int /*<<< orphan*/  NFSBUFCNTCHK () ; 
 int NFSBUF_LRU_STALE ; 
 int NFSBUF_META_STALE ; 
 scalar_t__ NFSNOLIST ; 
 struct nfsbuf* TAILQ_FIRST (struct nfsbuffreehead*) ; 
 int /*<<< orphan*/  TAILQ_INIT (struct nfsbuffreehead*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (struct nfsbuffreehead*,struct nfsbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct nfsbuffreehead*,struct nfsbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  microuptime (struct timeval*) ; 
 int /*<<< orphan*/  nb_free ; 
 int /*<<< orphan*/  nb_hash ; 
 int /*<<< orphan*/  nb_vnbufs ; 
 int /*<<< orphan*/  nfs_buf_mutex ; 
 int /*<<< orphan*/  nfs_buf_remfree (struct nfsbuf*) ; 
 scalar_t__ nfsbufcnt ; 
 struct nfsbuffreehead nfsbuffree ; 
 int nfsbuffreecnt ; 
 struct nfsbuffreehead nfsbuffreemeta ; 
 int nfsbuffreemetacnt ; 
 int /*<<< orphan*/  nfsbufmetacnt ; 
 scalar_t__ nfsbufmin ; 

void
nfs_buf_freeup(int timer)
{
	struct nfsbuf *fbp;
	struct timeval now;
	int count;
	struct nfsbuffreehead nfsbuffreeup;

	TAILQ_INIT(&nfsbuffreeup);

	lck_mtx_lock(nfs_buf_mutex);

	microuptime(&now);

	FSDBG(320, nfsbufcnt, nfsbuffreecnt, nfsbuffreemetacnt, 0);

	count = timer ? nfsbuffreecnt/LRU_FREEUP_FRAC_ON_TIMER : LRU_TO_FREEUP;
	while ((nfsbufcnt > nfsbufmin) && (count-- > 0)) {
		fbp = TAILQ_FIRST(&nfsbuffree);
		if (!fbp)
			break;
		if (fbp->nb_refs)
			break;
		if (NBUFSTAMPVALID(fbp) &&
		    (fbp->nb_timestamp + (2*NFSBUF_LRU_STALE)) > now.tv_sec)
			break;
		nfs_buf_remfree(fbp);
		/* disassociate buffer from any nfsnode */
		if (fbp->nb_np) {
			if (fbp->nb_vnbufs.le_next != NFSNOLIST) {
				LIST_REMOVE(fbp, nb_vnbufs);
				fbp->nb_vnbufs.le_next = NFSNOLIST;
			}
			fbp->nb_np = NULL;
		}
		LIST_REMOVE(fbp, nb_hash);
		TAILQ_INSERT_TAIL(&nfsbuffreeup, fbp, nb_free);
		nfsbufcnt--;
	}

	count = timer ? nfsbuffreemetacnt/META_FREEUP_FRAC_ON_TIMER : META_TO_FREEUP;
	while ((nfsbufcnt > nfsbufmin) && (count-- > 0)) {
		fbp = TAILQ_FIRST(&nfsbuffreemeta);
		if (!fbp)
			break;
		if (fbp->nb_refs)
			break;
		if (NBUFSTAMPVALID(fbp) &&
		    (fbp->nb_timestamp + (2*NFSBUF_META_STALE)) > now.tv_sec)
			break;
		nfs_buf_remfree(fbp);
		/* disassociate buffer from any nfsnode */
		if (fbp->nb_np) {
			if (fbp->nb_vnbufs.le_next != NFSNOLIST) {
				LIST_REMOVE(fbp, nb_vnbufs);
				fbp->nb_vnbufs.le_next = NFSNOLIST;
			}
			fbp->nb_np = NULL;
		}
		LIST_REMOVE(fbp, nb_hash);
		TAILQ_INSERT_TAIL(&nfsbuffreeup, fbp, nb_free);
		nfsbufcnt--;
		nfsbufmetacnt--;
	}

	FSDBG(320, nfsbufcnt, nfsbuffreecnt, nfsbuffreemetacnt, 0);
	NFSBUFCNTCHK();

	lck_mtx_unlock(nfs_buf_mutex);

	while ((fbp = TAILQ_FIRST(&nfsbuffreeup))) {
		TAILQ_REMOVE(&nfsbuffreeup, fbp, nb_free);
		/* nuke any creds */
		if (IS_VALID_CRED(fbp->nb_rcred))
			kauth_cred_unref(&fbp->nb_rcred);
		if (IS_VALID_CRED(fbp->nb_wcred))
			kauth_cred_unref(&fbp->nb_wcred);
		/* if buf was NB_META, dump buffer */
		if (ISSET(fbp->nb_flags, NB_META) && fbp->nb_data)
			kfree(fbp->nb_data, fbp->nb_bufsize);
		FREE(fbp, M_TEMP);
	}

}