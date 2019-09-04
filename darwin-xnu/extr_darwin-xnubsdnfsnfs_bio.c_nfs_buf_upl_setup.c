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
typedef  int /*<<< orphan*/ * upl_t ;
struct nfsbuf {int /*<<< orphan*/  nb_flags; int /*<<< orphan*/ * nb_pagelist; int /*<<< orphan*/  nb_np; int /*<<< orphan*/  nb_bufsize; } ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  FSDBG (int,struct nfsbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  NBOFF (struct nfsbuf*) ; 
 int /*<<< orphan*/  NB_PAGELIST ; 
 int /*<<< orphan*/  NB_READ ; 
 int /*<<< orphan*/  NFSTOV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int UPL_PRECIOUS ; 
 int UPL_WILL_MODIFY ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_FILE ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 
 scalar_t__ ubc_create_upl_kernel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int
nfs_buf_upl_setup(struct nfsbuf *bp)
{
	kern_return_t kret;
	upl_t upl;
	int upl_flags;

	if (ISSET(bp->nb_flags, NB_PAGELIST))
		return (0);

	upl_flags = UPL_PRECIOUS;
	if (!ISSET(bp->nb_flags, NB_READ)) {
		/*
		 * We're doing a "write", so we intend to modify
		 * the pages we're gathering.
		 */
		upl_flags |= UPL_WILL_MODIFY;
	}
	kret = ubc_create_upl_kernel(NFSTOV(bp->nb_np), NBOFF(bp), bp->nb_bufsize,
				&upl, NULL, upl_flags, VM_KERN_MEMORY_FILE);
	if (kret == KERN_INVALID_ARGUMENT) {
		/* vm object probably doesn't exist any more */
		bp->nb_pagelist = NULL;
		return (EINVAL);
	}
	if (kret != KERN_SUCCESS) {
		printf("nfs_buf_upl_setup(): failed to get pagelist %d\n", kret);
		bp->nb_pagelist = NULL;
		return (EIO);
	}

	FSDBG(538, bp, NBOFF(bp), bp->nb_bufsize, bp->nb_np);

	bp->nb_pagelist = upl;
	SET(bp->nb_flags, NB_PAGELIST);
	return (0);
}