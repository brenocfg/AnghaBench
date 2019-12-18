#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* fbdev; int /*<<< orphan*/  (* power_down ) (int /*<<< orphan*/ ) ;TYPE_2__* int_ctrl; TYPE_1__* extif; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* cleanup ) () ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* cleanup ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  OMAPFB_UPDATE_DISABLED ; 
 TYPE_4__ blizzard ; 
 int /*<<< orphan*/  blizzard_set_update_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void blizzard_cleanup(void)
{
	blizzard_set_update_mode(OMAPFB_UPDATE_DISABLED);
	blizzard.extif->cleanup();
	blizzard.int_ctrl->cleanup();
	if (blizzard.power_down != NULL)
		blizzard.power_down(blizzard.fbdev->dev);
}