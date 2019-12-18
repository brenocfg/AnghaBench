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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 
 scalar_t__ panic_stackshot ; 

void
stackshot_memcpy(void *dst, const void *src, size_t len)
{
#if CONFIG_EMBEDDED
	if (panic_stackshot) {
		uint8_t *dest_bytes = (uint8_t *)dst;
		const uint8_t *src_bytes = (const uint8_t *)src;
		for (size_t i = 0; i < len; i++) {
			dest_bytes[i] = src_bytes[i];
		}
	} else
#endif
		memcpy(dst, src, len);
}