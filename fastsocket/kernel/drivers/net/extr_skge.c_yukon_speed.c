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
typedef  int u16 ;
struct skge_hw {int dummy; } ;

/* Variables and functions */
#define  PHY_M_PS_SPEED_100 129 
#define  PHY_M_PS_SPEED_1000 128 
 int PHY_M_PS_SPEED_MSK ; 
 int SPEED_10 ; 
 int SPEED_100 ; 
 int SPEED_1000 ; 

__attribute__((used)) static u16 yukon_speed(const struct skge_hw *hw, u16 aux)
{
	switch (aux & PHY_M_PS_SPEED_MSK) {
	case PHY_M_PS_SPEED_1000:
		return SPEED_1000;
	case PHY_M_PS_SPEED_100:
		return SPEED_100;
	default:
		return SPEED_10;
	}
}