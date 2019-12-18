#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  LED_CALC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLC59401_SetValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void TLC59401_Set8bitCalValue(uint8_t index, uint8_t value) {
    TLC59401_SetValue(index, LED_CALC(index, value) );
}