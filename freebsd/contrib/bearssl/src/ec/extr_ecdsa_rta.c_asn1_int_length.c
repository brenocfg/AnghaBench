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

__attribute__((used)) static size_t
asn1_int_length(const unsigned char *x, size_t xlen)
{
	while (xlen > 0 && *x == 0) {
		x ++;
		xlen --;
	}
	if (xlen == 0 || *x >= 0x80) {
		xlen ++;
	}
	return xlen;
}