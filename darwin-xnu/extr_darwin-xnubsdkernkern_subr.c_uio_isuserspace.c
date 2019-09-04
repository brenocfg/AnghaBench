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
typedef  TYPE_1__* uio_t ;
struct TYPE_3__ {int /*<<< orphan*/  uio_segflg; } ;

/* Variables and functions */
 scalar_t__ UIO_SEG_IS_USER_SPACE (int /*<<< orphan*/ ) ; 

int uio_isuserspace( uio_t a_uio )
{
	if (a_uio == NULL) {
#if LP64_DEBUG
		panic("%s :%d - invalid uio_t\n", __FILE__, __LINE__); 
#endif /* LP64_DEBUG */
		return(0);
	}

	if (UIO_SEG_IS_USER_SPACE(a_uio->uio_segflg)) {
		return( 1 );
	}
	return( 0 );
}