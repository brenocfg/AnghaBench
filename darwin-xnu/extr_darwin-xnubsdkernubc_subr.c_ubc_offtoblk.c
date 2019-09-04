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
typedef  int /*<<< orphan*/  off_t ;
typedef  int daddr64_t ;

/* Variables and functions */
 scalar_t__ UBCINFOEXISTS (int /*<<< orphan*/ ) ; 
 int VNOP_OFFTOBLK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

daddr64_t
ubc_offtoblk(vnode_t vp, off_t offset)
{
	daddr64_t blkno = -1;
	int error = 0;

	if (UBCINFOEXISTS(vp)) {
		error = VNOP_OFFTOBLK(vp, offset, &blkno);
		if (error)
			blkno = -1;
	}

	return (blkno);
}