#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* uio_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct user_iovec {scalar_t__ iov_len; } ;
struct uio {int dummy; } ;
struct TYPE_8__ {TYPE_1__* kiovp; struct user_iovec* uiovp; } ;
struct TYPE_9__ {int uio_max_iovs; scalar_t__ uio_iovcnt; int uio_flags; TYPE_2__ uio_iovs; int /*<<< orphan*/  uio_size; } ;
struct TYPE_7__ {scalar_t__ iov_len; } ;

/* Variables and functions */
 int UIO_FLAGS_INITED ; 
 int UIO_FLAGS_WE_ALLOCED ; 
 scalar_t__ UIO_IS_USER_SPACE (TYPE_3__*) ; 
 int /*<<< orphan*/  bcopy (void*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ kalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,char*,int) ; 

uio_t uio_duplicate( uio_t a_uio )
{
	uio_t		my_uio;
	int			i;

	if (a_uio == NULL) {
		return(NULL);
	}
	
	my_uio = (uio_t) kalloc(a_uio->uio_size);
	if (my_uio == 0) {
		panic("%s :%d - allocation failed\n", __FILE__, __LINE__); 
	}
	
	bcopy((void *)a_uio, (void *)my_uio, a_uio->uio_size);
	/* need to set our iovec pointer to point to first active iovec */
	if (my_uio->uio_max_iovs > 0) {
		my_uio->uio_iovs.uiovp = (struct user_iovec *)
			(((uint8_t *)my_uio) + sizeof(struct uio));

		/* advance to first nonzero iovec */
		if (my_uio->uio_iovcnt > 0) {
			for ( i = 0; i < my_uio->uio_max_iovs; i++ ) {
				if (UIO_IS_USER_SPACE(a_uio)) {
					if (my_uio->uio_iovs.uiovp->iov_len != 0) {
						break;
					}
					my_uio->uio_iovs.uiovp++;
				}
				else {
					if (my_uio->uio_iovs.kiovp->iov_len != 0) {
						break;
					}
					my_uio->uio_iovs.kiovp++;
				}
			}
		}
	}

	my_uio->uio_flags = UIO_FLAGS_WE_ALLOCED | UIO_FLAGS_INITED;
#if DEBUG
		(void)hw_atomic_add(&uio_t_count, 1);
#endif


	return(my_uio);
}