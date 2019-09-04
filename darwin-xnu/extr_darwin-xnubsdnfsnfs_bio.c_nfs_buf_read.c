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
typedef  int /*<<< orphan*/ * thread_t ;
struct nfsbuf {int /*<<< orphan*/  nb_flags; int /*<<< orphan*/  nb_rcred; int /*<<< orphan*/  nb_np; } ;
typedef  int /*<<< orphan*/  nfsnode_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
struct TYPE_2__ {int /*<<< orphan*/  read_bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_VALID_CRED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NB_ASYNC ; 
 int /*<<< orphan*/  NB_DONE ; 
 int /*<<< orphan*/  NB_READ ; 
 int /*<<< orphan*/  NFS_BUF_MAP (struct nfsbuf*) ; 
 int /*<<< orphan*/  OSAddAtomic64 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * current_thread () ; 
 int /*<<< orphan*/  kauth_cred_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ *) ; 
 int nfs_buf_read_rpc (struct nfsbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ nfsstats ; 
 int /*<<< orphan*/  panic (char*) ; 

int
nfs_buf_read(struct nfsbuf *bp)
{
	int error = 0;
	nfsnode_t np;
	thread_t thd;
	kauth_cred_t cred;

	np = bp->nb_np;
	cred = bp->nb_rcred;
	if (IS_VALID_CRED(cred))
		kauth_cred_ref(cred);
	thd = ISSET(bp->nb_flags, NB_ASYNC) ? NULL : current_thread();

	/* sanity checks */
	if (!ISSET(bp->nb_flags, NB_READ))
		panic("nfs_buf_read: !NB_READ");
	if (ISSET(bp->nb_flags, NB_DONE))
		CLR(bp->nb_flags, NB_DONE);

	NFS_BUF_MAP(bp);

	OSAddAtomic64(1, &nfsstats.read_bios);

	error = nfs_buf_read_rpc(bp, thd, cred);
	/*
	 * For async I/O, the callbacks will finish up the
	 * read.  Otherwise, the read has already been finished.
	 */

	if (IS_VALID_CRED(cred))
		kauth_cred_unref(&cred);
	return (error);
}