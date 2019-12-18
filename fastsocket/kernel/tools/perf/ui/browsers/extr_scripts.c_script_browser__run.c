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
struct perf_script_browser {int /*<<< orphan*/  b; int /*<<< orphan*/  script_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ui_browser__hide (int /*<<< orphan*/ *) ; 
 int ui_browser__run (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ui_browser__show (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int script_browser__run(struct perf_script_browser *self)
{
	int key;

	if (ui_browser__show(&self->b, self->script_name,
			     "Press <- or ESC to exit") < 0)
		return -1;

	while (1) {
		key = ui_browser__run(&self->b, 0);

		/* We can add some special key handling here if needed */
		break;
	}

	ui_browser__hide(&self->b);
	return key;
}