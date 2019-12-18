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

/* Variables and functions */
 int /*<<< orphan*/  LED_B ; 
 int /*<<< orphan*/  LED_OFF ; 
 int /*<<< orphan*/  board_led_operation (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void board_prov_complete(void)
{
    board_led_operation(LED_B, LED_OFF);
}