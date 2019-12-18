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
typedef  int /*<<< orphan*/  user_size_t ;
typedef  int /*<<< orphan*/  upl_t ;
typedef  int /*<<< orphan*/  upl_page_info_t ;
typedef  scalar_t__ u_int32_t ;
struct uio {int uio_offset; } ;
struct clios {int dummy; } ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  buf_t ;
typedef  int addr64_t ;

/* Variables and functions */
 int CL_NOCACHE ; 
 int CL_PASSIVE ; 
 int CL_READ ; 
 int EINVAL ; 
 int IO_NOCACHE ; 
 int IO_PASSIVE ; 
 scalar_t__ KERN_SUCCESS ; 
 int PAGE_MASK_64 ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int UPL_ABORT_DUMP_PAGES ; 
 int UPL_ABORT_FREE_ON_EMPTY ; 
 int UPL_FILE_IO ; 
 int UPL_SET_LITE ; 
 int UPL_WILL_MODIFY ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_FILE ; 
 int cluster_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct clios*,int (*) (buf_t,void*),void*) ; 
 int /*<<< orphan*/  copypv (int,int,scalar_t__,int) ; 
 scalar_t__ ubc_create_upl_kernel (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubc_upl_abort_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uio_update (struct uio*,int /*<<< orphan*/ ) ; 
 scalar_t__ upl_dirty_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ upl_phys_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ upl_valid_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cluster_align_phys_io(vnode_t vp, struct uio *uio, addr64_t usr_paddr, u_int32_t xsize, int flags, int (*callback)(buf_t, void *), void *callback_arg)
{
        upl_page_info_t  *pl;
        upl_t            upl;
        addr64_t	 ubc_paddr;
        kern_return_t    kret;
        int              error = 0;
	int		 did_read = 0;
	int		 abort_flags;
	int		 upl_flags;
	int              bflag;

	if (flags & IO_PASSIVE)
		bflag = CL_PASSIVE;
	else
		bflag = 0;

	if (flags & IO_NOCACHE)
		bflag |= CL_NOCACHE;

	upl_flags = UPL_SET_LITE;

	if ( !(flags & CL_READ) ) {
		/*
		 * "write" operation:  let the UPL subsystem know
		 * that we intend to modify the buffer cache pages
		 * we're gathering.
		 */
		upl_flags |= UPL_WILL_MODIFY;
	} else {
	        /*
		 * indicate that there is no need to pull the
		 * mapping for this page... we're only going
		 * to read from it, not modify it.
		 */
		upl_flags |= UPL_FILE_IO;
	}
        kret = ubc_create_upl_kernel(vp,
                              uio->uio_offset & ~PAGE_MASK_64,
                              PAGE_SIZE,
                              &upl,
                              &pl,
                              upl_flags,
                              VM_KERN_MEMORY_FILE);

        if (kret != KERN_SUCCESS)
                return(EINVAL);

        if (!upl_valid_page(pl, 0)) {
                /*
                 * issue a synchronous read to cluster_io
                 */
                error = cluster_io(vp, upl, 0, uio->uio_offset & ~PAGE_MASK_64, PAGE_SIZE,
				   CL_READ | bflag, (buf_t)NULL, (struct clios *)NULL, callback, callback_arg);
                if (error) {
                          ubc_upl_abort_range(upl, 0, PAGE_SIZE, UPL_ABORT_DUMP_PAGES | UPL_ABORT_FREE_ON_EMPTY);

                          return(error);
                }
		did_read = 1;
        }
        ubc_paddr = ((addr64_t)upl_phys_page(pl, 0) << PAGE_SHIFT) + (addr64_t)(uio->uio_offset & PAGE_MASK_64);

/*
 *	NOTE:  There is no prototype for the following in BSD. It, and the definitions
 *	of the defines for cppvPsrc, cppvPsnk, cppvFsnk, and cppvFsrc will be found in
 *	osfmk/ppc/mappings.h.  They are not included here because there appears to be no
 *	way to do so without exporting them to kexts as well.
 */
	if (flags & CL_READ)
//		copypv(ubc_paddr, usr_paddr, xsize, cppvPsrc | cppvPsnk | cppvFsnk);	/* Copy physical to physical and flush the destination */
		copypv(ubc_paddr, usr_paddr, xsize,        2 |        1 |        4);	/* Copy physical to physical and flush the destination */
	else
//		copypv(usr_paddr, ubc_paddr, xsize, cppvPsrc | cppvPsnk | cppvFsrc);	/* Copy physical to physical and flush the source */
		copypv(usr_paddr, ubc_paddr, xsize,        2 |        1 |        8);	/* Copy physical to physical and flush the source */
	
	if ( !(flags & CL_READ) || (upl_valid_page(pl, 0) && upl_dirty_page(pl, 0))) {
	        /*
		 * issue a synchronous write to cluster_io
		 */
		error = cluster_io(vp, upl, 0, uio->uio_offset & ~PAGE_MASK_64, PAGE_SIZE,
				   bflag, (buf_t)NULL, (struct clios *)NULL, callback, callback_arg);
	}
	if (error == 0) 
	        uio_update(uio, (user_size_t)xsize);

	if (did_read)
	        abort_flags = UPL_ABORT_FREE_ON_EMPTY;
	else
	        abort_flags = UPL_ABORT_FREE_ON_EMPTY | UPL_ABORT_DUMP_PAGES;

	ubc_upl_abort_range(upl, 0, PAGE_SIZE, abort_flags);
	
	return (error);
}