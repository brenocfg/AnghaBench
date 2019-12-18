#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/  uio_t ;
typedef  int /*<<< orphan*/  uio_buf ;
struct fd_vn_data {int fv_eofflag; size_t fv_bufallocsiz; size_t fv_bufsiz; int /*<<< orphan*/ * fv_buf; scalar_t__ fv_bufdone; int /*<<< orphan*/  fv_eoff; int /*<<< orphan*/  fv_soff; scalar_t__ fv_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_USER_ADDR_T (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t FV_DIRBUF_MAX_SIZ ; 
 size_t FV_DIRBUF_START_SIZ ; 
 int /*<<< orphan*/  MALLOC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_FD_DIRBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  UIO_READ ; 
 int UIO_SIZEOF (int) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  VNODE_READDIR_EXTENDED ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  caddr_t ; 
 int /*<<< orphan*/  uio_addiov (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  uio_createwithbuffer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  uio_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uio_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uio_resid (int /*<<< orphan*/ ) ; 
 int vnode_readdir64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
refill_fd_direntries(vfs_context_t ctx, vnode_t dvp, struct fd_vn_data *fvd,
    int *eofflagp)
{
	uio_t rdir_uio;
	char uio_buf[UIO_SIZEOF(1)];
	size_t rdirbufsiz;
	size_t rdirbufused;
	int eofflag;
	int nentries;
	int error;

	/*
	 * If the last readdir returned EOF, don't try again.
	 */
	if (fvd->fv_eofflag) {
		*eofflagp = 1;
		if (fvd->fv_buf) {
			FREE(fvd->fv_buf, M_FD_DIRBUF);
			fvd->fv_buf = NULL;
		}
		return 0;
	}

	error = 0;

	/*
	 * If there is a cached allocation size of the dirbuf that should be
	 * allocated, use that. Otherwise start with a allocation size of
	 * FV_DIRBUF_START_SIZ. This start size may need to be increased if the
	 * filesystem doesn't respond to the initial size.
	 */

	if (fvd->fv_offset && fvd->fv_bufallocsiz) {
		rdirbufsiz = fvd->fv_bufallocsiz;
	} else {
		rdirbufsiz = FV_DIRBUF_START_SIZ;
	}

	*eofflagp = 0;

	rdir_uio = uio_createwithbuffer(1, 0, UIO_SYSSPACE, UIO_READ,
	    &uio_buf[0], sizeof(uio_buf));

retry_alloc:
	/*
	 * Don't explicitly zero out this buffer since this is
	 * not copied out to user space.
	 */
	if (!fvd->fv_buf) {
		MALLOC(fvd->fv_buf, caddr_t, rdirbufsiz, M_FD_DIRBUF, M_WAITOK);
		fvd->fv_bufdone = 0;
	}

	uio_reset(rdir_uio, fvd->fv_eoff, UIO_SYSSPACE, UIO_READ);
	uio_addiov(rdir_uio, CAST_USER_ADDR_T(fvd->fv_buf), rdirbufsiz);

	/*
	 * Some filesystems do not set nentries or eofflag...
	 */
	eofflag = 0;
	nentries = 0;
	error = vnode_readdir64(dvp, rdir_uio, VNODE_READDIR_EXTENDED,
	    &eofflag, &nentries, ctx);

	rdirbufused = rdirbufsiz - (size_t)uio_resid(rdir_uio);

	if (!error && (rdirbufused > 0) && (rdirbufused <= rdirbufsiz)) {
		/* Save offsets */
		fvd->fv_soff = fvd->fv_eoff;
		fvd->fv_eoff = uio_offset(rdir_uio);
		 /* Save eofflag state but don't return EOF for this time.*/
		fvd->fv_eofflag = eofflag;
		eofflag = 0;
		 /* Reset buffer parameters */
		fvd->fv_bufsiz = rdirbufused;
		fvd->fv_bufdone = 0;
		bzero(fvd->fv_buf + rdirbufused, rdirbufsiz - rdirbufused);
		/* Cache allocation size the Filesystem responded to */
		fvd->fv_bufallocsiz = rdirbufsiz;
	} else if (!eofflag && (rdirbufsiz < FV_DIRBUF_MAX_SIZ)) {
		/*
		 * Some Filesystems have higher requirements for the
		 * smallest buffer size they will respond to for a
		 * directory listing. Start (relatively) small but increase
		 * it upto FV_DIRBUF_MAX_SIZ. Most should be good with
		 * 1*direntry. Cache the size found so that this does not need
		 * need to be done every time. This also means that an error
		 * from VNOP_READDIR is ignored until at least FV_DIRBUF_MAX_SIZ
		 * has been attempted.
		 */
		FREE(fvd->fv_buf, M_FD_DIRBUF);
		fvd->fv_buf = NULL;
		rdirbufsiz = 2 * rdirbufsiz;
		fvd->fv_bufallocsiz = 0;
		goto retry_alloc;
	} else if (!error) {
		/*
		 * The Filesystem did not set eofflag but also did not
		 * return any entries (or an error). It is presumed that
		 * EOF has been reached.
		 */
		fvd->fv_eofflag = eofflag = 1;
	}

	/*
	 * If the filesystem returned an error and it had previously returned
	 * EOF, ignore the error and set EOF.
	 */
	if (error && fvd->fv_eofflag) {
		eofflag = 1;
		error = 0;
	}

	/*
	 * If either the directory has either hit EOF or an error, now is a good
	 * time to free up directory entry buffer.
	 */
	if ((error || eofflag) && fvd->fv_buf) {
		FREE(fvd->fv_buf, M_FD_DIRBUF);
		fvd->fv_buf = NULL;
	}

	*eofflagp = eofflag;

	return (error);
}