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
 int DUPLEX_FULL ; 
#define  SPEED_10 131 
#define  SPEED_100 130 
#define  SPEED_1000 129 
#define  SPEED_10000 128 
 int SUPPORTED_10000baseT_Full ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_1000baseT_Half ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 

__attribute__((used)) static int speed_duplex_to_caps(int speed, int duplex)
{
	int cap = 0;

	switch (speed) {
	case SPEED_10:
		if (duplex == DUPLEX_FULL)
			cap = SUPPORTED_10baseT_Full;
		else
			cap = SUPPORTED_10baseT_Half;
		break;
	case SPEED_100:
		if (duplex == DUPLEX_FULL)
			cap = SUPPORTED_100baseT_Full;
		else
			cap = SUPPORTED_100baseT_Half;
		break;
	case SPEED_1000:
		if (duplex == DUPLEX_FULL)
			cap = SUPPORTED_1000baseT_Full;
		else
			cap = SUPPORTED_1000baseT_Half;
		break;
	case SPEED_10000:
		if (duplex == DUPLEX_FULL)
			cap = SUPPORTED_10000baseT_Full;
	}
	return cap;
}