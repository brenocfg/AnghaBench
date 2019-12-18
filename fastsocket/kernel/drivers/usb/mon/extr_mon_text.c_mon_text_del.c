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
struct mon_bus {int /*<<< orphan*/ * dent_s; int /*<<< orphan*/ * dent_t; int /*<<< orphan*/ * dent_u; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ *) ; 

void mon_text_del(struct mon_bus *mbus)
{
	debugfs_remove(mbus->dent_u);
	if (mbus->dent_t != NULL)
		debugfs_remove(mbus->dent_t);
	debugfs_remove(mbus->dent_s);
}