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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  br_enc64be (unsigned char*,int /*<<< orphan*/ ) ; 

void
br_range_enc64be(void *dst, const uint64_t *v, size_t num)
{
	unsigned char *buf;

	buf = dst;
	while (num -- > 0) {
		br_enc64be(buf, *v ++);
		buf += 8;
	}
}