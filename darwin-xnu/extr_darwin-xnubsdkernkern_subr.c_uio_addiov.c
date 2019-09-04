#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ user_size_t ;
typedef  scalar_t__ user_addr_t ;
typedef  TYPE_4__* uio_t ;
typedef  void* u_int64_t ;
struct TYPE_9__ {TYPE_2__* kiovp; TYPE_1__* uiovp; } ;
struct TYPE_10__ {int uio_max_iovs; int /*<<< orphan*/  uio_resid_64; int /*<<< orphan*/  uio_iovcnt; TYPE_3__ uio_iovs; } ;
struct TYPE_8__ {scalar_t__ iov_len; scalar_t__ iov_base; } ;
struct TYPE_7__ {scalar_t__ iov_len; scalar_t__ iov_base; } ;

/* Variables and functions */
 scalar_t__ UIO_IS_USER_SPACE (TYPE_4__*) ; 

int uio_addiov( uio_t a_uio, user_addr_t a_baseaddr, user_size_t a_length )
{
	int			i;
	
	if (a_uio == NULL) {
#if DEBUG
		panic("%s :%d - invalid uio_t\n", __FILE__, __LINE__); 
#endif /* LP64_DEBUG */
		return(-1);
	}

	if (UIO_IS_USER_SPACE(a_uio)) {
		for ( i = 0; i < a_uio->uio_max_iovs; i++ ) {
			if (a_uio->uio_iovs.uiovp[i].iov_len == 0 && a_uio->uio_iovs.uiovp[i].iov_base == 0) {
				a_uio->uio_iovs.uiovp[i].iov_len = a_length;
				a_uio->uio_iovs.uiovp[i].iov_base = a_baseaddr;
				a_uio->uio_iovcnt++;
				a_uio->uio_resid_64 += a_length;
				return( 0 );
			}
		}
	}
	else {
		for ( i = 0; i < a_uio->uio_max_iovs; i++ ) {
			if (a_uio->uio_iovs.kiovp[i].iov_len == 0 && a_uio->uio_iovs.kiovp[i].iov_base == 0) {
				a_uio->uio_iovs.kiovp[i].iov_len = (u_int64_t)a_length;
				a_uio->uio_iovs.kiovp[i].iov_base = (u_int64_t)a_baseaddr;
				a_uio->uio_iovcnt++;
				a_uio->uio_resid_64 += a_length;
				return( 0 );
			}
		}
	}

	return( -1 );
}