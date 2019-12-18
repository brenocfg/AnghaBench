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
struct printf_spec {int flags; int base; scalar_t__ field_width; int precision; } ;

/* Variables and functions */
 int LEFT ; 
 int PLUS ; 
 int SIGN ; 
 char SMALL ; 
 int SPACE ; 
 int SPECIAL ; 
 int ZEROPAD ; 
 char* put_dec (char*,unsigned long long) ; 

__attribute__((used)) static char *number(char *buf, char *end, unsigned long long num,
			struct printf_spec spec)
{
	/* we are called with base 8, 10 or 16, only, thus don't need "G..."  */
	static const char digits[16] = "0123456789ABCDEF"; /* "GHIJKLMNOPQRSTUVWXYZ"; */

	char tmp[66];
	char sign;
	char locase;
	int need_pfx = ((spec.flags & SPECIAL) && spec.base != 10);
	int i;

	/* locase = 0 or 0x20. ORing digits or letters with 'locase'
	 * produces same digits or (maybe lowercased) letters */
	locase = (spec.flags & SMALL);
	if (spec.flags & LEFT)
		spec.flags &= ~ZEROPAD;
	sign = 0;
	if (spec.flags & SIGN) {
		if ((signed long long) num < 0) {
			sign = '-';
			num = - (signed long long) num;
			spec.field_width--;
		} else if (spec.flags & PLUS) {
			sign = '+';
			spec.field_width--;
		} else if (spec.flags & SPACE) {
			sign = ' ';
			spec.field_width--;
		}
	}
	if (need_pfx) {
		spec.field_width--;
		if (spec.base == 16)
			spec.field_width--;
	}

	/* generate full string in tmp[], in reverse order */
	i = 0;
	if (num == 0)
		tmp[i++] = '0';
	/* Generic code, for any base:
	else do {
		tmp[i++] = (digits[do_div(num,base)] | locase);
	} while (num != 0);
	*/
	else if (spec.base != 10) { /* 8 or 16 */
		int mask = spec.base - 1;
		int shift = 3;
		if (spec.base == 16) shift = 4;
		do {
			tmp[i++] = (digits[((unsigned char)num) & mask] | locase);
			num >>= shift;
		} while (num);
	} else { /* base 10 */
		i = put_dec(tmp, num) - tmp;
	}

	/* printing 100 using %2d gives "100", not "00" */
	if (i > spec.precision)
		spec.precision = i;
	/* leading space padding */
	spec.field_width -= spec.precision;
	if (!(spec.flags & (ZEROPAD+LEFT))) {
		while(--spec.field_width >= 0) {
			if (buf < end)
				*buf = ' ';
			++buf;
		}
	}
	/* sign */
	if (sign) {
		if (buf < end)
			*buf = sign;
		++buf;
	}
	/* "0x" / "0" prefix */
	if (need_pfx) {
		if (buf < end)
			*buf = '0';
		++buf;
		if (spec.base == 16) {
			if (buf < end)
				*buf = ('X' | locase);
			++buf;
		}
	}
	/* zero or space padding */
	if (!(spec.flags & LEFT)) {
		char c = (spec.flags & ZEROPAD) ? '0' : ' ';
		while (--spec.field_width >= 0) {
			if (buf < end)
				*buf = c;
			++buf;
		}
	}
	/* hmm even more zero padding? */
	while (i <= --spec.precision) {
		if (buf < end)
			*buf = '0';
		++buf;
	}
	/* actual digits of result */
	while (--i >= 0) {
		if (buf < end)
			*buf = tmp[i];
		++buf;
	}
	/* trailing space padding */
	while (--spec.field_width >= 0) {
		if (buf < end)
			*buf = ' ';
		++buf;
	}
	return buf;
}