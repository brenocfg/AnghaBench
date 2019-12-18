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
typedef  union map_info {int dummy; } map_info ;
struct mddev {TYPE_1__* pers; } ;
struct raid_set {struct mddev md; } ;
struct dm_target {struct raid_set* private; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* make_request ) (struct mddev*,struct bio*) ;} ;

/* Variables and functions */
 int DM_MAPIO_SUBMITTED ; 
 int /*<<< orphan*/  stub1 (struct mddev*,struct bio*) ; 

__attribute__((used)) static int raid_map(struct dm_target *ti, struct bio *bio, union map_info *map_context)
{
	struct raid_set *rs = ti->private;
	struct mddev *mddev = &rs->md;

	mddev->pers->make_request(mddev, bio);

	return DM_MAPIO_SUBMITTED;
}