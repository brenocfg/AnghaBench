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
struct TYPE_2__ {int /*<<< orphan*/  iwcm; } ;
struct nes_ib_device {TYPE_1__ ibdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_dealloc_device (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nes_unregister_ofa_device (struct nes_ib_device*) ; 

void nes_destroy_ofa_device(struct nes_ib_device *nesibdev)
{
	if (nesibdev == NULL)
		return;

	nes_unregister_ofa_device(nesibdev);

	kfree(nesibdev->ibdev.iwcm);
	ib_dealloc_device(&nesibdev->ibdev);
}