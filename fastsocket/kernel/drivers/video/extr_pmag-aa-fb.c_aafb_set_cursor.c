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
struct aafb_cursor {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct aafb_info {int /*<<< orphan*/  bt431; struct aafb_cursor cursor; } ;

/* Variables and functions */
 int /*<<< orphan*/  bt431_enable_cursor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt431_erase_cursor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt431_position_cursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aafb_set_cursor(struct aafb_info *info, int on)
{
	struct aafb_cursor *c = &info->cursor;

	if (on) {
		bt431_position_cursor(info->bt431, c->x, c->y);
		bt431_enable_cursor(info->bt431);
	} else
		bt431_erase_cursor(info->bt431);
}