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
 int INADDRSZ ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 char* strchr (char const*,int) ; 

__attribute__((used)) static int
inet_pton4(const char *src, unsigned char *dst)
{
    static const char digits[] = "0123456789";
    int saw_digit, octets, ch;
    unsigned char tmp[INADDRSZ], *tp;

    saw_digit = 0;
    octets = 0;
    *(tp = tmp) = 0;
    while ((ch = *src++) != '\0') {
	const char *pch;

	if ((pch = strchr(digits, ch)) != NULL) {
	    unsigned int new = *tp * 10 + (unsigned int)(pch - digits);

	    if (new > 255)
		return (0);
	    *tp = new;
	    if (! saw_digit) {
		if (++octets > 4)
		    return (0);
		saw_digit = 1;
	    }
	} else if (ch == '.' && saw_digit) {
	    if (octets == 4)
		return (0);
	    *++tp = 0;
	    saw_digit = 0;
	} else
		return (0);
    }
    if (octets < 4)
	return (0);

    memcpy(dst, tmp, INADDRSZ);
    return (1);
}