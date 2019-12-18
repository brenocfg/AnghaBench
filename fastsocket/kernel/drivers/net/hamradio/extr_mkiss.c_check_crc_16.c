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
 unsigned short crc16 (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int check_crc_16(unsigned char *cp, int size)
{
	unsigned short crc = 0x0000;

	if (size < 3)
		return -1;

	crc = crc16(0, cp, size);

	if (crc != 0x0000)
		return -1;

	return 0;
}