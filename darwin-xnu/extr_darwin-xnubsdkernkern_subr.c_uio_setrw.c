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
struct TYPE_3__ {int uio_rw; } ;

/* Variables and functions */
 int UIO_READ ; 
 int UIO_WRITE ; 

void uio_setrw( uio_t a_uio, int a_value )
{
	if (a_uio == NULL) {
#if LP64_DEBUG
	panic("%s :%d - invalid uio_t\n", __FILE__, __LINE__); 
#endif /* LP64_DEBUG */
		return;
	}

#if LP64_DEBUG
	if (!(a_value == UIO_READ || a_value == UIO_WRITE)) {
		panic("%s :%d - invalid a_value\n", __FILE__, __LINE__); 
	}
#endif /* LP64_DEBUG */

	if (a_value == UIO_READ || a_value == UIO_WRITE) {
		a_uio->uio_rw = a_value;
	}
	return;
}