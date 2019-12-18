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
struct mca_find_device_by_slot_info {int slot; struct mca_device* mca_dev; } ;
struct mca_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_for_each_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct mca_find_device_by_slot_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mca_bus_type ; 
 int /*<<< orphan*/  mca_find_device_by_slot_callback ; 

struct mca_device *mca_find_device_by_slot(int slot)
{
	struct mca_find_device_by_slot_info info;

	info.slot = slot;
	info.mca_dev = NULL;

	bus_for_each_dev(&mca_bus_type, NULL, &info, mca_find_device_by_slot_callback);

	return info.mca_dev;
}