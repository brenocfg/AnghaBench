#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  pin; int /*<<< orphan*/  GPIOx; } ;
typedef  TYPE_1__ CONFIG_Pin_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_ResetBits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_SetBits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void PIN_Num(const CONFIG_Pin_TypeDef *pins, uint16_t state, uint8_t num_pins) {
    int i;
    for(i = 0; i < num_pins; i++) {
        if(state & 1)
            GPIO_SetBits(pins[i].GPIOx, pins[i].pin);
        else
            GPIO_ResetBits(pins[i].GPIOx, pins[i].pin);
        state >>= 1;
    }
}