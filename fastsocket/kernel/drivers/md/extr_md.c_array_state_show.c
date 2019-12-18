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
struct mddev {int ro; scalar_t__ raid_disks; scalar_t__ dev_sectors; int /*<<< orphan*/  disks; int /*<<< orphan*/  safemode; int /*<<< orphan*/  flags; int /*<<< orphan*/  in_sync; scalar_t__ pers; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  enum array_state { ____Placeholder_array_state } array_state ;

/* Variables and functions */
 int /*<<< orphan*/  MD_CHANGE_PENDING ; 
 int active ; 
 int active_idle ; 
 char** array_states ; 
 int clean ; 
 int clear ; 
 int inactive ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int read_auto ; 
 int readonly ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int write_pending ; 

__attribute__((used)) static ssize_t
array_state_show(struct mddev *mddev, char *page)
{
	enum array_state st = inactive;

	if (mddev->pers)
		switch(mddev->ro) {
		case 1:
			st = readonly;
			break;
		case 2:
			st = read_auto;
			break;
		case 0:
			if (mddev->in_sync)
				st = clean;
			else if (test_bit(MD_CHANGE_PENDING, &mddev->flags))
				st = write_pending;
			else if (mddev->safemode)
				st = active_idle;
			else
				st = active;
		}
	else {
		if (list_empty(&mddev->disks) &&
		    mddev->raid_disks == 0 &&
		    mddev->dev_sectors == 0)
			st = clear;
		else
			st = inactive;
	}
	return sprintf(page, "%s\n", array_states[st]);
}