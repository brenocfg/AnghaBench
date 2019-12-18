#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_4__ {int paths; char** path; int /*<<< orphan*/  can_be_active; } ;
typedef  TYPE_1__ importargs_t ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  UMEM_NOFAIL ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  dump_nvlist (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fatal (char*,int) ; 
 int /*<<< orphan*/  g_zfs ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 scalar_t__ nvpair_value_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ pool_match (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int strlen (char*) ; 
 char* strpbrk (char*,char*) ; 
 char* strstr (char*,char*) ; 
 char* umem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify (int) ; 
 int /*<<< orphan*/ * zpool_search_import (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static char *
find_zpool(char **target, nvlist_t **configp, int dirc, char **dirv)
{
	nvlist_t *pools;
	nvlist_t *match = NULL;
	char *name = NULL;
	char *sepp = NULL;
	char sep = '\0';
	int count = 0;
	importargs_t args;

	bzero(&args, sizeof (args));
	args.paths = dirc;
	args.path = dirv;
	args.can_be_active = B_TRUE;

	if ((sepp = strpbrk(*target, "/@")) != NULL) {
		sep = *sepp;
		*sepp = '\0';
	}

	pools = zpool_search_import(g_zfs, &args);

	if (pools != NULL) {
		nvpair_t *elem = NULL;
		while ((elem = nvlist_next_nvpair(pools, elem)) != NULL) {
			verify(nvpair_value_nvlist(elem, configp) == 0);
			if (pool_match(*configp, *target)) {
				count++;
				if (match != NULL) {
					/* print previously found config */
					if (name != NULL) {
						(void) printf("%s\n", name);
						dump_nvlist(match, 8);
						name = NULL;
					}
					(void) printf("%s\n",
					    nvpair_name(elem));
					dump_nvlist(*configp, 8);
				} else {
					match = *configp;
					name = nvpair_name(elem);
				}
			}
		}
	}
	if (count > 1)
		(void) fatal("\tMatched %d pools - use pool GUID "
		    "instead of pool name or \n"
		    "\tpool name part of a dataset name to select pool", count);

	if (sepp)
		*sepp = sep;
	/*
	 * If pool GUID was specified for pool id, replace it with pool name
	 */
	if (name && (strstr(*target, name) != *target)) {
		int sz = 1 + strlen(name) + ((sepp) ? strlen(sepp) : 0);

		*target = umem_alloc(sz, UMEM_NOFAIL);
		(void) snprintf(*target, sz, "%s%s", name, sepp ? sepp : "");
	}

	*configp = name ? match : NULL;

	return (name);
}