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
typedef  char u_int16_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENAMETOOLONG ; 
 char const OSSwapInt16 (char const) ; 
 char SP_HALF_BASE ; 
 char SP_HALF_SHIFT ; 
 char SP_HIGH_FIRST ; 
 char SP_HIGH_LAST ; 
 char SP_LOW_FIRST ; 
 char SP_LOW_LAST ; 
 char UCS_ALT_NULL ; 
 int UTF_DECOMPOSED ; 
 int UTF_NO_NULL_TERM ; 
 int UTF_REVERSE_ENDIAN ; 
 int UTF_SFM_CONVERSIONS ; 
 char sfm_to_ucs (char) ; 
 int unicode_decompose (char,char*) ; 
 scalar_t__ unicode_decomposeable (char) ; 

int
utf8_encodestr(const u_int16_t * ucsp, size_t ucslen, u_int8_t * utf8p,
               size_t * utf8len, size_t buflen, u_int16_t altslash, int flags)
{
	u_int8_t * bufstart;
	u_int8_t * bufend;
	u_int16_t ucs_ch;
	u_int16_t * chp = NULL;
	u_int16_t sequence[8];
	int extra = 0;
	size_t charcnt;
	int swapbytes = (flags & UTF_REVERSE_ENDIAN);
	int nullterm  = ((flags & UTF_NO_NULL_TERM) == 0);
	int decompose = (flags & UTF_DECOMPOSED);
	int sfmconv = (flags & UTF_SFM_CONVERSIONS);
	int result = 0;

	bufstart = utf8p;
	bufend = bufstart + buflen;
	if (nullterm)
		--bufend;
	charcnt = ucslen / 2;

	while (charcnt-- > 0) {
		if (extra > 0) {
			--extra;
			ucs_ch = *chp++;
		} else {
			ucs_ch = swapbytes ? OSSwapInt16(*ucsp++) : *ucsp++;

			if (decompose && unicode_decomposeable(ucs_ch)) {
				extra = unicode_decompose(ucs_ch, sequence) - 1;
				charcnt += extra;
				ucs_ch = sequence[0];
				chp = &sequence[1];
			}
		}

		/* Slash and NULL are not permitted */
		if (ucs_ch == '/') {
			if (altslash)
				ucs_ch = altslash;
			else {
				ucs_ch = '_';
				result = EINVAL;
			}
		} else if (ucs_ch == '\0') {
			ucs_ch = UCS_ALT_NULL;
		}

		if (ucs_ch < 0x0080) {
			if (utf8p >= bufend) {
				result = ENAMETOOLONG;
				break;
			}			
			*utf8p++ = ucs_ch;

		} else if (ucs_ch < 0x800) {
			if ((utf8p + 1) >= bufend) {
				result = ENAMETOOLONG;
				break;
			}
			*utf8p++ = 0xc0 | (ucs_ch >> 6);
			*utf8p++ = 0x80 | (0x3f & ucs_ch);

		} else {
			/* These chars never valid Unicode. */
			if (ucs_ch == 0xFFFE || ucs_ch == 0xFFFF) {
				result = EINVAL;
				break;
			}

			/* Combine valid surrogate pairs */
			if (ucs_ch >= SP_HIGH_FIRST && ucs_ch <= SP_HIGH_LAST
				&& charcnt > 0) {
				u_int16_t ch2;
				u_int32_t pair;

				ch2 = swapbytes ? OSSwapInt16(*ucsp) : *ucsp;
				if (ch2 >= SP_LOW_FIRST && ch2 <= SP_LOW_LAST) {
					pair = ((ucs_ch - SP_HIGH_FIRST) << SP_HALF_SHIFT)
						+ (ch2 - SP_LOW_FIRST) + SP_HALF_BASE;
					if ((utf8p + 3) >= bufend) {
						result = ENAMETOOLONG;
						break;
					}
					--charcnt;
					++ucsp;				
					*utf8p++ = 0xf0 | (pair >> 18);
					*utf8p++ = 0x80 | (0x3f & (pair >> 12));
					*utf8p++ = 0x80 | (0x3f & (pair >> 6));
					*utf8p++ = 0x80 | (0x3f & pair);
					continue;
				}
			} else if (sfmconv) {
				ucs_ch = sfm_to_ucs(ucs_ch);
				if (ucs_ch < 0x0080) {
					if (utf8p >= bufend) {
						result = ENAMETOOLONG;
						break;
					}			
					*utf8p++ = ucs_ch;
					continue;
				}
			}
			if ((utf8p + 2) >= bufend) {
				result = ENAMETOOLONG;
				break;
			}
			*utf8p++ = 0xe0 | (ucs_ch >> 12);
			*utf8p++ = 0x80 | (0x3f & (ucs_ch >> 6));
			*utf8p++ = 0x80 | (0x3f & ucs_ch);
		}	
	}
	
	*utf8len = utf8p - bufstart;
	if (nullterm)
		*utf8p++ = '\0';

	return (result);
}