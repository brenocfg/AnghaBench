#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct map_browser {int /*<<< orphan*/  b; TYPE_2__* map; } ;
struct TYPE_4__ {TYPE_1__* dso; } ;
struct TYPE_3__ {int /*<<< orphan*/  long_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  map_browser__search (struct map_browser*) ; 
 int /*<<< orphan*/  ui_browser__hide (int /*<<< orphan*/ *) ; 
 int ui_browser__run (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ui_browser__show (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int map_browser__run(struct map_browser *self)
{
	int key;

	if (ui_browser__show(&self->b, self->map->dso->long_name,
			     "Press <- or ESC to exit, %s / to search",
			     verbose ? "" : "restart with -v to use") < 0)
		return -1;

	while (1) {
		key = ui_browser__run(&self->b, 0);

		if (verbose && key == '/')
			map_browser__search(self);
		else
			break;
	}

	ui_browser__hide(&self->b);
	return key;
}