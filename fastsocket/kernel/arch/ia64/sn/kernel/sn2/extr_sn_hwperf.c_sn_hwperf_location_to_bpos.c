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
 int sscanf (char*,char*,int*,char*,int*,int*,...) ; 

__attribute__((used)) static int sn_hwperf_location_to_bpos(char *location,
	int *rack, int *bay, int *slot, int *slab)
{
	char type;

	/* first scan for an old style geoid string */
	if (sscanf(location, "%03d%c%02d#%d",
		rack, &type, bay, slab) == 4)
		*slot = 0; 
	else /* scan for a new bladed geoid string */
	if (sscanf(location, "%03d%c%02d^%02d#%d",
		rack, &type, bay, slot, slab) != 5)
		return -1; 
	/* success */
	return 0;
}