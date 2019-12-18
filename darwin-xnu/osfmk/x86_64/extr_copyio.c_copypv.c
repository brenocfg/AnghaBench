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
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int addr64_t ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  KERNEL_DEBUG (int,unsigned int,unsigned int,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  bcopy_phys (int,int,unsigned int) ; 
 scalar_t__ copyio_phys (int,int,unsigned int,int) ; 
 int cppvFsnk ; 
 int cppvFsrc ; 
 int cppvPsnk ; 
 int cppvPsrc ; 
 int /*<<< orphan*/  flush_dcache64 (int,unsigned int,int) ; 
 int /*<<< orphan*/  panic (char*) ; 

kern_return_t
copypv(addr64_t src64, addr64_t snk64, unsigned int size, int which)
{
	unsigned int lop, csize;
	int bothphys = 0;
	
	KERNEL_DEBUG(0xeff7004c | DBG_FUNC_START, (unsigned)src64,
		     (unsigned)snk64, size, which, 0);

	if ((which & (cppvPsrc | cppvPsnk)) == 0 )				/* Make sure that only one is virtual */
		panic("copypv: no more than 1 parameter may be virtual\n");	/* Not allowed */

	if ((which & (cppvPsrc | cppvPsnk)) == (cppvPsrc | cppvPsnk))
	        bothphys = 1;							/* both are physical */

	while (size) {
	  
	        if (bothphys) {
		        lop = (unsigned int)(PAGE_SIZE - (snk64 & (PAGE_SIZE - 1)));		/* Assume sink smallest */

			if (lop > (unsigned int)(PAGE_SIZE - (src64 & (PAGE_SIZE - 1))))
			        lop = (unsigned int)(PAGE_SIZE - (src64 & (PAGE_SIZE - 1)));	/* No, source is smaller */
		} else {
		        /*
			 * only need to compute the resid for the physical page
			 * address... we don't care about where we start/finish in
			 * the virtual since we just call the normal copyin/copyout
			 */
		        if (which & cppvPsrc)
			        lop = (unsigned int)(PAGE_SIZE - (src64 & (PAGE_SIZE - 1)));
			else
			        lop = (unsigned int)(PAGE_SIZE - (snk64 & (PAGE_SIZE - 1)));
		}
		csize = size;						/* Assume we can copy it all */
		if (lop < size)
		        csize = lop;					/* Nope, we can't do it all */
#if 0		
		/*
		 * flush_dcache64 is currently a nop on the i386... 
		 * it's used when copying to non-system memory such
		 * as video capture cards... on PPC there was a need
		 * to flush due to how we mapped this memory... not
		 * sure if it's needed on i386.
		 */
		if (which & cppvFsrc)
		        flush_dcache64(src64, csize, 1);		/* If requested, flush source before move */
		if (which & cppvFsnk)
		        flush_dcache64(snk64, csize, 1);		/* If requested, flush sink before move */
#endif
		if (bothphys)
		        bcopy_phys(src64, snk64, csize);		/* Do a physical copy, virtually */
		else {
		        if (copyio_phys(src64, snk64, csize, which))
			        return (KERN_FAILURE);
		}
#if 0
		if (which & cppvFsrc)
		        flush_dcache64(src64, csize, 1);	/* If requested, flush source after move */
		if (which & cppvFsnk)
		        flush_dcache64(snk64, csize, 1);	/* If requested, flush sink after move */
#endif
		size   -= csize;					/* Calculate what is left */
		snk64 += csize;					/* Bump sink to next physical address */
		src64 += csize;					/* Bump source to next physical address */
	}
	KERNEL_DEBUG(0xeff7004c | DBG_FUNC_END, (unsigned)src64,
		     (unsigned)snk64, size, which, 0);

	return KERN_SUCCESS;
}