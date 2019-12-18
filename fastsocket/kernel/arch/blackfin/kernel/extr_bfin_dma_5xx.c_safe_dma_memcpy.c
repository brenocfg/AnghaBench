#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  VERIFY_READ ; 
 int /*<<< orphan*/  VERIFY_WRITE ; 
 int /*<<< orphan*/  access_ok (int /*<<< orphan*/ ,void const*,size_t) ; 
 void* dma_memcpy (void*,void const*,size_t) ; 

void *safe_dma_memcpy(void *dst, const void *src, size_t size)
{
	if (!access_ok(VERIFY_WRITE, dst, size))
		return NULL;
	if (!access_ok(VERIFY_READ, src, size))
		return NULL;
	return dma_memcpy(dst, src, size);
}