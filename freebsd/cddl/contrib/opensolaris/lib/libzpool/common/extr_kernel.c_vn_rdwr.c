#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int v_dump_fd; int /*<<< orphan*/  v_fd; } ;
typedef  TYPE_1__ vnode_t ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  rlim64_t ;
typedef  scalar_t__ offset_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EIO ; 
 int SPA_MINBLOCKSHIFT ; 
 int UIO_READ ; 
 int errno ; 
 int pread64 (int /*<<< orphan*/ ,void*,int,scalar_t__) ; 
 int pwrite64 (int,char*,int,scalar_t__) ; 
 int rand () ; 

int
vn_rdwr(int uio, vnode_t *vp, void *addr, ssize_t len, offset_t offset,
    int x1, int x2, rlim64_t x3, void *x4, ssize_t *residp)
{
	ssize_t iolen, split;

	if (uio == UIO_READ) {
		iolen = pread64(vp->v_fd, addr, len, offset);
		if (vp->v_dump_fd != -1) {
			int status =
			    pwrite64(vp->v_dump_fd, addr, iolen, offset);
			ASSERT(status != -1);
		}
	} else {
		/*
		 * To simulate partial disk writes, we split writes into two
		 * system calls so that the process can be killed in between.
		 */
		int sectors = len >> SPA_MINBLOCKSHIFT;
		split = (sectors > 0 ? rand() % sectors : 0) <<
		    SPA_MINBLOCKSHIFT;
		iolen = pwrite64(vp->v_fd, addr, split, offset);
		iolen += pwrite64(vp->v_fd, (char *)addr + split,
		    len - split, offset + split);
	}

	if (iolen == -1)
		return (errno);
	if (residp)
		*residp = len - iolen;
	else if (iolen != len)
		return (EIO);
	return (0);
}