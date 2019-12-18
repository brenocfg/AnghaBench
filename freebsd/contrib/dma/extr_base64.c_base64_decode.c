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
 unsigned int DECODE_ERROR ; 
 int /*<<< orphan*/  base64_chars ; 
 scalar_t__ strchr (int /*<<< orphan*/ ,char const) ; 
 unsigned int token_decode (char const*) ; 

int
base64_decode(const char *str, void *data)
{
	const char *p;
	unsigned char *q;

	q = data;
	for (p = str; *p && (*p == '=' || strchr(base64_chars, *p)); p += 4) {
		unsigned int val = token_decode(p);
		unsigned int marker = (val >> 24) & 0xff;
		if (val == DECODE_ERROR)
			return -1;
		*q++ = (val >> 16) & 0xff;
		if (marker < 2)
			*q++ = (val >> 8) & 0xff;
		if (marker < 1)
			*q++ = val & 0xff;
	}
	return q - (unsigned char *) data;
}