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
 int /*<<< orphan*/  EEEPC_EC_SC02 ; 
 int SENSORS_LIMIT (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ec_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void eeepc_set_fan_pwm(int value)
{
	value = SENSORS_LIMIT(value, 0, 255);
	value = value * 100 / 255;
	ec_write(EEEPC_EC_SC02, value);
}