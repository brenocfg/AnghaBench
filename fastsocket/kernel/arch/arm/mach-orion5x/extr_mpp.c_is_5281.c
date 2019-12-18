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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ MV88F5281_DEV_ID ; 
 int /*<<< orphan*/  orion5x_pcie_id (scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int is_5281(void)
{
	u32 dev;
	u32 rev;

	orion5x_pcie_id(&dev, &rev);

	return !!(dev == MV88F5281_DEV_ID);
}