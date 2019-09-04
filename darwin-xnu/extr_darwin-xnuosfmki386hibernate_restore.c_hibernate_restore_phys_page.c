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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEST_COPY_AREA ; 
 int /*<<< orphan*/  __nosan_memcpy (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ pal_hib_map (int /*<<< orphan*/ ,scalar_t__) ; 

uintptr_t 
hibernate_restore_phys_page(uint64_t src, uint64_t dst, uint32_t len, uint32_t procFlags)
{
	(void)procFlags;
	uint64_t * d;
	uint64_t * s;

	if (src == 0)
		return (uintptr_t)dst;

	d = (uint64_t *)pal_hib_map(DEST_COPY_AREA, dst);
	s = (uint64_t *) (uintptr_t)src;

	__nosan_memcpy(d, s, len);

	return (uintptr_t)d;
}