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
typedef  char u8 ;

/* Variables and functions */
 int wmi_parse_hexbyte (char const*) ; 

__attribute__((used)) static bool wmi_parse_guid(const u8 *src, u8 *dest)
{
	static const int size[] = { 4, 2, 2, 2, 6 };
	int i, j, v;

	if (src[8]  != '-' || src[13] != '-' ||
		src[18] != '-' || src[23] != '-')
		return false;

	for (j = 0; j < 5; j++, src++) {
		for (i = 0; i < size[j]; i++, src += 2, *dest++ = v) {
			v = wmi_parse_hexbyte(src);
			if (v < 0)
				return false;
		}
	}

	return true;
}