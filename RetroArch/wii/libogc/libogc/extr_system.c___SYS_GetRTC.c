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
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ __getrtc (int*) ; 

u32 __SYS_GetRTC(u32 *gctime)
{
	u32 cnt,ret;
	u32 time1,time2;

	cnt = 0;
	ret = 0;
	while(cnt<16) {
		if(__getrtc(&time1)==0) ret |= 0x01;
		if(__getrtc(&time2)==0) ret |= 0x02;
		if(ret) return 0;
		if(time1==time2) {
			*gctime = time1;
			return 1;
		}
		cnt++;
	}
	return 0;
}