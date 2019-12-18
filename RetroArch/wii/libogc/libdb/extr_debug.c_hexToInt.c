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
typedef  int s32 ;

/* Variables and functions */
 int hex (char) ; 

__attribute__((used)) static s32 hexToInt(char **ptr, s32 *ival)
{
	s32 cnt;
	s32 val,nibble;

	val = 0;
	cnt = 0;
	while(**ptr) {
		nibble = hex(**ptr);
		if(nibble<0) break;

		val = (val<<4)|nibble;
		cnt++;

		(*ptr)++;
	}
	*ival = val;
	return cnt;
}