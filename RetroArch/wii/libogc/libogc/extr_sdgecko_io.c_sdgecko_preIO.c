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
typedef  size_t s32 ;

/* Variables and functions */
 size_t CARDIO_ERROR_READY ; 
 scalar_t__ INITIALIZED ; 
 scalar_t__* _ioFlag ; 
 size_t sdgecko_initIO (size_t) ; 

s32 sdgecko_preIO(s32 drv_no)
{
	s32 ret;

	if(_ioFlag[drv_no]!=INITIALIZED) {
		ret = sdgecko_initIO(drv_no);
		if(ret!=CARDIO_ERROR_READY) {
			return ret;
		}
	}
	return CARDIO_ERROR_READY;
}