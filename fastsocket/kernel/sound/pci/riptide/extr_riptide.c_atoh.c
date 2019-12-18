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
typedef  unsigned int u32 ;

/* Variables and functions */

__attribute__((used)) static u32 atoh(const unsigned char *in, unsigned int len)
{
	u32 sum = 0;
	unsigned int mult = 1;
	unsigned char c;

	while (len) {
		c = in[len - 1];
		if ((c >= '0') && (c <= '9'))
			sum += mult * (c - '0');
		else if ((c >= 'A') && (c <= 'F'))
			sum += mult * (c - ('A' - 10));
		else if ((c >= 'a') && (c <= 'f'))
			sum += mult * (c - ('a' - 10));
		mult *= 16;
		--len;
	}
	return sum;
}