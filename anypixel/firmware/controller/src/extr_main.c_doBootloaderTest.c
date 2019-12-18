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
 int /*<<< orphan*/  PKT_TYPE_BL_ERASE_FLASH ; 
 int /*<<< orphan*/  PKT_TYPE_BL_READ_BLOCK ; 
 int /*<<< orphan*/  PKT_TYPE_BL_UNLOCK_FLASH ; 
 int /*<<< orphan*/  PKT_TYPE_BL_WRITE_BLOCK ; 
 TYPE_2__* ledpackets ; 

void doBootloaderTest() {
    int i, j;
    uint32_t * payload32 = (uint32_t*)ledpackets[PANEL_NW].s.payload;

    /*for(i = 0; i < 10; i++) {
        ledpackets[PANEL_NW].s.type = PKT_TYPE_BL_READ_BLOCK;
        payload32[0] = 0x08002000+32*i;
        payload32[1] = 0x8;
        BLhelper_dup();
        BLhelper_send();
    }*/

    ledpackets[PANEL_NW].s.type = PKT_TYPE_BL_UNLOCK_FLASH;
    payload32[0] = 0x45670123;
    payload32[1] = 0xCDEF89AB;
    BLhelper_dup();
    BLhelper_send();

    ledpackets[PANEL_NW].s.type = PKT_TYPE_BL_ERASE_FLASH;
    payload32[0] = 0xACEA1623;
    BLhelper_dup();
    BLhelper_send();

    Delay(5000);

    for(i = 0; i < 10; i++) {
        ledpackets[PANEL_NW].s.type = PKT_TYPE_BL_WRITE_BLOCK;
        payload32[0] = 0x08002000+32*i;
        payload32[1] = 0x8;
        for(j = 0; j < 8; j++)
            payload32[2+j] = 8*i+j;
        BLhelper_dup();
        BLhelper_send();
    }

    for(i = 0; i < 10; i++) {
        ledpackets[PANEL_NW].s.type = PKT_TYPE_BL_READ_BLOCK;
        payload32[0] = 0x08002000+32*i;
        payload32[1] = 0x8;
        BLhelper_dup();
        BLhelper_send();
    }

    while(1);

}