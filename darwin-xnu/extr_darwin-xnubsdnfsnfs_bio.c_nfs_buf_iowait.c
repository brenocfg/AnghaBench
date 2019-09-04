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
struct nfsbuf {int nb_error; int /*<<< orphan*/  nb_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINTR ; 
 int EIO ; 
 int /*<<< orphan*/  FSDBG_BOT (int,struct nfsbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FSDBG_TOP (int,struct nfsbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NBOFF (struct nfsbuf*) ; 
 int /*<<< orphan*/  NB_DONE ; 
 int /*<<< orphan*/  NB_EINTR ; 
 int /*<<< orphan*/  NB_ERROR ; 
 scalar_t__ PRIBIO ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (struct nfsbuf*,int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_buf_mutex ; 

int
nfs_buf_iowait(struct nfsbuf *bp)
{
	FSDBG_TOP(549, bp, NBOFF(bp), bp->nb_flags, bp->nb_error);

	lck_mtx_lock(nfs_buf_mutex);

	while (!ISSET(bp->nb_flags, NB_DONE))
		msleep(bp, nfs_buf_mutex, PRIBIO + 1, "nfs_buf_iowait", NULL);

	lck_mtx_unlock(nfs_buf_mutex);

	FSDBG_BOT(549, bp, NBOFF(bp), bp->nb_flags, bp->nb_error);

	/* check for interruption of I/O, then errors. */
	if (ISSET(bp->nb_flags, NB_EINTR)) {
		CLR(bp->nb_flags, NB_EINTR);
		return (EINTR);
	} else if (ISSET(bp->nb_flags, NB_ERROR))
		return (bp->nb_error ? bp->nb_error : EIO);
	return (0);
}