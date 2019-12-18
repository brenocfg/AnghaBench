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
 int /*<<< orphan*/  ud_bmove ; 
 int /*<<< orphan*/  ud_clear ; 
 int /*<<< orphan*/  ud_clear_margins ; 
 int /*<<< orphan*/  ud_cursor ; 
 int /*<<< orphan*/  ud_putcs ; 
 int /*<<< orphan*/  ud_update_start ; 

void fbcon_rotate_ud(struct fbcon_ops *ops)
{
	ops->bmove = ud_bmove;
	ops->clear = ud_clear;
	ops->putcs = ud_putcs;
	ops->clear_margins = ud_clear_margins;
	ops->cursor = ud_cursor;
	ops->update_start = ud_update_start;
}