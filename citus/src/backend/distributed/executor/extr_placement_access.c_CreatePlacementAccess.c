#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  accessType; int /*<<< orphan*/ * placement; } ;
typedef  int /*<<< orphan*/  ShardPlacementAccessType ;
typedef  TYPE_1__ ShardPlacementAccess ;
typedef  int /*<<< orphan*/  ShardPlacement ;

/* Variables and functions */
 scalar_t__ palloc0 (int) ; 

ShardPlacementAccess *
CreatePlacementAccess(ShardPlacement *placement, ShardPlacementAccessType accessType)
{
	ShardPlacementAccess *placementAccess = NULL;

	placementAccess = (ShardPlacementAccess *) palloc0(sizeof(ShardPlacementAccess));
	placementAccess->placement = placement;
	placementAccess->accessType = accessType;

	return placementAccess;
}