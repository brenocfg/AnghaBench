#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* uio_t ;
struct TYPE_4__ {int uio_flags; int /*<<< orphan*/  uio_size; } ;

/* Variables and functions */
 int UIO_FLAGS_WE_ALLOCED ; 
 int /*<<< orphan*/  kfree (TYPE_1__*,int /*<<< orphan*/ ) ; 

void uio_free( uio_t a_uio ) 
{
#if DEBUG
	if (a_uio == NULL) {
		panic("%s :%d - passing NULL uio_t\n", __FILE__, __LINE__); 
	}
#endif /* LP64_DEBUG */

	if (a_uio != NULL && (a_uio->uio_flags & UIO_FLAGS_WE_ALLOCED) != 0) {
#if DEBUG
		if (hw_atomic_sub(&uio_t_count, 1) == UINT_MAX)
			panic("%s :%d - uio_t_count underflow\n", __FILE__, __LINE__); 
#endif
		kfree(a_uio, a_uio->uio_size);
	}


}