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
typedef  struct vnode* vnode_t ;
struct vnode {struct ubc_info* v_ubcinfo; } ;
struct ubc_info {TYPE_1__* cs_blobs; } ;
struct fileglob {scalar_t__ fg_data; } ;
struct TYPE_2__ {unsigned int csb_signer_type; } ;

/* Variables and functions */
 unsigned int CS_SIGNER_TYPE_UNKNOWN ; 
 scalar_t__ DTYPE_VNODE ; 
 scalar_t__ FILEGLOB_DTYPE (struct fileglob*) ; 
 int /*<<< orphan*/  UBCINFOEXISTS (struct vnode*) ; 
 int /*<<< orphan*/  vnode_lock (struct vnode*) ; 
 int /*<<< orphan*/  vnode_unlock (struct vnode*) ; 

unsigned int
csfg_get_signer_type(struct fileglob *fg)
{
	struct ubc_info *uip;
	unsigned int signer_type = CS_SIGNER_TYPE_UNKNOWN;
	vnode_t vp;

	if (FILEGLOB_DTYPE(fg) != DTYPE_VNODE)
		return CS_SIGNER_TYPE_UNKNOWN;
	
	vp = (struct vnode *)fg->fg_data;
	if (vp == NULL)
		return CS_SIGNER_TYPE_UNKNOWN;

	vnode_lock(vp);
	if (!UBCINFOEXISTS(vp))
		goto out;
	
	uip = vp->v_ubcinfo;
	if (uip == NULL)
		goto out;
	
	if (uip->cs_blobs == NULL)
		goto out;

	/* It is OK to extract the signer type from the first blob,
	   because all blobs of a vnode must have the same signer type. */	
	signer_type = uip->cs_blobs->csb_signer_type;
out:
	vnode_unlock(vp);

	return signer_type;
}