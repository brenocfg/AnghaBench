#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nubus_dir {int /*<<< orphan*/  mask; scalar_t__ done; int /*<<< orphan*/  base; int /*<<< orphan*/  ptr; } ;
struct nubus_dev {TYPE_1__* board; int /*<<< orphan*/  directory; } ;
struct TYPE_2__ {int /*<<< orphan*/  lanes; } ;

/* Variables and functions */

int nubus_get_func_dir(const struct nubus_dev* dev,
		       struct nubus_dir* dir)
{
	dir->ptr = dir->base = dev->directory;
	dir->done = 0;
	dir->mask = dev->board->lanes;
	return 0;
}