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

/* Variables and functions */
#define  SPEED_100 129 
#define  SPEED_1000 128 

__attribute__((used)) static int igb_link_mbps(int internal_link_speed)
{
	switch (internal_link_speed) {
	case SPEED_100:
		return 100;
	case SPEED_1000:
		return 1000;
	default:
		return 0;
	}
}