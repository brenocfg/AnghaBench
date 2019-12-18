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
 scalar_t__ strtoul (char*,char**,int) ; 

__attribute__((used)) static int parse_hex_color(char *buff)
{
	char *endp = buff;
	int t = (int) strtoul(buff, &endp, 16);
	if (endp != buff)
#ifdef PSP
		return ((t<<8)&0xf800) | ((t>>5)&0x07e0) | ((t>>19)&0x1f);
#else
		return ((t>>8)&0xf800) | ((t>>5)&0x07e0) | ((t>>3)&0x1f);
#endif
	return -1;
}