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
typedef  int u32 ;
struct e1000_hw {scalar_t__ mac_type; } ;

/* Variables and functions */
 int E1000_COLD_SHIFT ; 
 int E1000_COLLISION_DISTANCE ; 
 int E1000_COLLISION_DISTANCE_82542 ; 
 int E1000_TCTL_COLD ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH () ; 
 int /*<<< orphan*/  TCTL ; 
 scalar_t__ e1000_82543 ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 

void e1000_config_collision_dist(struct e1000_hw *hw)
{
	u32 tctl, coll_dist;

	e_dbg("e1000_config_collision_dist");

	if (hw->mac_type < e1000_82543)
		coll_dist = E1000_COLLISION_DISTANCE_82542;
	else
		coll_dist = E1000_COLLISION_DISTANCE;

	tctl = er32(TCTL);

	tctl &= ~E1000_TCTL_COLD;
	tctl |= coll_dist << E1000_COLD_SHIFT;

	ew32(TCTL, tctl);
	E1000_WRITE_FLUSH();
}