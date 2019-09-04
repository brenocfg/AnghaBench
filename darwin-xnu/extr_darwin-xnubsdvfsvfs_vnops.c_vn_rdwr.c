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
typedef  int /*<<< orphan*/  uint64_t ;
struct vnode {int dummy; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
typedef  int int64_t ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;
typedef  enum uio_rw { ____Placeholder_uio_rw } uio_rw ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int vn_rdwr_64 (int,struct vnode*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

int
vn_rdwr(
	enum uio_rw rw,
	struct vnode *vp,
	caddr_t base,
	int len,
	off_t offset,
	enum uio_seg segflg,
	int ioflg,
	kauth_cred_t cred,
	int *aresid,
	proc_t p)
{
	int64_t resid;
	int result;
	
	result = vn_rdwr_64(rw,
			vp,
			(uint64_t)(uintptr_t)base,
			(int64_t)len,
			offset,
			segflg,
			ioflg,
			cred,
			&resid,
			p);

	/* "resid" should be bounded above by "len," which is an int */
	if (aresid != NULL) {
		*aresid = resid;
	}

	return result;
}