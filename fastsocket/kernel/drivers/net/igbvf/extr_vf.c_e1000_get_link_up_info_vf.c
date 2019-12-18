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
typedef  int /*<<< orphan*/  u16 ;
struct e1000_hw {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int E1000_STATUS_FD ; 
 int E1000_STATUS_SPEED_100 ; 
 int E1000_STATUS_SPEED_1000 ; 
 int E1000_SUCCESS ; 
 int /*<<< orphan*/  FULL_DUPLEX ; 
 int /*<<< orphan*/  HALF_DUPLEX ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  STATUS ; 
 int er32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 e1000_get_link_up_info_vf(struct e1000_hw *hw, u16 *speed,
                                     u16 *duplex)
{
	s32 status;

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

	return E1000_SUCCESS;
}