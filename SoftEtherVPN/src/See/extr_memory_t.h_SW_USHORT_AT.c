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
typedef  int uint16 ;

/* Variables and functions */

__inline uint16 SW_USHORT_AT(void *b, uint32 os)
{
	return ((uint16)
		((uint16)*((uint8 *)b+os+0)<<8|
		 (uint16)*((uint8 *)b+os+1)<<0));
}