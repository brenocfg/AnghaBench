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
struct binder_stats {int* bc; int* br; int* obj_created; int* obj_deleted; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int* binder_command_strings ; 
 int* binder_objstat_strings ; 
 int* binder_return_strings ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,int,int,...) ; 

__attribute__((used)) static char *print_binder_stats(char *buf, char *end, const char *prefix,
				struct binder_stats *stats)
{
	int i;

	BUILD_BUG_ON(ARRAY_SIZE(stats->bc) !=
			ARRAY_SIZE(binder_command_strings));
	for (i = 0; i < ARRAY_SIZE(stats->bc); i++) {
		if (stats->bc[i])
			buf += snprintf(buf, end - buf, "%s%s: %d\n", prefix,
					binder_command_strings[i],
					stats->bc[i]);
		if (buf >= end)
			return buf;
	}

	BUILD_BUG_ON(ARRAY_SIZE(stats->br) !=
			ARRAY_SIZE(binder_return_strings));
	for (i = 0; i < ARRAY_SIZE(stats->br); i++) {
		if (stats->br[i])
			buf += snprintf(buf, end - buf, "%s%s: %d\n", prefix,
					binder_return_strings[i], stats->br[i]);
		if (buf >= end)
			return buf;
	}

	BUILD_BUG_ON(ARRAY_SIZE(stats->obj_created) !=
			ARRAY_SIZE(binder_objstat_strings));
	BUILD_BUG_ON(ARRAY_SIZE(stats->obj_created) !=
			ARRAY_SIZE(stats->obj_deleted));
	for (i = 0; i < ARRAY_SIZE(stats->obj_created); i++) {
		if (stats->obj_created[i] || stats->obj_deleted[i])
			buf += snprintf(buf, end - buf,
					"%s%s: active %d total %d\n", prefix,
					binder_objstat_strings[i],
					stats->obj_created[i] -
						stats->obj_deleted[i],
					stats->obj_created[i]);
		if (buf >= end)
			return buf;
	}
	return buf;
}