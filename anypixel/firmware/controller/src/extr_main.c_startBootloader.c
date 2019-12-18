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
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  type; scalar_t__ payload; } ;
struct TYPE_4__ {TYPE_1__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLhelper_dup () ; 
 int /*<<< orphan*/  BLhelper_send () ; 
 int /*<<< orphan*/  Delay (int) ; 
 size_t PANEL_NW ; 
 int /*<<< orphan*/  PKT_TYPE_BL_INIT ; 
 int /*<<< orphan*/  PKT_TYPE_REBOOT ; 
 TYPE_2__* ledpackets ; 

void startBootloader() {
    int i;
    uint32_t * payload32 = (uint32_t*)ledpackets[PANEL_NW].s.payload;

    // send reboot a bunch of times to make sure we get it to work
    for(i = 0; i < 10; i++) {
        ledpackets[PANEL_NW].s.type = PKT_TYPE_REBOOT;
        payload32[0] = 0x816A4EB2;
        BLhelper_dup();
        BLhelper_send();
        Delay(100);
    }
    for(i = 0; i < 10; i++) {
        ledpackets[PANEL_NW].s.type = PKT_TYPE_BL_INIT;
        BLhelper_send();
        Delay(500);
    }
}