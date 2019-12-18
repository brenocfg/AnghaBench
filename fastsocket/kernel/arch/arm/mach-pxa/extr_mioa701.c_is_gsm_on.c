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
 int /*<<< orphan*/  GPIO25_GSM_MOD_ON_STATE ; 
 int /*<<< orphan*/  gpio_get_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_gsm_on(void)
{
	int is_on;

	is_on = !!gpio_get_value(GPIO25_GSM_MOD_ON_STATE);
	return is_on;
}