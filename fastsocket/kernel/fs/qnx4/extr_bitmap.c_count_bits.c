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
 int QNX4_BLOCK_SIZE ; 

__attribute__((used)) static void count_bits(register const char *bmPart, register int size,
		       int *const tf)
{
	char b;
	int tot = *tf;

	if (size > QNX4_BLOCK_SIZE) {
		size = QNX4_BLOCK_SIZE;
	}
	do {
		b = *bmPart++;
		if ((b & 1) == 0)
			tot++;
		if ((b & 2) == 0)
			tot++;
		if ((b & 4) == 0)
			tot++;
		if ((b & 8) == 0)
			tot++;
		if ((b & 16) == 0)
			tot++;
		if ((b & 32) == 0)
			tot++;
		if ((b & 64) == 0)
			tot++;
		if ((b & 128) == 0)
			tot++;
		size--;
	} while (size != 0);
	*tf = tot;
}