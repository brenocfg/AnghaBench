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
typedef  scalar_t__ boolean_t ;
typedef  scalar_t__ (* argsep_func_t ) (char) ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int NUM ; 
 int STR ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static int
getval(
	char *s,
	long long *val,
	argsep_func_t issep,
	boolean_t skip_equal_sign )
{
	unsigned long long radix, intval;
	unsigned char c;
	int sign = 1;
	boolean_t has_value = FALSE;

	if (*s == '=') {
		s++;
		has_value = TRUE;
	}

	if (has_value || skip_equal_sign) {
		if (*s == '-') {
			sign = -1;
			s++;
		}
		intval = *s++-'0';
		radix = 10;
		if (intval == 0) {
			switch(*s) {

			case 'x':
				radix = 16;
				s++;
				break;

			case 'b':
				radix = 2;
				s++;
				break;

			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7':
				intval = *s-'0';
				s++;
				radix = 8;
				break;

			default:
				if (!issep(*s))
					return (STR);
			}
                } else if (intval >= radix) {
                    return (STR);
                }
		for(;;) {
                        c = *s++;
                        if (issep(c))
                            break;
                        if ((radix <= 10) &&
                            ((c >= '0') && (c <= ('9' - (10 - radix))))) {
                                c -= '0';
                        } else if ((radix == 16) &&
                                   ((c >= '0') && (c <= '9'))) {
				c -= '0';
                        } else if ((radix == 16) &&
                                   ((c >= 'a') && (c <= 'f'))) {
				c -= 'a' - 10;
                        } else if ((radix == 16) &&
                                   ((c >= 'A') && (c <= 'F'))) {
				c -= 'A' - 10;
                        } else if (c == 'k' || c == 'K') {
				sign *= 1024;
				break;
			} else if (c == 'm' || c == 'M') {
				sign *= 1024 * 1024;
                                break;
			} else if (c == 'g' || c == 'G') {
				sign *= 1024 * 1024 * 1024;
                                break;
			} else {
				return (STR);
                        }
			if (c >= radix)
				return (STR);
			intval *= radix;
			intval += c;
		}
                if (!issep(c) && !issep(*s))
                    return STR;
		*val = intval * sign;
		return (NUM);
	}
	*val = 1;
	return (NUM);
}