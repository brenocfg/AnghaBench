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
typedef  int /*<<< orphan*/  u32 ;
struct ar9170 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR9170_GPIO_REG_PORT_DATA ; 
 int carl9170_write_reg (struct ar9170*,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

int carl9170_led_set_state(struct ar9170 *ar, const u32 led_state)
{
	return carl9170_write_reg(ar, AR9170_GPIO_REG_PORT_DATA, led_state);
}