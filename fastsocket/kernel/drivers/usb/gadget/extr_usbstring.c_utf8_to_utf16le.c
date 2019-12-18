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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  put_unaligned_le16 (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (scalar_t__) ; 

__attribute__((used)) static int utf8_to_utf16le(const char *s, __le16 *cp, unsigned len)
{
	int	count = 0;
	u8	c;
	u16	uchar;

	/* this insists on correct encodings, though not minimal ones.
	 * BUT it currently rejects legit 4-byte UTF-8 code points,
	 * which need surrogate pairs.  (Unicode 3.1 can use them.)
	 */
	while (len != 0 && (c = (u8) *s++) != 0) {
		if (unlikely(c & 0x80)) {
			// 2-byte sequence:
			// 00000yyyyyxxxxxx = 110yyyyy 10xxxxxx
			if ((c & 0xe0) == 0xc0) {
				uchar = (c & 0x1f) << 6;

				c = (u8) *s++;
				if ((c & 0xc0) != 0x80)
					goto fail;
				c &= 0x3f;
				uchar |= c;

			// 3-byte sequence (most CJKV characters):
			// zzzzyyyyyyxxxxxx = 1110zzzz 10yyyyyy 10xxxxxx
			} else if ((c & 0xf0) == 0xe0) {
				uchar = (c & 0x0f) << 12;

				c = (u8) *s++;
				if ((c & 0xc0) != 0x80)
					goto fail;
				c &= 0x3f;
				uchar |= c << 6;

				c = (u8) *s++;
				if ((c & 0xc0) != 0x80)
					goto fail;
				c &= 0x3f;
				uchar |= c;

				/* no bogus surrogates */
				if (0xd800 <= uchar && uchar <= 0xdfff)
					goto fail;

			// 4-byte sequence (surrogate pairs, currently rare):
			// 11101110wwwwzzzzyy + 110111yyyyxxxxxx
			//     = 11110uuu 10uuzzzz 10yyyyyy 10xxxxxx
			// (uuuuu = wwww + 1)
			// FIXME accept the surrogate code points (only)

			} else
				goto fail;
		} else
			uchar = c;
		put_unaligned_le16(uchar, cp++);
		count++;
		len--;
	}
	return count;
fail:
	return -1;
}