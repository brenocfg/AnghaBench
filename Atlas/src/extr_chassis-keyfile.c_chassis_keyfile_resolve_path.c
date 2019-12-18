#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t gint ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_3__ {int arg; int /*<<< orphan*/ *** arg_data; scalar_t__ long_name; } ;
typedef  TYPE_1__ GOptionEntry ;

/* Variables and functions */
#define  G_OPTION_ARG_FILENAME 129 
#define  G_OPTION_ARG_FILENAME_ARRAY 128 
 int /*<<< orphan*/  chassis_resolve_path (char const*,int /*<<< orphan*/ **) ; 

int chassis_keyfile_resolve_path(const char *base_dir, GOptionEntry *config_entries) {
	int entry_idx;

	for (entry_idx = 0; config_entries[entry_idx].long_name; entry_idx++) {
		GOptionEntry entry = config_entries[entry_idx];
		
		switch(entry.arg) {
		case G_OPTION_ARG_FILENAME: {
			gchar **data = entry.arg_data;
			chassis_resolve_path(base_dir, data);
			break;
		}
		case G_OPTION_ARG_FILENAME_ARRAY: {
			gchar ***data = entry.arg_data;
			gchar **files = *data;
			if (NULL != files) {
				gint j;
				for (j = 0; files[j]; j++) chassis_resolve_path(base_dir, &files[j]);
			}
			break;
		}
		default:
			/* ignore other option types */
			break;
		}
	}

	return 0;
}