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
 scalar_t__ CENTRAL_BUS_ADDR ; 
 int MAX_NATIVE_DEVICES ; 
 int NATIVE_DEVICE_OFFSET ; 
 int /*<<< orphan*/  root ; 
 int /*<<< orphan*/  walk_native_bus (scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 

void walk_central_bus(void)
{
	walk_native_bus(CENTRAL_BUS_ADDR,
			CENTRAL_BUS_ADDR + (MAX_NATIVE_DEVICES * NATIVE_DEVICE_OFFSET),
			&root);
}