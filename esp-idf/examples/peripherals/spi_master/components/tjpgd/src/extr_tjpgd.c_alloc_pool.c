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
typedef  int uint16_t ;
struct TYPE_3__ {int sz_pool; void* pool; } ;
typedef  TYPE_1__ JDEC ;

/* Variables and functions */

__attribute__((used)) static void* alloc_pool (	/* Pointer to allocated memory block (NULL:no memory available) */
	JDEC* jd,		/* Pointer to the decompressor object */
	uint16_t nd		/* Number of bytes to allocate */
)
{
	char *rp = 0;


	nd = (nd + 3) & ~3;			/* Align block size to the word boundary */

	if (jd->sz_pool >= nd) {
		jd->sz_pool -= nd;
		rp = (char*)jd->pool;			/* Get start of available memory pool */
		jd->pool = (void*)(rp + nd);	/* Allocate requierd bytes */
	}

	return (void*)rp;	/* Return allocated memory block (NULL:no memory to allocate) */
}