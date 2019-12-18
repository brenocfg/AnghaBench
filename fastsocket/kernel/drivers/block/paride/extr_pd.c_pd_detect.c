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
struct pd_unit {int changed; int drive; int alt_geom; int standby; scalar_t__ gd; scalar_t__ capacity; int /*<<< orphan*/ * pi; int /*<<< orphan*/  name; scalar_t__ access; int /*<<< orphan*/  pia; } ;

/* Variables and functions */
 size_t D_DLY ; 
 size_t D_GEO ; 
 size_t D_MOD ; 
 size_t D_PRO ; 
 size_t D_PRT ; 
 size_t D_SBY ; 
 size_t D_SLV ; 
 size_t D_UNI ; 
 int /*<<< orphan*/  PD_NAMELEN ; 
 int PD_UNITS ; 
 int /*<<< orphan*/  PI_PD ; 
 int /*<<< orphan*/  add_disk (scalar_t__) ; 
 int*** drives ; 
 char* name ; 
 struct pd_unit* pd ; 
 int /*<<< orphan*/  pd_probe_drive (struct pd_unit*) ; 
 int /*<<< orphan*/  pd_scratch ; 
 scalar_t__ pi_init (int /*<<< orphan*/ *,int,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pi_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,char*) ; 
 int /*<<< orphan*/  set_capacity (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int pd_detect(void)
{
	int found = 0, unit, pd_drive_count = 0;
	struct pd_unit *disk;

	for (unit = 0; unit < PD_UNITS; unit++) {
		int *parm = *drives[unit];
		struct pd_unit *disk = pd + unit;
		disk->pi = &disk->pia;
		disk->access = 0;
		disk->changed = 1;
		disk->capacity = 0;
		disk->drive = parm[D_SLV];
		snprintf(disk->name, PD_NAMELEN, "%s%c", name, 'a'+unit);
		disk->alt_geom = parm[D_GEO];
		disk->standby = parm[D_SBY];
		if (parm[D_PRT])
			pd_drive_count++;
	}

	if (pd_drive_count == 0) { /* nothing spec'd - so autoprobe for 1 */
		disk = pd;
		if (pi_init(disk->pi, 1, -1, -1, -1, -1, -1, pd_scratch,
			    PI_PD, verbose, disk->name)) {
			pd_probe_drive(disk);
			if (!disk->gd)
				pi_release(disk->pi);
		}

	} else {
		for (unit = 0, disk = pd; unit < PD_UNITS; unit++, disk++) {
			int *parm = *drives[unit];
			if (!parm[D_PRT])
				continue;
			if (pi_init(disk->pi, 0, parm[D_PRT], parm[D_MOD],
				     parm[D_UNI], parm[D_PRO], parm[D_DLY],
				     pd_scratch, PI_PD, verbose, disk->name)) {
				pd_probe_drive(disk);
				if (!disk->gd)
					pi_release(disk->pi);
			}
		}
	}
	for (unit = 0, disk = pd; unit < PD_UNITS; unit++, disk++) {
		if (disk->gd) {
			set_capacity(disk->gd, disk->capacity);
			add_disk(disk->gd);
			found = 1;
		}
	}
	if (!found)
		printk("%s: no valid drive found\n", name);
	return found;
}