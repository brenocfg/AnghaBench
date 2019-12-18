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
typedef  unsigned int u8 ;

/* Variables and functions */

__attribute__((used)) static int wmi_parse_hexbyte(const u8 *src)
{
	unsigned int x; /* For correct wrapping */
	int h;

	/* high part */
	x = src[0];
	if (x - '0' <= '9' - '0') {
		h = x - '0';
	} else if (x - 'a' <= 'f' - 'a') {
		h = x - 'a' + 10;
	} else if (x - 'A' <= 'F' - 'A') {
		h = x - 'A' + 10;
	} else {
		return -1;
	}
	h <<= 4;

	/* low part */
	x = src[1];
	if (x - '0' <= '9' - '0')
		return h | (x - '0');
	if (x - 'a' <= 'f' - 'a')
		return h | (x - 'a' + 10);
	if (x - 'A' <= 'F' - 'A')
		return h | (x - 'A' + 10);
	return -1;
}