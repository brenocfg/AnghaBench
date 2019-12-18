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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  VOID ;

/* Variables and functions */

__inline VOID SW_ULONG_ASSIGN(void *dst, uint32 src)
{
	*((uint8*)dst+0)=*((uint8*)&src+3);
	*((uint8*)dst+1)=*((uint8*)&src+2);
	*((uint8*)dst+2)=*((uint8*)&src+1);
	*((uint8*)dst+3)=*((uint8*)&src+0);

}