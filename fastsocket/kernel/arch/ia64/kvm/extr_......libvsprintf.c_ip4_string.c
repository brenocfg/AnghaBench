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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 char* put_dec_trunc (char*,int /*<<< orphan*/  const) ; 

__attribute__((used)) static char *ip4_string(char *p, const u8 *addr, bool leading_zeros)
{
	int i;

	for (i = 0; i < 4; i++) {
		char temp[3];	/* hold each IP quad in reverse order */
		int digits = put_dec_trunc(temp, addr[i]) - temp;
		if (leading_zeros) {
			if (digits < 3)
				*p++ = '0';
			if (digits < 2)
				*p++ = '0';
		}
		/* reverse the digits in the quad */
		while (digits--)
			*p++ = temp[digits];
		if (i < 3)
			*p++ = '.';
	}

	*p = '\0';
	return p;
}