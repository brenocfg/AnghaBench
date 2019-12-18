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
typedef  char u_int16_t ;

/* Variables and functions */
 char OSSwapInt16 (char) ; 
 char UCS_ALT_NULL ; 
 scalar_t__ UNICODE_TO_UTF8_LEN (char) ; 
 int UTF_DECOMPOSED ; 
 int UTF_REVERSE_ENDIAN ; 
 int unicode_decompose (char,char*) ; 
 scalar_t__ unicode_decomposeable (char) ; 

size_t
utf8_encodelen(const u_int16_t * ucsp, size_t ucslen, u_int16_t altslash, int flags)
{
	u_int16_t ucs_ch;
	u_int16_t * chp = NULL;
	u_int16_t sequence[8];
	int extra = 0;
	size_t charcnt;
	int swapbytes = (flags & UTF_REVERSE_ENDIAN);
	int decompose = (flags & UTF_DECOMPOSED);
	size_t len;

	charcnt = ucslen / 2;
	len = 0;

	while (charcnt-- > 0) {
		if (extra > 0) {
			--extra;
			ucs_ch = *chp++;
		} else {
			ucs_ch = *ucsp++;
			if (swapbytes) {
				ucs_ch = OSSwapInt16(ucs_ch);
			}
			if (ucs_ch == '/') {
				ucs_ch = altslash ? altslash : '_';
			} else if (ucs_ch == '\0') {
				ucs_ch = UCS_ALT_NULL;
			} else if (decompose && unicode_decomposeable(ucs_ch)) {
				extra = unicode_decompose(ucs_ch, sequence) - 1;
				charcnt += extra;
				ucs_ch = sequence[0];
				chp = &sequence[1];
			}
		}
		len += UNICODE_TO_UTF8_LEN(ucs_ch);
	}

	return (len);
}