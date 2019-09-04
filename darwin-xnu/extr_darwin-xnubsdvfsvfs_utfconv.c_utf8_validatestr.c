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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int u_int32_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SP_HALF_BASE ; 
 int SP_HALF_MASK ; 
 int SP_HALF_SHIFT ; 
 int SP_HIGH_FIRST ; 
 unsigned int SP_HIGH_LAST ; 
 int SP_LOW_FIRST ; 
 unsigned int SP_LOW_LAST ; 
 size_t* utf_extrabytes ; 

int
utf8_validatestr(const u_int8_t* utf8p, size_t utf8len)
{
	unsigned int byte;
	u_int32_t ch;
	unsigned int ucs_ch;
	size_t extrabytes;

	while (utf8len-- > 0 && (byte = *utf8p++) != '\0') {
		if (byte < 0x80)
			continue;  /* plain ascii */

		extrabytes = utf_extrabytes[byte >> 3];

		if (utf8len < extrabytes)
			goto invalid;
		utf8len -= extrabytes;

		switch (extrabytes) {
		case 1:
			ch = byte; ch <<= 6;   /* 1st byte */
			byte = *utf8p++;       /* 2nd byte */
			if ((byte >> 6) != 2)
				goto invalid;
			ch += byte;
			ch -= 0x00003080UL;
			if (ch < 0x0080)
				goto invalid;
			break;
		case 2:
			ch = byte; ch <<= 6;   /* 1st byte */
			byte = *utf8p++;       /* 2nd byte */
			if ((byte >> 6) != 2)
				goto invalid;
			ch += byte; ch <<= 6;
			byte = *utf8p++;       /* 3rd byte */
			if ((byte >> 6) != 2)
				goto invalid;
			ch += byte;
			ch -= 0x000E2080UL;
			if (ch < 0x0800)
				goto invalid;
			if (ch >= 0xD800) {
				if (ch <= 0xDFFF)
					goto invalid;
				if (ch == 0xFFFE || ch == 0xFFFF)
					goto invalid;
			}
			break;
		case 3:
			ch = byte; ch <<= 6;   /* 1st byte */
			byte = *utf8p++;       /* 2nd byte */
			if ((byte >> 6) != 2)
				goto invalid;
			ch += byte; ch <<= 6;
			byte = *utf8p++;       /* 3rd byte */
			if ((byte >> 6) != 2)
				goto invalid;
			ch += byte; ch <<= 6;
			byte = *utf8p++;       /* 4th byte */
			if ((byte >> 6) != 2)
				goto invalid;
			ch += byte;
			ch -= 0x03C82080UL + SP_HALF_BASE;
			ucs_ch = (ch >> SP_HALF_SHIFT) + SP_HIGH_FIRST;
			if (ucs_ch < SP_HIGH_FIRST || ucs_ch > SP_HIGH_LAST)
				goto invalid;
			ucs_ch = (ch & SP_HALF_MASK) + SP_LOW_FIRST;
			if (ucs_ch < SP_LOW_FIRST || ucs_ch > SP_LOW_LAST)
				goto invalid;
			break;
		default:
			goto invalid;
		}
		
	}
	return (0);
invalid:
	return (EINVAL);
}