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
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t s32 ;

/* Variables and functions */
 int /*<<< orphan*/  __card_setblocklen (size_t,int) ; 
 int* _ioPageSize ; 

u32 sdgecko_setPageSize(s32 drv_no, int size)
{
	if(_ioPageSize[drv_no]!=size)
		_ioPageSize[drv_no] = size;

	return __card_setblocklen(drv_no, _ioPageSize[drv_no]);
}