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
typedef  int /*<<< orphan*/  upl_t ;
typedef  int /*<<< orphan*/  upl_page_info_t ;
struct uio {int uio_segflg; scalar_t__ uio_rw; scalar_t__ uio_offset; } ;
typedef  int addr64_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FSRW ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 scalar_t__ FALSE ; 
 int FSDBG_CODE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KERNEL_DEBUG (int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  TASK_WRITE_DEFERRED ; 
 int UIO_PHYS_SYSSPACE ; 
 int UIO_PHYS_USERSPACE ; 
 int UIO_PHYS_USERSPACE32 ; 
 int UIO_PHYS_USERSPACE64 ; 
#define  UIO_SYSSPACE 134 
#define  UIO_USERISPACE 133 
#define  UIO_USERISPACE32 132 
#define  UIO_USERISPACE64 131 
#define  UIO_USERSPACE 130 
#define  UIO_USERSPACE32 129 
#define  UIO_USERSPACE64 128 
 scalar_t__ UIO_WRITE ; 
 int /*<<< orphan*/  current_task () ; 
 int min (int,int) ; 
 int /*<<< orphan*/  task_update_logical_writes (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ubc_upl_pageinfo (int /*<<< orphan*/ ) ; 
 int uiomove64 (int,int,struct uio*) ; 
 scalar_t__ upl_dirty_page (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  upl_lookup_vnode (int /*<<< orphan*/ ) ; 
 scalar_t__ upl_phys_page (int /*<<< orphan*/ *,int) ; 

int
cluster_copy_upl_data(struct uio *uio, upl_t upl, int upl_offset, int *io_resid)
{
        int       pg_offset;
	int       pg_index;
        int   	  csize;
	int       segflg;
	int       retval = 0;
	int	  xsize;
	upl_page_info_t *pl;
	int 	  dirty_count;

	xsize = *io_resid;

	KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 34)) | DBG_FUNC_START,
		     (int)uio->uio_offset, upl_offset, xsize, 0, 0);

	segflg = uio->uio_segflg;

	switch(segflg) {

	  case UIO_USERSPACE32:
	  case UIO_USERISPACE32:
		uio->uio_segflg = UIO_PHYS_USERSPACE32;
		break;

	  case UIO_USERSPACE:
	  case UIO_USERISPACE:
		uio->uio_segflg = UIO_PHYS_USERSPACE;
		break;

	  case UIO_USERSPACE64:
	  case UIO_USERISPACE64:
		uio->uio_segflg = UIO_PHYS_USERSPACE64;
		break;

	  case UIO_SYSSPACE:
		uio->uio_segflg = UIO_PHYS_SYSSPACE;
		break;

	}
	pl = ubc_upl_pageinfo(upl);

	pg_index  = upl_offset / PAGE_SIZE;
	pg_offset = upl_offset & PAGE_MASK;
	csize     = min(PAGE_SIZE - pg_offset, xsize);

	dirty_count = 0;
	while (xsize && retval == 0) {
	        addr64_t  paddr;

		paddr = ((addr64_t)upl_phys_page(pl, pg_index) << PAGE_SHIFT) + pg_offset;
		if ((uio->uio_rw == UIO_WRITE) && (upl_dirty_page(pl, pg_index) == FALSE)) 
			dirty_count++;

		retval = uiomove64(paddr, csize, uio);

		pg_index += 1;
		pg_offset = 0;
		xsize    -= csize;
		csize     = min(PAGE_SIZE, xsize);
	}
	*io_resid = xsize;

	uio->uio_segflg = segflg;

	task_update_logical_writes(current_task(), (dirty_count * PAGE_SIZE), TASK_WRITE_DEFERRED, upl_lookup_vnode(upl));
	KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 34)) | DBG_FUNC_END,
		     (int)uio->uio_offset, xsize, retval, segflg, 0);
	
	return (retval);
}