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
typedef  int uint64_t ;

/* Variables and functions */
 int hex_value (char const) ; 
 int /*<<< orphan*/  ishexdigit (char const) ; 

__attribute__((used)) static int
read_num(const char *line, int *len, uint64_t *num, size_t sz, int *checksum)
{
	uint8_t b;

	*num = 0;
	for (; sz > 0; sz--) {
		if (!ishexdigit(line[*len]) || !ishexdigit(line[*len + 1]))
			return (-1);
		b = (hex_value(line[*len]) << 4) | hex_value(line[*len + 1]);
		*num = (*num << 8) | b;
		*len += 2;
		if (checksum != NULL)
			*checksum = (*checksum + b) & 0xFF;
	}

	return (0);
}