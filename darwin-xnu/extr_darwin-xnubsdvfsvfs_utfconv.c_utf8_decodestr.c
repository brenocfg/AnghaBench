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
typedef  int uint16_t ;
typedef  unsigned int u_int8_t ;
typedef  int u_int32_t ;
typedef  int u_int16_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENAMETOOLONG ; 
 int OSSwapInt16 (int) ; 
 int /*<<< orphan*/  SP_HALF_BASE ; 
 int SP_HALF_MASK ; 
 int SP_HALF_SHIFT ; 
 int SP_HIGH_FIRST ; 
 unsigned int SP_HIGH_LAST ; 
 int SP_LOW_FIRST ; 
 unsigned int SP_LOW_LAST ; 
 unsigned int UCS_ALT_NULL ; 
 int UTF_DECOMPOSED ; 
 int UTF_ESCAPE_ILLEGAL ; 
 int UTF_PRECOMPOSED ; 
 int UTF_REVERSE_ENDIAN ; 
 int UTF_SFM_CONVERSIONS ; 
 unsigned int* hexdigits ; 
 int /*<<< orphan*/  prioritysort (int*,int) ; 
 int /*<<< orphan*/  push (unsigned int,int*,int**) ; 
 unsigned int ucs_to_sfm (unsigned int,int) ; 
 scalar_t__ unicode_combinable (unsigned int) ; 
 int unicode_combine (int,unsigned int) ; 
 int unicode_decompose (unsigned int,int*) ; 
 scalar_t__ unicode_decomposeable (unsigned int) ; 
 int* utf_extrabytes ; 

int
utf8_decodestr(const u_int8_t* utf8p, size_t utf8len, u_int16_t* ucsp,
               size_t *ucslen, size_t buflen, u_int16_t altslash, int flags)
{
	u_int16_t* bufstart;
	u_int16_t* bufend;
	unsigned int ucs_ch;
	unsigned int byte;
	int combcharcnt = 0;
	int result = 0;
	int decompose, precompose, escaping;
	int sfmconv;
	int extrabytes;

	decompose  = (flags & UTF_DECOMPOSED);
	precompose = (flags & UTF_PRECOMPOSED);
	escaping   = (flags & UTF_ESCAPE_ILLEGAL);
	sfmconv    = (flags & UTF_SFM_CONVERSIONS);

	bufstart = ucsp;
	bufend = (u_int16_t *)((u_int8_t *)ucsp + buflen);

	while (utf8len-- > 0 && (byte = *utf8p++) != '\0') {
		if (ucsp >= bufend)
			goto toolong;

		/* check for ascii */
		if (byte < 0x80) {
			ucs_ch = sfmconv ? ucs_to_sfm(byte, utf8len == 0) : byte;
		} else {
			u_int32_t ch;

			extrabytes = utf_extrabytes[byte >> 3];
			if ((extrabytes < 0) || ((int)utf8len < extrabytes)) {
				goto escape;
			}
			utf8len -= extrabytes;

			switch (extrabytes) {
			case 1:
				ch = byte; ch <<= 6;   /* 1st byte */
				byte = *utf8p++;       /* 2nd byte */
				if ((byte >> 6) != 2)
					goto escape2;
				ch += byte;
				ch -= 0x00003080UL;
				if (ch < 0x0080)
					goto escape2;
				ucs_ch = ch;
			        break;
			case 2:
				ch = byte; ch <<= 6;   /* 1st byte */
				byte = *utf8p++;       /* 2nd byte */
				if ((byte >> 6) != 2)
					goto escape2;
				ch += byte; ch <<= 6;
				byte = *utf8p++;       /* 3rd byte */
				if ((byte >> 6) != 2)
					goto escape3;
				ch += byte;
				ch -= 0x000E2080UL;
				if (ch < 0x0800)
					goto escape3;
				if (ch >= 0xD800) {
					if (ch <= 0xDFFF)
						goto escape3;
					if (ch == 0xFFFE || ch == 0xFFFF)
						goto escape3;
				}
				ucs_ch = ch;
				break;
			case 3:
				ch = byte; ch <<= 6;   /* 1st byte */
				byte = *utf8p++;       /* 2nd byte */
				if ((byte >> 6) != 2)
					goto escape2;
				ch += byte; ch <<= 6;
				byte = *utf8p++;       /* 3rd byte */
				if ((byte >> 6) != 2)
					goto escape3;
				ch += byte; ch <<= 6;
				byte = *utf8p++;       /* 4th byte */
				if ((byte >> 6) != 2)
					goto escape4;
			        ch += byte;
				ch -= 0x03C82080UL + SP_HALF_BASE;
				ucs_ch = (ch >> SP_HALF_SHIFT) + SP_HIGH_FIRST;
				if (ucs_ch < SP_HIGH_FIRST || ucs_ch > SP_HIGH_LAST)
					goto escape4;
				push(ucs_ch, &combcharcnt, &ucsp);
				if (ucsp >= bufend)
					goto toolong;
				ucs_ch = (ch & SP_HALF_MASK) + SP_LOW_FIRST;
				if (ucs_ch < SP_LOW_FIRST || ucs_ch > SP_LOW_LAST) {
					--ucsp;
					goto escape4;
				}
				*ucsp++ = ucs_ch;
			        continue;
			default:
				result = EINVAL;
				goto exit;
			}
			if (decompose) {
				if (unicode_decomposeable(ucs_ch)) {
					u_int16_t sequence[8];
					int count, i;

					count = unicode_decompose(ucs_ch, sequence);

					for (i = 0; i < count; ++i) {
						if (ucsp >= bufend)
							goto toolong;

						push(sequence[i], &combcharcnt, &ucsp);
					}

					continue;
				}
			} else if (precompose && (ucsp != bufstart)) {
				u_int16_t composite, base;

				if (unicode_combinable(ucs_ch)) {
					base = ucsp[-1];
					composite = unicode_combine(base, ucs_ch);
					if (composite) {
						--ucsp;
						ucs_ch = composite;
					}
				}
			}
			if (ucs_ch == UCS_ALT_NULL)
				ucs_ch = '\0';
		}
		if (ucs_ch == altslash)
			ucs_ch = '/';

		push(ucs_ch, &combcharcnt, &ucsp);
		continue;

		/* 
		 * Escape illegal UTF-8 into something legal.
		 */
escape4:
		utf8p -= 3;
		goto escape;
escape3:
		utf8p -= 2;
		goto escape;
escape2:
		utf8p -= 1;
escape:
		if (!escaping) {
			result = EINVAL;
			goto exit;
		}
		if (extrabytes > 0)
			utf8len += extrabytes;
		byte = *(utf8p - 1);

		if ((ucsp + 2) >= bufend)
			goto toolong;

		/* Make a previous combining sequence canonical. */
		if (combcharcnt > 1) {
			prioritysort(ucsp - combcharcnt, combcharcnt);
		}
		combcharcnt = 0;
		
		ucs_ch = '%';
		*ucsp++ = ucs_ch;
		ucs_ch =  hexdigits[byte >> 4];
		*ucsp++ = ucs_ch;
		ucs_ch =  hexdigits[byte & 0x0F];
		*ucsp++ = ucs_ch;
	}
	/*
	 * Make a previous combining sequence canonical
	 */
	if (combcharcnt > 1) {
		prioritysort(ucsp - combcharcnt, combcharcnt);
	}

	if (flags & UTF_REVERSE_ENDIAN) {
		uint16_t *p = bufstart;
		while (p < ucsp) {
			*p = OSSwapInt16(*p);
			++p;
		}
	}

exit:
	*ucslen = (u_int8_t*)ucsp - (u_int8_t*)bufstart;

	return (result);

toolong:
	result = ENAMETOOLONG;
	goto exit;
}