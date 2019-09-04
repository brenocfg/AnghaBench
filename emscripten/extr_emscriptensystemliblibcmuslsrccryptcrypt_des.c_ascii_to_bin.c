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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t ascii_to_bin(int ch)
{
	int sch = (ch < 0x80) ? ch : -(0x100 - ch);
	int retval;

	retval = sch - '.';
	if (sch >= 'A') {
		retval = sch - ('A' - 12);
		if (sch >= 'a')
			retval = sch - ('a' - 38);
	}
	retval &= 0x3f;

	return retval;
}