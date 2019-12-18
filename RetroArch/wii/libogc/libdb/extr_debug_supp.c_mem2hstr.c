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
typedef  scalar_t__ s32 ;

/* Variables and functions */
 void** hexchars ; 

char* mem2hstr(char *buf,const char *mem,s32 count)
{
	s32 i;
	char ch;

	for(i=0;i<count;i++,mem++) {
		ch = *mem;
		*buf++ = hexchars[ch>>4];
		*buf++ = hexchars[ch&0x0f];
	}
	*buf = 0;
	return buf;
}