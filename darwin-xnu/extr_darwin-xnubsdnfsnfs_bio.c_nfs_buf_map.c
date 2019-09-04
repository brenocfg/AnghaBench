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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct nfsbuf {scalar_t__ nb_data; int /*<<< orphan*/  nb_flags; int /*<<< orphan*/  nb_pagelist; } ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FSDBG (int,struct nfsbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  NBOFF (struct nfsbuf*) ; 
 int /*<<< orphan*/  NB_PAGELIST ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 scalar_t__ ubc_upl_map (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
nfs_buf_map(struct nfsbuf *bp)
{
	kern_return_t kret;

	if (bp->nb_data)
		return (0);
	if (!ISSET(bp->nb_flags, NB_PAGELIST))
		return (EINVAL);

	kret = ubc_upl_map(bp->nb_pagelist, (vm_offset_t *)&(bp->nb_data));
	if (kret != KERN_SUCCESS)
		panic("nfs_buf_map: ubc_upl_map() failed with (%d)", kret);
	if (bp->nb_data == 0)
		panic("ubc_upl_map mapped 0");
	FSDBG(540, bp, bp->nb_flags, NBOFF(bp), bp->nb_data);
	return (0);
}