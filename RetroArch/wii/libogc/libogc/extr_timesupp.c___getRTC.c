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
 int /*<<< orphan*/  EXI_CHANNEL_0 ; 
 int /*<<< orphan*/  EXI_Unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ __getrtc (int*) ; 
 int /*<<< orphan*/  __time_exi_wait () ; 

__attribute__((used)) static u32 __getRTC(u32 *gctime)
{
	u32 cnt,time1,time2;

	__time_exi_wait();

	cnt = 0;

	while(cnt<16) {
		if(__getrtc(&time1)==0
			|| __getrtc(&time2)==0) {
			EXI_Unlock(EXI_CHANNEL_0);
			break;
		}
		if(time1==time2) {
			*gctime = time1;
			EXI_Unlock(EXI_CHANNEL_0);
			return 1;
		}
		cnt++;
	}
	return 0;
}