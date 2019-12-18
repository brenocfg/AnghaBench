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
typedef  scalar_t__ const apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static const char *
inet_ntop4(const unsigned char *src, char *dst, apr_size_t size)
{
	const apr_size_t MIN_SIZE = 16; /* space for 255.255.255.255\0 */
	int n = 0;
	char *next = dst;

	if (size < MIN_SIZE) {
	    errno = ENOSPC;
	    return NULL;
	}
	do {
	    unsigned char u = *src++;
	    if (u > 99) {
		*next++ = '0' + u/100;
		u %= 100;
		*next++ = '0' + u/10;
		u %= 10;
	    }
	    else if (u > 9) {
		*next++ = '0' + u/10;
		u %= 10;
	    }
	    *next++ = '0' + u;
	    *next++ = '.';
	    n++;
	} while (n < 4);
	*--next = 0;
	return dst;
}