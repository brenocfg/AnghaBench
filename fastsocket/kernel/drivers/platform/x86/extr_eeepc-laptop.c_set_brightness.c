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
struct backlight_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_ASL_PANELBRIGHT ; 
 int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int set_acpi (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int set_brightness(struct backlight_device *bd, int value)
{
	value = max(0, min(15, value));
	return set_acpi(CM_ASL_PANELBRIGHT, value);
}