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
typedef  TYPE_4__* uio_t ;
struct TYPE_9__ {TYPE_2__* kiovp; TYPE_1__* uiovp; } ;
struct TYPE_10__ {int uio_iovcnt; scalar_t__ uio_resid_64; TYPE_3__ uio_iovs; int /*<<< orphan*/  uio_offset; } ;
struct TYPE_8__ {scalar_t__ iov_len; int /*<<< orphan*/  iov_base; } ;
struct TYPE_7__ {scalar_t__ iov_len; int /*<<< orphan*/  iov_base; } ;

/* Variables and functions */
 scalar_t__ UIO_IS_USER_SPACE (TYPE_4__*) ; 

void uio_update( uio_t a_uio, user_size_t a_count )
{
#if LP64_DEBUG
	if (a_uio == NULL) {
		panic("%s :%d - invalid uio_t\n", __FILE__, __LINE__); 
	}
	if (UIO_IS_32_BIT_SPACE(a_uio) && a_count > 0xFFFFFFFFull) {
		panic("%s :%d - invalid count value \n", __FILE__, __LINE__); 
	}
#endif /* LP64_DEBUG */

	if (a_uio == NULL || a_uio->uio_iovcnt < 1) {
		return;
	}

	if (UIO_IS_USER_SPACE(a_uio)) {
	        /*
		 * if a_count == 0, then we are asking to skip over
		 * any empty iovs
		 */
	        if (a_count) {
		        if (a_count > a_uio->uio_iovs.uiovp->iov_len) {
			        a_uio->uio_iovs.uiovp->iov_base += a_uio->uio_iovs.uiovp->iov_len;
				a_uio->uio_iovs.uiovp->iov_len = 0;
			}
			else {
				a_uio->uio_iovs.uiovp->iov_base += a_count;
				a_uio->uio_iovs.uiovp->iov_len -= a_count;
			}
			if (a_count > (user_size_t)a_uio->uio_resid_64) {
				a_uio->uio_offset += a_uio->uio_resid_64;
				a_uio->uio_resid_64 = 0;
			}
			else {
				a_uio->uio_offset += a_count;
				a_uio->uio_resid_64 -= a_count;
			}
		}
		/*
		 * advance to next iovec if current one is totally consumed
		 */
		while (a_uio->uio_iovcnt > 0 && a_uio->uio_iovs.uiovp->iov_len == 0) {
			a_uio->uio_iovcnt--;
			if (a_uio->uio_iovcnt > 0) {
				a_uio->uio_iovs.uiovp++;
			}
		}
	}
	else {
	        /*
		 * if a_count == 0, then we are asking to skip over
		 * any empty iovs
		 */
	        if (a_count) {
		        if (a_count > a_uio->uio_iovs.kiovp->iov_len) {
			        a_uio->uio_iovs.kiovp->iov_base += a_uio->uio_iovs.kiovp->iov_len;
				a_uio->uio_iovs.kiovp->iov_len = 0;
			}
			else {
			        a_uio->uio_iovs.kiovp->iov_base += a_count;
				a_uio->uio_iovs.kiovp->iov_len -= a_count;
			}
			if (a_count > (user_size_t)a_uio->uio_resid_64) {
				a_uio->uio_offset += a_uio->uio_resid_64;
				a_uio->uio_resid_64 = 0;
			}
			else {
				a_uio->uio_offset += a_count;
				a_uio->uio_resid_64 -= a_count;
			}
		}
		/*
		 * advance to next iovec if current one is totally consumed
		 */
		while (a_uio->uio_iovcnt > 0 && a_uio->uio_iovs.kiovp->iov_len == 0) {
			a_uio->uio_iovcnt--;
			if (a_uio->uio_iovcnt > 0) {
				a_uio->uio_iovs.kiovp++;
			}
		}
	}
	return;
}