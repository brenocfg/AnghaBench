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
struct fbcon_ops {int /*<<< orphan*/  update_start; int /*<<< orphan*/  cursor; int /*<<< orphan*/  clear_margins; int /*<<< orphan*/  putcs; int /*<<< orphan*/  clear; int /*<<< orphan*/  bmove; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccw_bmove ; 
 int /*<<< orphan*/  ccw_clear ; 
 int /*<<< orphan*/  ccw_clear_margins ; 
 int /*<<< orphan*/  ccw_cursor ; 
 int /*<<< orphan*/  ccw_putcs ; 
 int /*<<< orphan*/  ccw_update_start ; 

void fbcon_rotate_ccw(struct fbcon_ops *ops)
{
	ops->bmove = ccw_bmove;
	ops->clear = ccw_clear;
	ops->putcs = ccw_putcs;
	ops->clear_margins = ccw_clear_margins;
	ops->cursor = ccw_cursor;
	ops->update_start = ccw_update_start;
}