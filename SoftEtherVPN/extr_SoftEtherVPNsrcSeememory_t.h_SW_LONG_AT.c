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
typedef  scalar_t__ uint8 ;
typedef  int uint32 ;
typedef  int int32 ;

/* Variables and functions */

__inline int32 SW_LONG_AT(void *b, uint32 c)
{
	return	((int32)*((uint8 *)b+c)<<24|
		 (int32)*((uint8 *)b+c+1)<<16|
		 (int32)*((uint8 *)b+c+2)<<8|
		 (int32)*((uint8 *)b+c+3)<<0);
}