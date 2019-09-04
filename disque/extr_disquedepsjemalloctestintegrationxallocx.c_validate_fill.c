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
typedef  scalar_t__ const uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  print_filled_extents (void const*,scalar_t__ const,size_t) ; 

__attribute__((used)) static bool
validate_fill(const void *p, uint8_t c, size_t offset, size_t len)
{
	const uint8_t *pc = (const uint8_t *)p;
	bool err;
	size_t i;

	for (i = offset, err = false; i < offset+len; i++) {
		if (pc[i] != c)
			err = true;
	}

	if (err)
		print_filled_extents(p, c, offset + len);

	return (err);
}