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
 int /*<<< orphan*/  BLK_READ ; 
 int /*<<< orphan*/  do_breadn_for_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

errno_t
buf_breadn(vnode_t vp, daddr64_t blkno, int size, daddr64_t *rablks, int *rasizes, int nrablks, kauth_cred_t cred, buf_t *bpp)
{
	return (do_breadn_for_type(vp, blkno, size, rablks, rasizes, nrablks, cred, bpp, BLK_READ));
}