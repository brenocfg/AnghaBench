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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  WPA_PUT_LE16 (int*,int) ; 

__attribute__((used)) static int utf8_to_ucs2(const u8 *utf8_string, size_t utf8_string_len,
	     u8 *ucs2_buffer, size_t ucs2_buffer_size,
	     size_t *ucs2_string_size)
{
	size_t i, j;

	for (i = 0, j = 0; i < utf8_string_len; i++) {
		u8 c = utf8_string[i];
		if (j >= ucs2_buffer_size) {
			/* input too long */
			return -1;
		}
		if (c <= 0x7F) {
			WPA_PUT_LE16(ucs2_buffer + j, c);
			j += 2;
		} else if (i == utf8_string_len - 1 ||
			   j >= ucs2_buffer_size - 1) {
			/* incomplete surrogate */
			return -1;
		} else {
			u8 c2 = utf8_string[++i];
			if ((c & 0xE0) == 0xC0) {
				/* two-byte encoding */
				WPA_PUT_LE16(ucs2_buffer + j,
					     ((c & 0x1F) << 6) | (c2 & 0x3F));
				j += 2;
			} else if (i == utf8_string_len ||
				   j >= ucs2_buffer_size - 1) {
				/* incomplete surrogate */
				return -1;
			} else {
				/* three-byte encoding */
				u8 c3 = utf8_string[++i];
				WPA_PUT_LE16(ucs2_buffer + j,
					     ((c & 0xF) << 12) |
					     ((c2 & 0x3F) << 6) | (c3 & 0x3F));
			}
		}
	}

	if (ucs2_string_size)
		*ucs2_string_size = j / 2;
	return 0;
}