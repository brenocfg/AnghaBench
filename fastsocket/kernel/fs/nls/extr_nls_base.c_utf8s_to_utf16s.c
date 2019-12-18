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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int unicode_t ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  enum utf16_endian { ____Placeholder_utf16_endian } utf16_endian ;

/* Variables and functions */
 int EINVAL ; 
 int PLANE_SIZE ; 
 int SURROGATE_BITS ; 
 int SURROGATE_LOW ; 
 int SURROGATE_PAIR ; 
 int /*<<< orphan*/  put_utf16 (int /*<<< orphan*/ ,int,int) ; 
 int utf8_to_utf32 (int const*,int,int*) ; 

int utf8s_to_utf16s(const u8 *s, int len, enum utf16_endian endian,
		wchar_t *pwcs, int maxlen)
{
	u16 *op;
	int size;
	unicode_t u;

	op = pwcs;
	while (len > 0 && maxlen > 0 && *s) {
		if (*s & 0x80) {
			size = utf8_to_utf32(s, len, &u);
			if (size < 0)
				return -EINVAL;
			s += size;
			len -= size;

			if (u >= PLANE_SIZE) {
				if (maxlen < 2)
					break;
				u -= PLANE_SIZE;
				put_utf16(op++, SURROGATE_PAIR |
						((u >> 10) & SURROGATE_BITS),
						endian);
				put_utf16(op++, SURROGATE_PAIR |
						SURROGATE_LOW |
						(u & SURROGATE_BITS),
						endian);
				maxlen -= 2;
			} else {
				put_utf16(op++, u, endian);
				maxlen--;
			}
		} else {
			put_utf16(op++, *s++, endian);
			len--;
			maxlen--;
		}
	}
	return op - pwcs;
}