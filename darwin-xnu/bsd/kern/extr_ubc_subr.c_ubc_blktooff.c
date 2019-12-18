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
typedef  int off_t ;
typedef  int /*<<< orphan*/  daddr64_t ;

/* Variables and functions */
 scalar_t__ UBCINFOEXISTS (int /*<<< orphan*/ ) ; 
 int VNOP_BLKTOOFF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

off_t
ubc_blktooff(vnode_t vp, daddr64_t blkno)
{
	off_t file_offset = -1;
	int error;

	if (UBCINFOEXISTS(vp)) {
		error = VNOP_BLKTOOFF(vp, blkno, &file_offset);
		if (error)
			file_offset = -1;
	}

	return (file_offset);
}