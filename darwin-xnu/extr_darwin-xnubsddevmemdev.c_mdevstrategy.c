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
typedef  int vm_offset_t ;
struct buf {int dummy; } ;
typedef  scalar_t__ ppnum_t ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int addr64_t ;
struct TYPE_2__ {int mdFlags; int mdSecsize; int mdSize; int mdBase; } ;

/* Variables and functions */
 int B_READ ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  bcopy (void*,void*,size_t) ; 
 int /*<<< orphan*/  bcopy_phys (int,int,unsigned int) ; 
 int /*<<< orphan*/  buf_biodone (struct buf*) ; 
 int buf_blkno (struct buf*) ; 
 int buf_count (struct buf*) ; 
 int /*<<< orphan*/  buf_device (struct buf*) ; 
 int buf_flags (struct buf*) ; 
 scalar_t__ buf_map (struct buf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf_setcount (struct buf*,int) ; 
 int /*<<< orphan*/  buf_seterror (struct buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_setresid (struct buf*,int) ; 
 int /*<<< orphan*/  buf_unmap (struct buf*) ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  mapping_set_mod (int) ; 
 int mdInited ; 
 int mdPhys ; 
 TYPE_1__* mdev ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int minor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 scalar_t__ pmap_find_phys (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mdevstrategy(struct buf *bp) {
	unsigned int left, lop, csize;
	vm_offset_t vaddr, blkoff;
	int devid;
	addr64_t paddr, fvaddr;
	ppnum_t pp;

	devid = minor(buf_device(bp));							/* Get minor device number */

	if ((mdev[devid].mdFlags & mdInited) == 0) {		/* Have we actually been defined yet? */
	        buf_seterror(bp, ENXIO);
		buf_biodone(bp);
		return;
	}

	buf_setresid(bp, buf_count(bp));						/* Set byte count */
	
	blkoff = buf_blkno(bp) * mdev[devid].mdSecsize;		/* Get offset into file */

/*
 *	Note that reading past end is an error, but reading at end is an EOF.  For these
 *	we just return with resid == count.
 */

	if (blkoff >= (mdev[devid].mdSize << 12)) {			/* Are they trying to read/write at/after end? */
		if(blkoff != (mdev[devid].mdSize << 12)) {		/* Are we trying to read after EOF? */
		        buf_seterror(bp, EINVAL);						/* Yeah, this is an error */
		}
		buf_biodone(bp);								/* Return */
		return;
	}

	if ((blkoff + buf_count(bp)) > (mdev[devid].mdSize << 12)) {		/* Will this read go past end? */
		buf_setcount(bp, ((mdev[devid].mdSize << 12) - blkoff));	/* Yes, trim to max */
	}
	/*
	 * make sure the buffer's data area is
	 * accessible
	 */
	if (buf_map(bp, (caddr_t *)&vaddr))
	        panic("ramstrategy: buf_map failed\n");

	fvaddr = (mdev[devid].mdBase << 12) + blkoff;		/* Point to offset into ram disk */
	
	if (buf_flags(bp) & B_READ) {					/* Is this a read? */
		if(!(mdev[devid].mdFlags & mdPhys)) {			/* Physical mapped disk? */
			bcopy((void *)((uintptr_t)fvaddr),
				(void *)vaddr, (size_t)buf_count(bp));	/* This is virtual, just get the data */
		}
		else {
			left = buf_count(bp);						/* Init the amount left to copy */
			while(left) {								/* Go until it is all copied */
				
				lop = min((4096 - (vaddr & 4095)), (4096 - (fvaddr & 4095)));	/* Get smallest amount left on sink and source */
				csize = min(lop, left);					/* Don't move more than we need to */
				
				pp = pmap_find_phys(kernel_pmap, (addr64_t)((uintptr_t)vaddr));	/* Get the sink physical address */
				if(!pp) {								/* Not found, what gives? */
					panic("mdevstrategy: sink address %016llX not mapped\n", (addr64_t)((uintptr_t)vaddr));
				}
				paddr = (addr64_t)(((addr64_t)pp << 12) | (addr64_t)(vaddr & 4095));	/* Get actual address */
				bcopy_phys(fvaddr, paddr, csize);		/* Copy this on in */
				mapping_set_mod(paddr >> 12);			/* Make sure we know that it is modified */
				
				left = left - csize;					/* Calculate what is left */
				vaddr = vaddr + csize;					/* Move to next sink address */
				fvaddr = fvaddr + csize;				/* Bump to next physical address */
			}
		}
	}
	else {												/* This is a write */
		if(!(mdev[devid].mdFlags & mdPhys)) {			/* Physical mapped disk? */
			bcopy((void *)vaddr, (void *)((uintptr_t)fvaddr),
				(size_t)buf_count(bp));		/* This is virtual, just put the data */
		}
		else {
			left = buf_count(bp);						/* Init the amount left to copy */
			while(left) {								/* Go until it is all copied */
				
				lop = min((4096 - (vaddr & 4095)), (4096 - (fvaddr & 4095)));	/* Get smallest amount left on sink and source */
				csize = min(lop, left);					/* Don't move more than we need to */
				
				pp = pmap_find_phys(kernel_pmap, (addr64_t)((uintptr_t)vaddr));	/* Get the source physical address */
				if(!pp) {								/* Not found, what gives? */
					panic("mdevstrategy: source address %016llX not mapped\n", (addr64_t)((uintptr_t)vaddr));
				}
				paddr = (addr64_t)(((addr64_t)pp << 12) | (addr64_t)(vaddr & 4095));	/* Get actual address */
			
				bcopy_phys(paddr, fvaddr, csize);		/* Move this on out */
				
				left = left - csize;					/* Calculate what is left */
				vaddr = vaddr + csize;					/* Move to next sink address */
				fvaddr = fvaddr + csize;				/* Bump to next physical address */
			}
		}
	}
	/*
	 * buf_unmap takes care of all the cases
	 * it will unmap the buffer from kernel
	 * virtual space if that was the state
	 * when we mapped it.
	 */
	buf_unmap(bp);

	buf_setresid(bp, 0);									/* Nothing more to do */	
	buf_biodone(bp);									/* Say we've finished */
}