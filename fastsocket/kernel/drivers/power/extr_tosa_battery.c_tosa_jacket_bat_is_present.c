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
struct tosa_bat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TOSA_GPIO_JACKET_DETECT ; 
 scalar_t__ gpio_get_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool tosa_jacket_bat_is_present(struct tosa_bat *bat)
{
	return gpio_get_value(TOSA_GPIO_JACKET_DETECT) == 0;
}