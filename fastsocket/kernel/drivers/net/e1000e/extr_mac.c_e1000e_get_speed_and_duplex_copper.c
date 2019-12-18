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
typedef  scalar_t__ u16 ;
struct e1000_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int E1000_STATUS_FD ; 
 int E1000_STATUS_SPEED_100 ; 
 int E1000_STATUS_SPEED_1000 ; 
 scalar_t__ FULL_DUPLEX ; 
 scalar_t__ HALF_DUPLEX ; 
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_100 ; 
 scalar_t__ SPEED_1000 ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  e_dbg (char*,int,char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 

s32 e1000e_get_speed_and_duplex_copper(struct e1000_hw *hw, u16 *speed,
				       u16 *duplex)
{
	u32 status;

	status = er32(STATUS);
	if (status & E1000_STATUS_SPEED_1000)
		*speed = SPEED_1000;
	else if (status & E1000_STATUS_SPEED_100)
		*speed = SPEED_100;
	else
		*speed = SPEED_10;

	if (status & E1000_STATUS_FD)
		*duplex = FULL_DUPLEX;
	else
		*duplex = HALF_DUPLEX;

	e_dbg("%u Mbps, %s Duplex\n",
	      *speed == SPEED_1000 ? 1000 : *speed == SPEED_100 ? 100 : 10,
	      *duplex == FULL_DUPLEX ? "Full" : "Half");

	return 0;
}