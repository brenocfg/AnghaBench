#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uio_t ;
typedef  int /*<<< orphan*/  uio_buf ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  thread_t ;
struct nfsmount {TYPE_1__* nm_funcs; } ;
struct nfsbuf {int nb_dirty; int nb_bufsize; scalar_t__ nb_verf; int nb_error; int /*<<< orphan*/  nb_flags; scalar_t__ nb_data; TYPE_2__* nb_np; } ;
typedef  scalar_t__ off_t ;
typedef  TYPE_2__* nfsnode_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
struct TYPE_9__ {int /*<<< orphan*/  write_bios; } ;
struct TYPE_8__ {scalar_t__ n_size; } ;
struct TYPE_7__ {int (* nf_commit_rpc ) (TYPE_2__*,scalar_t__,int,int /*<<< orphan*/ ,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_USER_ADDR_T (scalar_t__) ; 
 int /*<<< orphan*/  CLR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NBOFF (struct nfsbuf*) ; 
 scalar_t__ NBPGDIRTY (struct nfsbuf*,int) ; 
 int /*<<< orphan*/  NB_ERROR ; 
 int /*<<< orphan*/  NB_WRITEINPROG ; 
 int NFSERR_STALEWRITEVERF ; 
 struct nfsmount* NFSTONMP (TYPE_2__*) ; 
 int /*<<< orphan*/  NFS_BUF_MAP (struct nfsbuf*) ; 
 int NFS_WRITE_FILESYNC ; 
 int NFS_WRITE_UNSTABLE ; 
 int /*<<< orphan*/  OSAddAtomic64 (int,int /*<<< orphan*/ *) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int UIO_SIZEOF (int) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 int nfs_write_rpc2 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,scalar_t__*) ; 
 TYPE_4__ nfsstats ; 
 int stub1 (TYPE_2__*,scalar_t__,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  uio_addiov (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uio_createwithbuffer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**,int) ; 
 int /*<<< orphan*/  uio_reset (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
nfs_buf_write_dirty_pages(struct nfsbuf *bp, thread_t thd, kauth_cred_t cred)
{
	nfsnode_t np = bp->nb_np;
	struct nfsmount *nmp = NFSTONMP(np);
	int error = 0, commit, iomode, iomode2, len, pg, count, npages, off;
	uint32_t dirty = bp->nb_dirty;
	uint64_t wverf;
	uio_t auio;
	char uio_buf [ UIO_SIZEOF(1) ];

	if (!bp->nb_dirty)
		return (0);

	/* there are pages marked dirty that need to be written out */
	OSAddAtomic64(1, &nfsstats.write_bios);
	NFS_BUF_MAP(bp);
	SET(bp->nb_flags, NB_WRITEINPROG);
	npages = bp->nb_bufsize / PAGE_SIZE;
	iomode = NFS_WRITE_UNSTABLE;

	auio = uio_createwithbuffer(1, 0, UIO_SYSSPACE, UIO_WRITE,
		&uio_buf, sizeof(uio_buf));

again:
	dirty = bp->nb_dirty;
	wverf = bp->nb_verf;
	commit = NFS_WRITE_FILESYNC;
	for (pg = 0; pg < npages; pg++) {
		if (!NBPGDIRTY(bp, pg))
			continue;
		count = 1;
		while (((pg + count) < npages) && NBPGDIRTY(bp, pg + count))
			count++;
		/* write count pages starting with page pg */
		off = pg * PAGE_SIZE;
		len = count * PAGE_SIZE;
		/* clip writes to EOF */
		if (NBOFF(bp) + off + len > (off_t) np->n_size)
			len -= (NBOFF(bp) + off + len) - np->n_size;
		if (len > 0) {
			iomode2 = iomode;
			uio_reset(auio, NBOFF(bp) + off, UIO_SYSSPACE, UIO_WRITE);
			uio_addiov(auio, CAST_USER_ADDR_T(bp->nb_data + off), len);
			error = nfs_write_rpc2(np, auio, thd, cred, &iomode2, &bp->nb_verf);
			if (error)
				break;
			if (iomode2 < commit) /* Retain the lowest commitment level returned. */
				commit = iomode2;
			if ((commit != NFS_WRITE_FILESYNC) && (wverf != bp->nb_verf)) {
				/* verifier changed, redo all the writes filesync */
				iomode = NFS_WRITE_FILESYNC;
				goto again;
			}
		}
		/* clear dirty bits */
		while (count--) {
			dirty &= ~(1 << pg);
			if (count) /* leave pg on last page */
				pg++;
		}
	}
	CLR(bp->nb_flags, NB_WRITEINPROG);

	if (!error && (commit != NFS_WRITE_FILESYNC)) {
		error = nmp->nm_funcs->nf_commit_rpc(np, NBOFF(bp), bp->nb_bufsize, cred, wverf);
		if (error == NFSERR_STALEWRITEVERF) {
			/* verifier changed, so we need to restart all the writes */
			iomode = NFS_WRITE_FILESYNC;
			goto again;
		}
	}
	if (!error) {
		bp->nb_dirty = dirty;
	} else {
		SET(bp->nb_flags, NB_ERROR);
		bp->nb_error = error;
	}
	return (error);
}