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
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 int /*<<< orphan*/  fb_get_options (int /*<<< orphan*/ ,char**) ; 
 TYPE_1__* known_lcd_panels ; 
 int nohwcursor ; 
 int panel_index ; 
 int /*<<< orphan*/  print_warn (char*,char*) ; 
 long simple_strtol (char*,char**,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static void au1200fb_setup(void)
{
	char* options = NULL;
	char* this_opt;
	int num_panels = ARRAY_SIZE(known_lcd_panels);
	int panel_idx = -1;

	fb_get_options(DRIVER_NAME, &options);

	if (options) {
		while ((this_opt = strsep(&options,",")) != NULL) {
			/* Panel option - can be panel name,
			 * "bs" for board-switch, or number/index */
			if (!strncmp(this_opt, "panel:", 6)) {
				int i;
				long int li;
				char *endptr;
				this_opt += 6;
				/* First check for index, which allows
				 * to short circuit this mess */
				li = simple_strtol(this_opt, &endptr, 0);
				if (*endptr == '\0') {
					panel_idx = (int)li;
				}
				else if (strcmp(this_opt, "bs") == 0) {
					extern int board_au1200fb_panel(void);
					panel_idx = board_au1200fb_panel();
				}

				else
				for (i = 0; i < num_panels; i++) {
					if (!strcmp(this_opt, known_lcd_panels[i].name)) {
						panel_idx = i;
						break;
					}
				}

				if ((panel_idx < 0) || (panel_idx >= num_panels)) {
						print_warn("Panel %s not supported!", this_opt);
				}
				else
					panel_index = panel_idx;
			}

			else if (strncmp(this_opt, "nohwcursor", 10) == 0) {
				nohwcursor = 1;
			}

			/* Unsupported option */
			else {
				print_warn("Unsupported option \"%s\"", this_opt);
			}
		}
	}
}