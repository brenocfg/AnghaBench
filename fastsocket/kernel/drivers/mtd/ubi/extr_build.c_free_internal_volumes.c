#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ubi_device {int vtbl_slots; TYPE_1__** volumes; } ;
struct TYPE_2__ {struct TYPE_2__* eba_tbl; } ;

/* Variables and functions */
 int UBI_INT_VOL_COUNT ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

__attribute__((used)) static void free_internal_volumes(struct ubi_device *ubi)
{
	int i;

	for (i = ubi->vtbl_slots;
	     i < ubi->vtbl_slots + UBI_INT_VOL_COUNT; i++) {
		kfree(ubi->volumes[i]->eba_tbl);
		kfree(ubi->volumes[i]);
	}
}