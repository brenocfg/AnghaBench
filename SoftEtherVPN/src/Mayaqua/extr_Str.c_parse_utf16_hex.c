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
 int hex_char_to_int (char) ; 

__attribute__((used)) static int parse_utf16_hex(char *s, unsigned int *result) {
	int x1, x2, x3, x4;
	if (s[0] == '\0' || s[1] == '\0' || s[2] == '\0' || s[3] == '\0') {
		return 0;
	}
	x1 = hex_char_to_int(s[0]);
	x2 = hex_char_to_int(s[1]);
	x3 = hex_char_to_int(s[2]);
	x4 = hex_char_to_int(s[3]);
	if (x1 == -1 || x2 == -1 || x3 == -1 || x4 == -1) {
		return 0;
	}
	*result = (unsigned int)((x1 << 12) | (x2 << 8) | (x3 << 4) | x4);
	return 1;
}