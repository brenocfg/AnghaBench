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
struct TYPE_5__ {int panel_idx; char* opt_mode; } ;
struct TYPE_4__ {char* name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_2__ drv_info ; 
 scalar_t__ isdigit (char) ; 
 TYPE_1__* known_lcd_panels ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int nocursor ; 
 int /*<<< orphan*/  print_err (char*) ; 
 int /*<<< orphan*/  print_info (char*,...) ; 
 int /*<<< orphan*/  print_warn (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 char* strsep (char**,char*) ; 

int au1100fb_setup(char *options)
{
	char* this_opt;
	int num_panels = ARRAY_SIZE(known_lcd_panels);
	char* mode = NULL;
	int panel_idx = 0;

	if (num_panels <= 0) {
		print_err("No LCD panels supported by driver!");
		return -EFAULT;
			}

	if (options) {
		while ((this_opt = strsep(&options,",")) != NULL) {
			/* Panel option */
			if (!strncmp(this_opt, "panel:", 6)) {
				int i;
				this_opt += 6;
				for (i = 0; i < num_panels; i++) {
					if (!strncmp(this_opt,
					      	     known_lcd_panels[i].name,
							strlen(this_opt))) {
						panel_idx = i;
						break;
					}
				}
				if (i >= num_panels) {
 					print_warn("Panel %s not supported!", this_opt);
				}
			}
			if (!strncmp(this_opt, "nocursor", 8)) {
				this_opt += 8;
				nocursor = 1;
				print_info("Cursor disabled");
			}
			/* Mode option (only option that start with digit) */
			else if (isdigit(this_opt[0])) {
				mode = kstrdup(this_opt, GFP_KERNEL);
				if (!mode) {
					print_err("memory allocation failed");
					return -ENOMEM;
				}
			}
			/* Unsupported option */
			else {
				print_warn("Unsupported option \"%s\"", this_opt);
			}
		}
	}

	drv_info.panel_idx = panel_idx;
	drv_info.opt_mode = mode;

	print_info("Panel=%s Mode=%s",
			known_lcd_panels[drv_info.panel_idx].name,
		      	drv_info.opt_mode ? drv_info.opt_mode : "default");

	return 0;
}