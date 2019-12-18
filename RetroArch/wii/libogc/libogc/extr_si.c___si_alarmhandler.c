#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ syswd_t ;
struct TYPE_2__ {int chan; int /*<<< orphan*/  callback; int /*<<< orphan*/  in_bytes; int /*<<< orphan*/  in; int /*<<< orphan*/  out_bytes; int /*<<< orphan*/  out; } ;

/* Variables and functions */
 scalar_t__ __si_transfer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* si_alarm ; 
 TYPE_1__* sipacket ; 

__attribute__((used)) static void __si_alarmhandler(syswd_t thealarm,void *cbarg)
{
	u32 chn = 0;

	while(chn<4)
   {
		if(si_alarm[chn]==thealarm)
         break;
		chn++;
	}
	if(chn==4)
      return;

	if(sipacket[chn].chan!=-1) {
		if(__si_transfer(sipacket[chn].chan,sipacket[chn].out,sipacket[chn].out_bytes,sipacket[chn].in,sipacket[chn].in_bytes,sipacket[chn].callback)) sipacket[chn].chan = -1;
	}
}