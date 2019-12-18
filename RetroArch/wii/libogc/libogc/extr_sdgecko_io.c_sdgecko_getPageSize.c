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
 int /*<<< orphan*/ * _ioPageSize ; 

u32 sdgecko_getPageSize(s32 drv_no)
{
	return _ioPageSize[drv_no];
}