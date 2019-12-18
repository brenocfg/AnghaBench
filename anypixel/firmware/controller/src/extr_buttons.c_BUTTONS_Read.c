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
 size_t BUTTONS_POLARITY ; 
 size_t GPIO_ReadInputDataBit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int configured ; 
 TYPE_1__* pin_buttons ; 

uint8_t BUTTONS_Read(uint8_t index) {
	assert(configured == true);

	if(GPIO_ReadInputDataBit(pin_buttons[index].GPIOx, pin_buttons[index].pin) == ((BUTTONS_POLARITY >> index) & 1) )
		return 1;
	else
		return 0;
}