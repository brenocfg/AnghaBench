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
struct mirror_set {int /*<<< orphan*/  features; struct dm_target* ti; } ;
struct dm_target {char* error; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_RAID1_HANDLE_ERRORS ; 
 int EINVAL ; 
 int sscanf (char*,char*,unsigned int*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int parse_features(struct mirror_set *ms, unsigned argc, char **argv,
			  unsigned *args_used)
{
	unsigned num_features;
	struct dm_target *ti = ms->ti;
	char dummy;

	*args_used = 0;

	if (!argc)
		return 0;

	if (sscanf(argv[0], "%u%c", &num_features, &dummy) != 1) {
		ti->error = "Invalid number of features";
		return -EINVAL;
	}

	argc--;
	argv++;
	(*args_used)++;

	if (num_features > argc) {
		ti->error = "Not enough arguments to support feature count";
		return -EINVAL;
	}

	if (!strcmp("handle_errors", argv[0]))
		ms->features |= DM_RAID1_HANDLE_ERRORS;
	else {
		ti->error = "Unrecognised feature requested";
		return -EINVAL;
	}

	(*args_used)++;

	return 0;
}