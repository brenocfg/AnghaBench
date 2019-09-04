#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_6__ {TYPE_2__* kiovp; TYPE_1__* uiovp; } ;
struct uio {TYPE_3__ uio_iovs; int /*<<< orphan*/  uio_rw; scalar_t__ uio_segflg; } ;
typedef  int addr64_t ;
struct TYPE_5__ {int iov_base; } ;
struct TYPE_4__ {int iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_DOWN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DBG_FSRW ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  DBG_UIO_COPYIN ; 
 int /*<<< orphan*/  DBG_UIO_COPYOUT ; 
 int EFAULT ; 
 int FSDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERNEL_DEBUG (int,uintptr_t,int,int,int,int /*<<< orphan*/ ) ; 
#define  UIO_PHYS_SYSSPACE 139 
#define  UIO_PHYS_USERSPACE 138 
#define  UIO_PHYS_USERSPACE32 137 
#define  UIO_PHYS_USERSPACE64 136 
 int /*<<< orphan*/  UIO_READ ; 
#define  UIO_SYSSPACE 135 
#define  UIO_SYSSPACE32 134 
#define  UIO_USERISPACE 133 
#define  UIO_USERISPACE32 132 
#define  UIO_USERISPACE64 131 
#define  UIO_USERSPACE 130 
#define  UIO_USERSPACE32 129 
#define  UIO_USERSPACE64 128 
 int /*<<< orphan*/  caddr_t ; 
 int copyin (int,int /*<<< orphan*/ ,int) ; 
 int copyout (int /*<<< orphan*/ ,int,int) ; 
 int copypv (int,int,int,int) ; 
 int copywithin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int cppvKmap ; 
 int cppvNoModSnk ; 
 int cppvNoRefSrc ; 
 int cppvPsnk ; 
 int cppvPsrc ; 
 int uio_curriovlen (struct uio*) ; 
 scalar_t__ uio_resid (struct uio*) ; 
 int /*<<< orphan*/  uio_update (struct uio*,int) ; 

int
uiomove64(const addr64_t c_cp, int n, struct uio *uio)
{
	addr64_t cp = c_cp;
	uint64_t acnt;
	int error = 0;

#if DIAGNOSTIC
	if (uio->uio_rw != UIO_READ && uio->uio_rw != UIO_WRITE)
		panic("uiomove: mode");
#endif

#if LP64_DEBUG
	if (IS_VALID_UIO_SEGFLG(uio->uio_segflg) == 0) {
		panic("%s :%d - invalid uio_segflg\n", __FILE__, __LINE__); 
	}
#endif /* LP64_DEBUG */

	while (n > 0 && uio_resid(uio)) {
		uio_update(uio, 0);
		acnt = uio_curriovlen(uio);
		if (acnt == 0) {
			continue;
		}
		if (n > 0 && acnt > (uint64_t)n)
			acnt = n;

		switch ((int) uio->uio_segflg) {

		case UIO_USERSPACE64:
		case UIO_USERISPACE64:
		case UIO_USERSPACE32:
		case UIO_USERISPACE32:
		case UIO_USERSPACE:
		case UIO_USERISPACE:
			// LP64 - 3rd argument in debug code is 64 bit, expected to be 32 bit
			if (uio->uio_rw == UIO_READ)
			  {
			        KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, DBG_UIO_COPYOUT)) | DBG_FUNC_START,
					 (int)cp, (uintptr_t)uio->uio_iovs.uiovp->iov_base, acnt, 0,0);

					error = copyout( CAST_DOWN(caddr_t, cp), uio->uio_iovs.uiovp->iov_base, acnt );

			        KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, DBG_UIO_COPYOUT)) | DBG_FUNC_END,
					 (int)cp, (uintptr_t)uio->uio_iovs.uiovp->iov_base, acnt, 0,0);
			  }
			else
			  {
			        KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, DBG_UIO_COPYIN)) | DBG_FUNC_START,
					 (uintptr_t)uio->uio_iovs.uiovp->iov_base, (int)cp, acnt, 0,0);

			        error = copyin(uio->uio_iovs.uiovp->iov_base, CAST_DOWN(caddr_t, cp), acnt);

			        KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, DBG_UIO_COPYIN)) | DBG_FUNC_END,
					 (uintptr_t)uio->uio_iovs.uiovp->iov_base, (int)cp, acnt, 0,0);
			  }
			if (error)
				return (error);
			break;

		case UIO_SYSSPACE32:
		case UIO_SYSSPACE:
			if (uio->uio_rw == UIO_READ)
				error = copywithin(CAST_DOWN(caddr_t, cp), CAST_DOWN(caddr_t, uio->uio_iovs.kiovp->iov_base),
						   acnt);
			else
				error = copywithin(CAST_DOWN(caddr_t, uio->uio_iovs.kiovp->iov_base), CAST_DOWN(caddr_t, cp),
						   acnt);
			break;

		case UIO_PHYS_USERSPACE64:
		case UIO_PHYS_USERSPACE32:
		case UIO_PHYS_USERSPACE:
			if (uio->uio_rw == UIO_READ)
			  {
			        KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, DBG_UIO_COPYOUT)) | DBG_FUNC_START,
					 (int)cp, (uintptr_t)uio->uio_iovs.uiovp->iov_base, acnt, 1,0);

				error = copypv((addr64_t)cp, uio->uio_iovs.uiovp->iov_base, acnt, cppvPsrc | cppvNoRefSrc);
				if (error) 	/* Copy physical to virtual */
				        error = EFAULT;

			        KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, DBG_UIO_COPYOUT)) | DBG_FUNC_END,
					 (int)cp, (uintptr_t)uio->uio_iovs.uiovp->iov_base, acnt, 1,0);
			  }
			else
			  {
			        KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, DBG_UIO_COPYIN)) | DBG_FUNC_START,
					 (uintptr_t)uio->uio_iovs.uiovp->iov_base, (int)cp, acnt, 1,0);

				error = copypv(uio->uio_iovs.uiovp->iov_base, (addr64_t)cp, acnt, cppvPsnk | cppvNoRefSrc | cppvNoModSnk);
				if (error)	/* Copy virtual to physical */
				        error = EFAULT;

			        KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, DBG_UIO_COPYIN)) | DBG_FUNC_END,
					 (uintptr_t)uio->uio_iovs.uiovp->iov_base, (int)cp, acnt, 1,0);
			  }
			if (error)
				return (error);
			break;

		case UIO_PHYS_SYSSPACE:
			if (uio->uio_rw == UIO_READ)
			  {
			        KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, DBG_UIO_COPYOUT)) | DBG_FUNC_START,
					 (int)cp, (uintptr_t)uio->uio_iovs.kiovp->iov_base, acnt, 2,0);

					error = copypv((addr64_t)cp, uio->uio_iovs.kiovp->iov_base, acnt, cppvKmap | cppvPsrc | cppvNoRefSrc);
				if (error) 	/* Copy physical to virtual */
				        error = EFAULT;

			        KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, DBG_UIO_COPYOUT)) | DBG_FUNC_END,
					 (int)cp, (uintptr_t)uio->uio_iovs.kiovp->iov_base, acnt, 2,0);
			  }
			else
			  {
			        KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, DBG_UIO_COPYIN)) | DBG_FUNC_START,
					 (uintptr_t)uio->uio_iovs.kiovp->iov_base, (int)cp, acnt, 2,0);

					error = copypv(uio->uio_iovs.kiovp->iov_base, (addr64_t)cp, acnt, cppvKmap | cppvPsnk | cppvNoRefSrc | cppvNoModSnk);
				if (error)	/* Copy virtual to physical */
				        error = EFAULT;

			        KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, DBG_UIO_COPYIN)) | DBG_FUNC_END,
					 (uintptr_t)uio->uio_iovs.kiovp->iov_base, (int)cp, acnt, 2,0);
			  }
			if (error)
				return (error);
			break;

		default:
			break;
		}
		uio_update(uio, acnt);
		cp += acnt;
		n -= acnt;
	}
	return (error);
}