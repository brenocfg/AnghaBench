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
typedef  int /*<<< orphan*/  wiimote ;
typedef  size_t u32 ;
struct bd_addr {int dummy; } ;
struct TYPE_4__ {TYPE_1__* active; } ;
struct TYPE_3__ {int /*<<< orphan*/ * bdaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR (struct bd_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t CONF_PAD_MAX_ACTIVE ; 
 size_t WPAD_MAX_WIIMOTES ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (size_t) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (size_t) ; 
 TYPE_2__ __wpad_devs ; 
 int /*<<< orphan*/ ** __wpads ; 
 int __wpads_used ; 
 scalar_t__ bd_addr_cmp (struct bd_addr*,struct bd_addr*) ; 

wiimote *__wpad_assign_slot(struct bd_addr *pad_addr)
{
    u32 i, level;
    struct bd_addr bdaddr;
    //printf("WPAD Assigning slot (active: 0x%02x)\n", __wpads_used);
    _CPU_ISR_Disable(level);

    // Try preassigned slots
    for(i=0; i<CONF_PAD_MAX_ACTIVE /*&& i<WPAD_MAX_WIIMOTES*/; i++) {
        BD_ADDR(&(bdaddr),__wpad_devs.active[i].bdaddr[5],__wpad_devs.active[i].bdaddr[4],__wpad_devs.active[i].bdaddr[3],__wpad_devs.active[i].bdaddr[2],__wpad_devs.active[i].bdaddr[1],__wpad_devs.active[i].bdaddr[0]);
        if(bd_addr_cmp(pad_addr,&bdaddr) && !(__wpads_used & (1<<i))) {
            //printf("WPAD Got Preassigned Slot %d\n", i);
            __wpads_used |= (0x01<<i);
            _CPU_ISR_Restore(level);
            return __wpads[i];
        }
    }

    // No match, pick the first free slot
    for(i=0; i<WPAD_MAX_WIIMOTES; i++) {
        if(!(__wpads_used & (1<<i))) {
            //printf("WPAD Got Free Slot %d\n", i);
            __wpads_used |= (0x01<<i);
            _CPU_ISR_Restore(level);
            return __wpads[i];
        }
    }
    //printf("WPAD All Slots Used\n");
    _CPU_ISR_Restore(level);
    return NULL;
}