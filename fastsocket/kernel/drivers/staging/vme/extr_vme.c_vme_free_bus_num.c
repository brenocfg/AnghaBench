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
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vme_bus_num_mtx ; 
 int vme_bus_numbers ; 

__attribute__((used)) static void vme_free_bus_num(int bus)
{
	mutex_lock(&vme_bus_num_mtx);
	vme_bus_numbers |= ~(0x1 << bus);
	mutex_unlock(&vme_bus_num_mtx);
}