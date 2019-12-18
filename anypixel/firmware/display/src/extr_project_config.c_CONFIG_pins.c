#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  GPIOx; int /*<<< orphan*/  speed; int /*<<< orphan*/  PuPd; int /*<<< orphan*/  otype; int /*<<< orphan*/  mode; int /*<<< orphan*/  pin; int /*<<< orphan*/  af; int /*<<< orphan*/  pinsource; } ;
struct TYPE_5__ {int /*<<< orphan*/  GPIO_Speed; int /*<<< orphan*/  GPIO_PuPd; int /*<<< orphan*/  GPIO_OType; int /*<<< orphan*/  GPIO_Mode; int /*<<< orphan*/  GPIO_Pin; } ;
typedef  TYPE_1__ GPIO_InitTypeDef ;
typedef  TYPE_2__ CONFIG_Pin_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_Init (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GPIO_PinAFConfig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void CONFIG_pins(const CONFIG_Pin_TypeDef *pins, int num_pins ) {
    GPIO_InitTypeDef  GPIO_InitStructure;
    int i;

    for(i = 0; i < num_pins; i++) {
        //if(pins[i].mode == GPIO_Mode_AF)
        GPIO_PinAFConfig(pins[i].GPIOx, pins[i].pinsource, pins[i].af);

        GPIO_InitStructure.GPIO_Pin = pins[i].pin;
        GPIO_InitStructure.GPIO_Mode = pins[i].mode;
        GPIO_InitStructure.GPIO_OType = pins[i].otype;
        GPIO_InitStructure.GPIO_PuPd = pins[i].PuPd;
        GPIO_InitStructure.GPIO_Speed = pins[i].speed;
        GPIO_Init(pins[i].GPIOx, &GPIO_InitStructure);

    }
}