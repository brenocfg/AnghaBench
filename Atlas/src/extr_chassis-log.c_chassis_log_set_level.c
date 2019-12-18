#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t gint ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_4__ {int /*<<< orphan*/  min_lvl; } ;
typedef  TYPE_1__ chassis_log ;
struct TYPE_5__ {int /*<<< orphan*/  lvl; scalar_t__ name; } ;

/* Variables and functions */
 TYPE_2__* log_lvl_map ; 
 scalar_t__ strcmp (scalar_t__,int /*<<< orphan*/  const*) ; 

int chassis_log_set_level(chassis_log *log, const gchar *level) {
	gint i;

	for (i = 0; log_lvl_map[i].name; i++) {
		if (0 == strcmp(log_lvl_map[i].name, level)) {
			log->min_lvl = log_lvl_map[i].lvl;
			return 0;
		}
	}

	return -1;
}