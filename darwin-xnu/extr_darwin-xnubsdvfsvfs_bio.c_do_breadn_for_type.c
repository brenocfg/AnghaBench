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
typedef  int /*<<< orphan*/  kauth_cred_t ;
typedef  int /*<<< orphan*/  errno_t ;
typedef  int /*<<< orphan*/  daddr64_t ;
typedef  int /*<<< orphan*/  buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_ASYNC ; 
 int /*<<< orphan*/  bio_doread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  buf_biowait (int /*<<< orphan*/ ) ; 
 scalar_t__ incore (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static errno_t
do_breadn_for_type(vnode_t vp, daddr64_t blkno, int size, daddr64_t *rablks, int *rasizes, 
		   int nrablks, kauth_cred_t cred, buf_t *bpp, int queuetype)
{
	buf_t	bp;
	int	i;

	bp = *bpp = bio_doread(vp, blkno, size, cred, 0, queuetype);

	/*
	 * For each of the read-ahead blocks, start a read, if necessary.
	 */
	for (i = 0; i < nrablks; i++) {
		/* If it's in the cache, just go on to next one. */
		if (incore(vp, rablks[i]))
			continue;

		/* Get a buffer for the read-ahead block */
		(void) bio_doread(vp, rablks[i], rasizes[i], cred, B_ASYNC, queuetype);
	}

	/* Otherwise, we had to start a read for it; wait until it's valid. */
	return (buf_biowait(bp));
}