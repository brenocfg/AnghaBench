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
struct imon_context {scalar_t__ display_type; int /*<<< orphan*/  touch; int /*<<< orphan*/  touch_y; int /*<<< orphan*/  touch_x; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 scalar_t__ IMON_DISPLAY_TYPE_VGA ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void imon_touch_display_timeout(unsigned long data)
{
	struct imon_context *ictx = (struct imon_context *)data;

	if (ictx->display_type != IMON_DISPLAY_TYPE_VGA)
		return;

	input_report_abs(ictx->touch, ABS_X, ictx->touch_x);
	input_report_abs(ictx->touch, ABS_Y, ictx->touch_y);
	input_report_key(ictx->touch, BTN_TOUCH, 0x00);
	input_sync(ictx->touch);
}