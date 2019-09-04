#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  TYPE_2__* uio_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct user_iovec {int dummy; } ;
struct uio {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_5__ {struct user_iovec* uiovp; } ;
struct TYPE_6__ {int uio_max_iovs; int uio_segflg; int uio_rw; int /*<<< orphan*/  uio_flags; int /*<<< orphan*/  uio_offset; TYPE_1__ uio_iovs; int /*<<< orphan*/  uio_size; } ;

/* Variables and functions */
#define  UIO_PHYS_USERSPACE 130 
 int UIO_PHYS_USERSPACE32 ; 
 int UIO_SYSSPACE ; 
#define  UIO_SYSSPACE32 129 
#define  UIO_USERSPACE 128 
 int UIO_USERSPACE32 ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int /*<<< orphan*/ ) ; 

void uio_reset( uio_t a_uio,
				off_t a_offset,			/* current offset */
				int a_spacetype,		/* type of address space */
				int a_iodirection )		/* read or write flag */
{
	vm_size_t	my_size;
	int			my_max_iovs;
	u_int32_t	my_old_flags;
	
#if LP64_DEBUG
	if (a_uio == NULL) {
		panic("%s :%d - could not allocate uio_t\n", __FILE__, __LINE__); 
	}
	if (!IS_VALID_UIO_SEGFLG(a_spacetype)) {
		panic("%s :%d - invalid address space type\n", __FILE__, __LINE__); 
	}
	if (!(a_iodirection == UIO_READ || a_iodirection == UIO_WRITE)) {
		panic("%s :%d - invalid IO direction flag\n", __FILE__, __LINE__); 
	}
#endif /* LP64_DEBUG */

	if (a_uio == NULL) {
		return;
	}

	my_size = a_uio->uio_size;
	my_old_flags = a_uio->uio_flags;
	my_max_iovs = a_uio->uio_max_iovs;
	bzero(a_uio, my_size);
	a_uio->uio_size = my_size;

	/*
	 * we use uio_segflg to indicate if the uio_t is the new format or
	 * old (pre LP64 support) legacy format
	 * This switch statement should canonicalize incoming space type
	 * to one of UIO_USERSPACE32/64, UIO_PHYS_USERSPACE32/64, or
	 * UIO_SYSSPACE/UIO_PHYS_SYSSPACE
	 */
	switch (a_spacetype) {
	case UIO_USERSPACE:
		a_uio->uio_segflg = UIO_USERSPACE32;
		break;
	case UIO_SYSSPACE32:
		a_uio->uio_segflg = UIO_SYSSPACE;
		break;
	case UIO_PHYS_USERSPACE:
		a_uio->uio_segflg = UIO_PHYS_USERSPACE32;
		break;
	default:
		a_uio->uio_segflg = a_spacetype;
		break;
	}

	if (my_max_iovs > 0) {
		a_uio->uio_iovs.uiovp = (struct user_iovec *)
			(((uint8_t *)a_uio) + sizeof(struct uio));
	}
	else {
		a_uio->uio_iovs.uiovp = NULL;
	}

	a_uio->uio_max_iovs = my_max_iovs;
	a_uio->uio_offset = a_offset;
	a_uio->uio_rw = a_iodirection;
	a_uio->uio_flags = my_old_flags;

	return;
}