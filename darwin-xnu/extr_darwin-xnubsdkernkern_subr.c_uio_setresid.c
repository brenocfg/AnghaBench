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

void uio_setresid( uio_t a_uio, user_ssize_t a_value )
{
#if DEBUG
	if (a_uio == NULL) {
		panic("%s :%d - invalid uio_t\n", __FILE__, __LINE__); 
	}
/* 	if (IS_VALID_UIO_SEGFLG(a_uio->uio_segflg) == 0) { */
/* 		panic("%s :%d - invalid uio_segflg\n", __FILE__, __LINE__);  */
/* 	} */
#endif /* DEBUG */

	if (a_uio == NULL) {
		return;
	}

	a_uio->uio_resid_64 = a_value;
	return;
}