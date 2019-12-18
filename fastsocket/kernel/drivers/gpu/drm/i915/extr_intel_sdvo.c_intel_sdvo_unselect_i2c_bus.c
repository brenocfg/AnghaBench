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
struct intel_sdvo {int /*<<< orphan*/  i2c; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_gmbus_force_bit (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
intel_sdvo_unselect_i2c_bus(struct intel_sdvo *sdvo)
{
	intel_gmbus_force_bit(sdvo->i2c, false);
}