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
typedef  size_t uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  pin; int /*<<< orphan*/  GPIOx; } ;

/* Variables and functions */
 scalar_t__ Bit_SET ; 
 size_t DEBUGPIN_NUM ; 
 scalar_t__ GPIO_ReadInputDataBit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_ResetBits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_SetBits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* pins_debug ; 

inline void DEBUGPIN_Toggle(uint8_t index) {
    assert(index < DEBUGPIN_NUM);
    //GPIO_ToggleBits(pins_debug[index].GPIOx, pins_debug[index].pin);
    //FIXME this implementation is untested and was just implemented since the F0 std lib doesn't seem to include the toggle function (processor doesn't have toggle register)
    if(GPIO_ReadInputDataBit(pins_debug[index].GPIOx,pins_debug[index].pin) == Bit_SET)
        GPIO_ResetBits(pins_debug[index].GPIOx, pins_debug[index].pin);
    else
        GPIO_SetBits(pins_debug[index].GPIOx, pins_debug[index].pin);
}