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
struct nubus_dirent {int dummy; } ;
struct nubus_dir {int /*<<< orphan*/  mask; scalar_t__ done; int /*<<< orphan*/  base; int /*<<< orphan*/  ptr; } ;
struct nubus_board {int /*<<< orphan*/  lanes; int /*<<< orphan*/  directory; } ;

/* Variables and functions */
 int nubus_get_subdir (struct nubus_dirent*,struct nubus_dir*) ; 
 int nubus_readdir (struct nubus_dir*,struct nubus_dirent*) ; 

int nubus_get_board_dir(const struct nubus_board* board,
			struct nubus_dir* dir)
{
	struct nubus_dirent ent;
	
	dir->ptr = dir->base = board->directory;
	dir->done = 0;
	dir->mask = board->lanes;

	/* Now dereference it (the first directory is always the board
	   directory) */
	if (nubus_readdir(dir, &ent) == -1)
		return -1;
	if (nubus_get_subdir(&ent, dir) == -1)
		return -1;
	return 0;
}