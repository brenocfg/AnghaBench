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
typedef  int uint16_t ;
struct intel_dvo_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VR01 ; 
 int VR01_LCD_ENABLE ; 
 int /*<<< orphan*/  ivch_read (struct intel_dvo_device*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool ivch_get_hw_state(struct intel_dvo_device *dvo)
{
	uint16_t vr01;

	/* Set the new power state of the panel. */
	if (!ivch_read(dvo, VR01, &vr01))
		return false;

	if (vr01 & VR01_LCD_ENABLE)
		return true;
	else
		return false;
}