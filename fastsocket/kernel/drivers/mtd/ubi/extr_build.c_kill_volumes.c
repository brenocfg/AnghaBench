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
struct ubi_device {int vtbl_slots; scalar_t__* volumes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ubi_free_volume (struct ubi_device*,scalar_t__) ; 

__attribute__((used)) static void kill_volumes(struct ubi_device *ubi)
{
	int i;

	for (i = 0; i < ubi->vtbl_slots; i++)
		if (ubi->volumes[i])
			ubi_free_volume(ubi, ubi->volumes[i]);
}