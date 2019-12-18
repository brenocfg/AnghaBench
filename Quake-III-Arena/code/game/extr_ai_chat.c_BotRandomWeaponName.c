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
 double random () ; 

char *BotRandomWeaponName(void) {
	int rnd;

#ifdef MISSIONPACK
	rnd = random() * 11.9;
#else
	rnd = random() * 8.9;
#endif
	switch(rnd) {
		case 0: return "Gauntlet";
		case 1: return "Shotgun";
		case 2: return "Machinegun";
		case 3: return "Grenade Launcher";
		case 4: return "Rocket Launcher";
		case 5: return "Plasmagun";
		case 6: return "Railgun";
		case 7: return "Lightning Gun";
#ifdef MISSIONPACK
		case 8: return "Nailgun";
		case 9: return "Chaingun";
		case 10: return "Proximity Launcher";
#endif
		default: return "BFG10K";
	}
}