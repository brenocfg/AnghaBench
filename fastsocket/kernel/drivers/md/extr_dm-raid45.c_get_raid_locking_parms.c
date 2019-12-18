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
struct dm_target {int dummy; } ;
struct dm_raid45_locking_type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,char*) ; 
 int EINVAL ; 
 struct dm_raid45_locking_type locking_none ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strnicmp (char*,char*,size_t) ; 

__attribute__((used)) static int get_raid_locking_parms(struct dm_target *ti, char **argv,
				  int *locking_parms,
				  struct dm_raid45_locking_type **locking_type)
{
	if (!strnicmp(argv[0], "locking", strlen(argv[0]))) {
		char *lckstr = argv[1];
		size_t lcksz = strlen(lckstr);

		if (!strnicmp(lckstr, "none", lcksz)) {
			*locking_type = &locking_none;
			*locking_parms = 2;
		} else if (!strnicmp(lckstr, "cluster", lcksz)) {
			DMERR("locking type \"%s\" not yet implemented",
			      lckstr);
			return -EINVAL;
		} else {
			DMERR("unknown locking type \"%s\"", lckstr);
			return -EINVAL;
		}
	}

	*locking_parms = 0;
	*locking_type = &locking_none;
	return 0;
}