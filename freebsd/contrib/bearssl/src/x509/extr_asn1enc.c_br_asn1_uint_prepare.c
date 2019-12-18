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
struct TYPE_3__ {unsigned char const* data; size_t len; size_t asn1len; } ;
typedef  TYPE_1__ br_asn1_uint ;

/* Variables and functions */

br_asn1_uint
br_asn1_uint_prepare(const void *xdata, size_t xlen)
{
	const unsigned char *x;
	br_asn1_uint t;

	x = xdata;
	while (xlen > 0 && *x == 0) {
		x ++;
		xlen --;
	}
	t.data = x;
	t.len = xlen;
	t.asn1len = xlen;
	if (xlen == 0 || x[0] >= 0x80) {
		t.asn1len ++;
	}
	return t;
}