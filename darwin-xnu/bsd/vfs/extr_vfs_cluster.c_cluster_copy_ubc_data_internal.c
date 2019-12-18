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
struct uio {int uio_offset; int uio_segflg; } ;
typedef  scalar_t__ memory_object_control_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FSRW ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int FSDBG_CODE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KERNEL_DEBUG (int,int,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ MEMORY_OBJECT_CONTROL_NULL ; 
 int PAGE_MASK_64 ; 
 int /*<<< orphan*/  UBC_FLAGS_NONE ; 
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
 int memory_object_control_uiomove (scalar_t__,int,struct uio*,int,int,int,int) ; 
 scalar_t__ ubc_getobject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uio_resid (struct uio*) ; 

__attribute__((used)) static int
cluster_copy_ubc_data_internal(vnode_t vp, struct uio *uio, int *io_resid, int mark_dirty, int take_reference)
{
	int       segflg;
	int       io_size;
	int       xsize;
	int       start_offset;
	int       retval = 0;
	memory_object_control_t	 control;

	io_size = *io_resid;

	KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 34)) | DBG_FUNC_START,
		     (int)uio->uio_offset, io_size, mark_dirty, take_reference, 0);

	control = ubc_getobject(vp, UBC_FLAGS_NONE);

	if (control == MEMORY_OBJECT_CONTROL_NULL) {
		KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 34)) | DBG_FUNC_END,
			     (int)uio->uio_offset, io_size, retval, 3, 0);

		return(0);
	}
	segflg = uio->uio_segflg;

	switch(segflg) {

	  case UIO_USERSPACE32:
	  case UIO_USERISPACE32:
		uio->uio_segflg = UIO_PHYS_USERSPACE32;
		break;

	  case UIO_USERSPACE64:
	  case UIO_USERISPACE64:
		uio->uio_segflg = UIO_PHYS_USERSPACE64;
		break;

	  case UIO_USERSPACE:
	  case UIO_USERISPACE:
		uio->uio_segflg = UIO_PHYS_USERSPACE;
		break;

	  case UIO_SYSSPACE:
		uio->uio_segflg = UIO_PHYS_SYSSPACE;
		break;
	}

	if ( (io_size = *io_resid) ) {
	        start_offset = (int)(uio->uio_offset & PAGE_MASK_64);
		xsize = uio_resid(uio);

		retval = memory_object_control_uiomove(control, uio->uio_offset - start_offset, uio,
						       start_offset, io_size, mark_dirty, take_reference);
		xsize -= uio_resid(uio);
		io_size -= xsize;
	}
	uio->uio_segflg = segflg;
	*io_resid       = io_size;

	KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 34)) | DBG_FUNC_END,
		     (int)uio->uio_offset, io_size, retval, 0x80000000 | segflg, 0);

	return(retval);
}