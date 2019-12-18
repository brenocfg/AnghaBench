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
struct dm_target {char* error; } ;
struct dm_dirty_log {int dummy; } ;

/* Variables and functions */
 struct dm_dirty_log* dm_dirty_log_create (char*,struct dm_target*,int /*<<< orphan*/ ,unsigned int,char**) ; 
 int /*<<< orphan*/  mirror_flush ; 
 int sscanf (char*,char*,unsigned int*,char*) ; 

__attribute__((used)) static struct dm_dirty_log *create_dirty_log(struct dm_target *ti,
					     unsigned argc, char **argv,
					     unsigned *args_used)
{
	unsigned param_count;
	struct dm_dirty_log *dl;
	char dummy;

	if (argc < 2) {
		ti->error = "Insufficient mirror log arguments";
		return NULL;
	}

	if (sscanf(argv[1], "%u%c", &param_count, &dummy) != 1) {
		ti->error = "Invalid mirror log argument count";
		return NULL;
	}

	*args_used = 2 + param_count;

	if (argc < *args_used) {
		ti->error = "Insufficient mirror log arguments";
		return NULL;
	}

	dl = dm_dirty_log_create(argv[0], ti, mirror_flush, param_count,
				 argv + 2);
	if (!dl) {
		ti->error = "Error creating mirror dirty log";
		return NULL;
	}

	return dl;
}