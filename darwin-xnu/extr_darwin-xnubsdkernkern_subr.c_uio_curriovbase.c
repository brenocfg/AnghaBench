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
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  TYPE_4__* uio_t ;
struct TYPE_9__ {TYPE_2__* kiovp; TYPE_1__* uiovp; } ;
struct TYPE_10__ {int uio_iovcnt; TYPE_3__ uio_iovs; } ;
struct TYPE_8__ {scalar_t__ iov_base; } ;
struct TYPE_7__ {int /*<<< orphan*/  iov_base; } ;

/* Variables and functions */
 scalar_t__ UIO_IS_USER_SPACE (TYPE_4__*) ; 

user_addr_t uio_curriovbase( uio_t a_uio )
{
#if LP64_DEBUG
	if (a_uio == NULL) {
		panic("%s :%d - invalid uio_t\n", __FILE__, __LINE__); 
	}
#endif /* LP64_DEBUG */

	if (a_uio == NULL || a_uio->uio_iovcnt < 1) {
		return(0);
	}
	
	if (UIO_IS_USER_SPACE(a_uio)) {
		return(a_uio->uio_iovs.uiovp->iov_base);
	}
	return((user_addr_t)a_uio->uio_iovs.kiovp->iov_base);
	
}