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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
typedef  scalar_t__ s64 ;
struct TYPE_2__ {int chan; scalar_t__ fire; int /*<<< orphan*/  callback; int /*<<< orphan*/  in_bytes; int /*<<< orphan*/  in; int /*<<< orphan*/  out_bytes; int /*<<< orphan*/  out; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_CancelAlarm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __si_transfer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gettime () ; 
 int /*<<< orphan*/ * si_alarm ; 
 TYPE_1__* sipacket ; 

__attribute__((used)) static void __si_transfernext(u32 chan)
{
	u32 cnt;
	u64 now;
	s64 diff;
	cnt = 0;
	while(cnt<4) {
		chan++;
		chan %= 4;
		if(sipacket[chan].chan!=-1) {
			now = gettime();
			diff = (now - sipacket[chan].fire);
			if(diff>=0) {
				if(!__si_transfer(sipacket[chan].chan,sipacket[chan].out,sipacket[chan].out_bytes,sipacket[chan].in,sipacket[chan].in_bytes,sipacket[chan].callback)) break;
				SYS_CancelAlarm(si_alarm[chan]);
				sipacket[chan].chan = -1;
			}
		}
		cnt++;
	}
}