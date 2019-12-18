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
 size_t __card_stopreadresponse (size_t,int /*<<< orphan*/ *,int) ; 
 size_t __check_response (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** _ioResponse ; 

__attribute__((used)) static s32 __card_stopresponse(s32 drv_no)
{
	s32 ret;

	if((ret=__card_stopreadresponse(drv_no,_ioResponse[drv_no],1))!=0) return ret;
	ret = __check_response(drv_no,_ioResponse[drv_no][0]);

	return ret;
}