#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct bd_addr {int dummy; } ;
struct TYPE_4__ {int num_registered; TYPE_1__* registered; } ;
struct TYPE_3__ {int /*<<< orphan*/ * bdaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR (struct bd_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ DISCONNECT_BATTERY_DIED ; 
 scalar_t__ DISCONNECT_POWER_OFF ; 
 scalar_t__ WPAD_STATE_ENABLED ; 
 int /*<<< orphan*/  __wpad_batcb (int) ; 
 TYPE_2__ __wpad_devs ; 
 int /*<<< orphan*/  __wpad_powcb (int) ; 
 scalar_t__ __wpads_inited ; 
 scalar_t__ bd_addr_cmp (struct bd_addr*,struct bd_addr*) ; 

void __wpad_disconnectCB(struct bd_addr *offaddr, u8 reason)
{
	struct bd_addr bdaddr;
	int i;

	if(__wpads_inited == WPAD_STATE_ENABLED) {
        for(i=0;i<__wpad_devs.num_registered;i++) {
            BD_ADDR(&(bdaddr),__wpad_devs.registered[i].bdaddr[5],__wpad_devs.registered[i].bdaddr[4],__wpad_devs.registered[i].bdaddr[3],__wpad_devs.registered[i].bdaddr[2],__wpad_devs.registered[i].bdaddr[1],__wpad_devs.registered[i].bdaddr[0]);
			if(bd_addr_cmp(offaddr,&bdaddr)) {
				if(reason == DISCONNECT_BATTERY_DIED) {
					if(__wpad_batcb) __wpad_batcb(i);		//sanity check since this pointer can be NULL.
				} else if(reason == DISCONNECT_POWER_OFF)
					__wpad_powcb(i);						//no sanity check because there's a default callback iff not otherwise set.
				break;
			}
		}
	}
}