#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user_ssize_t ;
typedef  TYPE_1__* uio_t ;
struct TYPE_3__ {int /*<<< orphan*/  uio_resid_64; } ;

/* Variables and functions */

user_ssize_t uio_resid( uio_t a_uio )
{
#if DEBUG
	if (a_uio == NULL) {
		printf("%s :%d - invalid uio_t\n", __FILE__, __LINE__); 
	}
/* 	if (IS_VALID_UIO_SEGFLG(a_uio->uio_segflg) == 0) { */
/* 		panic("%s :%d - invalid uio_segflg\n", __FILE__, __LINE__);  */
/* 	} */
#endif /* DEBUG */

	/* return 0 if there are no active iovecs */
	if (a_uio == NULL) {
		return( 0 );
	}

	return( a_uio->uio_resid_64 );
}