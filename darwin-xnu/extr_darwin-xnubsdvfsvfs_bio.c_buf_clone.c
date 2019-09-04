#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* buf_t ;
struct TYPE_7__ {int b_bcount; int b_flags; int b_uploffset; void (* b_iodone ) (TYPE_1__*,void*) ;uintptr_t b_datap; int /*<<< orphan*/  b_upl; void* b_transaction; int /*<<< orphan*/  b_vp; } ;

/* Variables and functions */
 int B_ASYNC ; 
 int B_CALL ; 
 int B_CLUSTER ; 
 int B_COMMIT_UPL ; 
 int B_FUA ; 
 int B_META ; 
 int B_PAGEIO ; 
 int B_PHYS ; 
 int B_RAW ; 
 int B_READ ; 
 int PAGE_MASK ; 
 TYPE_1__* alloc_io_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

buf_t
buf_clone(buf_t bp, int io_offset, int io_size, void (*iodone)(buf_t, void *), void *arg)
{
        buf_t	io_bp;

	if (io_offset < 0 || io_size < 0)
	        return (NULL);

	if ((unsigned)(io_offset + io_size) > (unsigned)bp->b_bcount)
	        return (NULL);

	if (bp->b_flags & B_CLUSTER) {
	        if (io_offset && ((bp->b_uploffset + io_offset) & PAGE_MASK))
		        return (NULL);

	        if (((bp->b_uploffset + io_offset + io_size) & PAGE_MASK) && ((io_offset + io_size) < bp->b_bcount))
		        return (NULL);
	}
	io_bp = alloc_io_buf(bp->b_vp, 0);

	io_bp->b_flags = bp->b_flags & (B_COMMIT_UPL | B_META | B_PAGEIO | B_CLUSTER | B_PHYS | B_RAW | B_ASYNC | B_READ | B_FUA);

	if (iodone) {
	        io_bp->b_transaction = arg;
		io_bp->b_iodone = iodone;
		io_bp->b_flags |= B_CALL;
	}
	if (bp->b_flags & B_CLUSTER) {
	        io_bp->b_upl = bp->b_upl;
		io_bp->b_uploffset = bp->b_uploffset + io_offset;
	} else {
	        io_bp->b_datap  = (uintptr_t)(((char *)bp->b_datap) + io_offset);
	}
	io_bp->b_bcount = io_size;

	return (io_bp);
}