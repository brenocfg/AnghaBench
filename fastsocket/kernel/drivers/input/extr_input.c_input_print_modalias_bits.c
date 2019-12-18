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
 unsigned long BIT_MASK (int) ; 
 size_t BIT_WORD (int) ; 
 int /*<<< orphan*/  max (int,int /*<<< orphan*/ ) ; 
 scalar_t__ snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int input_print_modalias_bits(char *buf, int size,
				     char name, unsigned long *bm,
				     unsigned int min_bit, unsigned int max_bit)
{
	int len = 0, i;

	len += snprintf(buf, max(size, 0), "%c", name);
	for (i = min_bit; i < max_bit; i++)
		if (bm[BIT_WORD(i)] & BIT_MASK(i))
			len += snprintf(buf + len, max(size - len, 0), "%X,", i);
	return len;
}