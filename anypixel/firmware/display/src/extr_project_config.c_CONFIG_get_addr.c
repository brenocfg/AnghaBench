#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  pin; int /*<<< orphan*/  GPIOx; } ;

/* Variables and functions */
 int ADDRPIN_NUM ; 
 int /*<<< orphan*/  ADDRPIN_POWER_AHB ; 
 scalar_t__ Bit_SET ; 
 int /*<<< orphan*/  CONFIG_pins (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ENABLE ; 
 scalar_t__ GPIO_ReadInputDataBit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCC_AHBPeriphClockCmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* pins_addrPD ; 
 TYPE_1__* pins_addrPU ; 
 int /*<<< orphan*/  usleep (int) ; 

uint32_t CONFIG_get_addr(void) {
    uint32_t low = 0, high = 0;
    int i;
    RCC_AHBPeriphClockCmd(ADDRPIN_POWER_AHB, ENABLE);
    // capture the values in both pull up and pull down
    CONFIG_pins(pins_addrPD, ADDRPIN_NUM);
    usleep(5000);
    for(i = ADDRPIN_NUM-1; i >= 0; i--) {
        if( GPIO_ReadInputDataBit(pins_addrPD[i].GPIOx, pins_addrPD[i].pin) == Bit_SET)
            low = (low << 1) | 1;
        else
            low = (low << 1);
    }
    CONFIG_pins(pins_addrPU, ADDRPIN_NUM);
    usleep(5000);
    for(i = ADDRPIN_NUM-1; i >= 0; i--) {
        if( GPIO_ReadInputDataBit(pins_addrPU[i].GPIOx, pins_addrPU[i].pin) == Bit_SET)
            high = (high << 1) | 1;
        else
            high = (high << 1);
    }
    if(low == high)
        return high;
    else
        return 4;
}