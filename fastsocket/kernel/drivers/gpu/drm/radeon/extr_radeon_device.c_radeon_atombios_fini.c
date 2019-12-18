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
struct TYPE_3__ {TYPE_2__* atom_card_info; TYPE_2__* atom_context; } ;
struct radeon_device {TYPE_1__ mode_info; } ;
struct TYPE_4__ {struct TYPE_4__* scratch; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 

void radeon_atombios_fini(struct radeon_device *rdev)
{
	if (rdev->mode_info.atom_context) {
		kfree(rdev->mode_info.atom_context->scratch);
	}
	kfree(rdev->mode_info.atom_context);
	rdev->mode_info.atom_context = NULL;
	kfree(rdev->mode_info.atom_card_info);
	rdev->mode_info.atom_card_info = NULL;
}