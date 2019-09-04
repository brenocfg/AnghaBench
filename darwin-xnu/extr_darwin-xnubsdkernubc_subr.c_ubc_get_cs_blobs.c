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
struct vnode {struct ubc_info* v_ubcinfo; } ;
struct ubc_info {struct cs_blob* cs_blobs; } ;
struct cs_blob {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UBCINFOEXISTS (struct vnode*) ; 

struct cs_blob *
ubc_get_cs_blobs(
	struct vnode	*vp)
{
	struct ubc_info	*uip;
	struct cs_blob	*blobs;

	/*
	 * No need to take the vnode lock here.  The caller must be holding
	 * a reference on the vnode (via a VM mapping or open file descriptor),
	 * so the vnode will not go away.  The ubc_info stays until the vnode
	 * goes away.  And we only modify "blobs" by adding to the head of the
	 * list.
	 * The ubc_info could go away entirely if the vnode gets reclaimed as
	 * part of a forced unmount.  In the case of a code-signature validation
	 * during a page fault, the "paging_in_progress" reference on the VM
	 * object guarantess that the vnode pager (and the ubc_info) won't go
	 * away during the fault.
	 * Other callers need to protect against vnode reclaim by holding the
	 * vnode lock, for example.
	 */

	if (! UBCINFOEXISTS(vp)) {
		blobs = NULL;
		goto out;
	}

	uip = vp->v_ubcinfo;
	blobs = uip->cs_blobs;

out:
	return blobs;
}