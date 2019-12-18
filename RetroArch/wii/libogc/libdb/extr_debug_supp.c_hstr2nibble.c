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
typedef  char s32 ;

/* Variables and functions */

s32 hstr2nibble(const char *buf,s32 *nibble)
{
	s32 ch;

	ch = *buf;
	if(ch>='0' && ch<='9') {
		*nibble = ch - '0';
		return 1;
	}
	if(ch>='a' && ch<='f') {
		*nibble = ch - 'a' + 10;
		return 1;
	}
	if(ch>='A' && ch<='F') {
		*nibble = ch - 'A' + 10;
		return 1;
	}
	return 0;
}