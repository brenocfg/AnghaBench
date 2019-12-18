#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  gart_bus_addr; } ;
struct TYPE_3__ {int clear_fake_agp; int /*<<< orphan*/  gma_bus_addr; } ;

/* Variables and functions */
 int EIO ; 
 TYPE_2__* agp_bridge ; 
 int /*<<< orphan*/  intel_enable_gtt () ; 
 TYPE_1__ intel_private ; 

__attribute__((used)) static int intel_fake_agp_configure(void)
{
	if (!intel_enable_gtt())
	    return -EIO;

	intel_private.clear_fake_agp = true;
	agp_bridge->gart_bus_addr = intel_private.gma_bus_addr;

	return 0;
}