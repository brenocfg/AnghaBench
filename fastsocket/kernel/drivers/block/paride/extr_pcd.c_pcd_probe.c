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
struct pcd_unit {int drive; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcd_identify (struct pcd_unit*,char*) ; 
 int /*<<< orphan*/  pcd_reset (struct pcd_unit*) ; 

__attribute__((used)) static int pcd_probe(struct pcd_unit *cd, int ms, char *id)
{
	if (ms == -1) {
		for (cd->drive = 0; cd->drive <= 1; cd->drive++)
			if (!pcd_reset(cd) && !pcd_identify(cd, id))
				return 0;
	} else {
		cd->drive = ms;
		if (!pcd_reset(cd) && !pcd_identify(cd, id))
			return 0;
	}
	return -1;
}