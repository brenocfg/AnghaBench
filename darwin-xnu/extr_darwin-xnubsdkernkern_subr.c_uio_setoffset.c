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
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_3__ {int /*<<< orphan*/  uio_offset; } ;

/* Variables and functions */

void uio_setoffset( uio_t a_uio, off_t a_offset )
{
#if LP64_DEBUG
	if (a_uio == NULL) {
		panic("%s :%d - invalid uio_t\n", __FILE__, __LINE__); 
	}
#endif /* LP64_DEBUG */

	if (a_uio == NULL) {
		return; 
	}
	a_uio->uio_offset = a_offset;
	return;
}