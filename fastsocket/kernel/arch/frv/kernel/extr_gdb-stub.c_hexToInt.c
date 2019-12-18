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
typedef  int uint8_t ;

/* Variables and functions */
 int hex (char) ; 

__attribute__((used)) static int hexToInt(char **ptr, unsigned long *_value)
{
	int count = 0, ch;

	*_value = 0;
	while (**ptr) {
		ch = hex(**ptr);
		if (ch < 0)
			break;

		*_value = (*_value << 4) | ((uint8_t) ch & 0xf);
		count++;

		(*ptr)++;
	}

	return count;
}