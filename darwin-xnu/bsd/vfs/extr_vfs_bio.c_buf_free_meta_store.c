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
typedef  int /*<<< orphan*/  zone_t ;
typedef  TYPE_1__* buf_t ;
struct TYPE_3__ {uintptr_t b_datap; scalar_t__ b_bufsize; int /*<<< orphan*/  b_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_ZALLOC ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getbufzone (scalar_t__) ; 
 int /*<<< orphan*/  kernel_map ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ,uintptr_t,scalar_t__) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void
buf_free_meta_store(buf_t bp)
{
	if (bp->b_bufsize) {
		if (ISSET(bp->b_flags, B_ZALLOC)) {
			zone_t z;

			z = getbufzone(bp->b_bufsize);
			zfree(z, (void *)bp->b_datap);
		} else
			kmem_free(kernel_map, bp->b_datap, bp->b_bufsize); 

		bp->b_datap = (uintptr_t)NULL;
		bp->b_bufsize = 0;
	}
}