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
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  errno_t ;
typedef  TYPE_1__* buf_t ;
struct TYPE_3__ {int b_flags; int b_lflags; int /*<<< orphan*/  b_upl; scalar_t__ b_datap; scalar_t__ b_real_bp; } ;

/* Variables and functions */
 int BL_IOBUF ; 
 int B_AGE ; 
 int B_CLUSTER ; 
 int B_PAGEIO ; 
 int B_READ ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ ubc_upl_unmap (int /*<<< orphan*/ ) ; 

errno_t
buf_unmap(buf_t bp)
{
        buf_t		real_bp;
        kern_return_t	kret;

        if ( !(bp->b_flags & B_CLUSTER))
	        return (0);
	/*
	 * see buf_map for the explanation
	 */
	real_bp = (buf_t)(bp->b_real_bp);

	if (real_bp && real_bp->b_datap)
	        return (0);

	if ((bp->b_lflags & BL_IOBUF) &&
	    ((bp->b_flags & (B_PAGEIO | B_READ)) != (B_PAGEIO | B_READ))) {
	        /*
		 * ignore pageins... the 'right' thing will
		 * happen due to the way we handle speculative
		 * clusters...
		 *
		 * when we commit these pages, we'll hit
		 * it with UPL_COMMIT_INACTIVE which
		 * will clear the reference bit that got
		 * turned on when we touched the mapping
		 */
	        bp->b_flags |= B_AGE;
	}
	kret = ubc_upl_unmap(bp->b_upl);

	if (kret != KERN_SUCCESS)
	        return (EINVAL);
	return (0);
}