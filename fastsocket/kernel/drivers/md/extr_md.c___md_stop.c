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
struct mddev {int /*<<< orphan*/  recovery; TYPE_1__* pers; int /*<<< orphan*/ * to_remove; scalar_t__ ready; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; scalar_t__ sync_request; int /*<<< orphan*/  (* stop ) (struct mddev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MD_RECOVERY_FROZEN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_redundancy_group ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mddev*) ; 

__attribute__((used)) static void __md_stop(struct mddev *mddev)
{
	mddev->ready = 0;
	mddev->pers->stop(mddev);
	if (mddev->pers->sync_request && mddev->to_remove == NULL)
		mddev->to_remove = &md_redundancy_group;
	module_put(mddev->pers->owner);
	mddev->pers = NULL;
	clear_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
}