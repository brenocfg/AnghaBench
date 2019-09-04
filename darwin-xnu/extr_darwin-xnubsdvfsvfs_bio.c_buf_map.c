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
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  errno_t ;
typedef  int /*<<< orphan*/ * caddr_t ;
typedef  TYPE_1__* buf_t ;
struct TYPE_3__ {int b_flags; scalar_t__ b_uploffset; int /*<<< orphan*/  b_upl; scalar_t__ b_datap; scalar_t__ b_real_bp; } ;

/* Variables and functions */
 int B_CLUSTER ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ ubc_upl_map (int /*<<< orphan*/ ,scalar_t__*) ; 

errno_t
buf_map(buf_t bp, caddr_t *io_addr)
{
        buf_t		real_bp;
        vm_offset_t	vaddr;
        kern_return_t	kret;

        if ( !(bp->b_flags & B_CLUSTER)) {
	        *io_addr = (caddr_t)bp->b_datap;
		return (0);
	}
	real_bp = (buf_t)(bp->b_real_bp);

	if (real_bp && real_bp->b_datap) {
	        /*
		 * b_real_bp is only valid if B_CLUSTER is SET
		 * if it's non-zero, than someone did a cluster_bp call
		 * if the backing physical pages were already mapped
		 * in before the call to cluster_bp (non-zero b_datap),
		 * than we just use that mapping
		 */
	        *io_addr = (caddr_t)real_bp->b_datap;
		return (0);
	}
	kret = ubc_upl_map(bp->b_upl, &vaddr);    /* Map it in */

	if (kret != KERN_SUCCESS) {
	        *io_addr = NULL;

	        return(ENOMEM);
	}
	vaddr += bp->b_uploffset;                                       

	*io_addr = (caddr_t)vaddr;

	return (0);
}