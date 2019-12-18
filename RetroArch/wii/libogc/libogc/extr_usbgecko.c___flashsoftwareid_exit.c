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
 scalar_t__ __flashwritecommand (int,int,int) ; 

__attribute__((used)) static int __flashsoftwareid_exit(s32 chn)
{
	s32 ret=0;

	if (__flashwritecommand(chn, 0x5555, 0xAA) && __flashwritecommand(chn, 0x2AAA, 0x55) &&
	    __flashwritecommand(chn, 0x5555, 0xF0))
		ret = 1;

	return ret;
}