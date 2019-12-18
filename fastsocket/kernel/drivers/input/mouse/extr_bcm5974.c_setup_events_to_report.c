#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct input_dev {int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; } ;
struct TYPE_8__ {int /*<<< orphan*/  fuzz; int /*<<< orphan*/  dim; } ;
struct TYPE_7__ {int /*<<< orphan*/  fuzz; int /*<<< orphan*/  dim; } ;
struct TYPE_6__ {int /*<<< orphan*/  fuzz; int /*<<< orphan*/  dim; } ;
struct TYPE_5__ {int /*<<< orphan*/  fuzz; int /*<<< orphan*/  dim; } ;
struct bcm5974_config {TYPE_4__ y; TYPE_3__ x; TYPE_2__ w; TYPE_1__ p; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_TOOL_WIDTH ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_TOOL_DOUBLETAP ; 
 int /*<<< orphan*/  BTN_TOOL_FINGER ; 
 int /*<<< orphan*/  BTN_TOOL_QUADTAP ; 
 int /*<<< orphan*/  BTN_TOOL_TRIPLETAP ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setup_events_to_report(struct input_dev *input_dev,
				   const struct bcm5974_config *cfg)
{
	__set_bit(EV_ABS, input_dev->evbit);

	input_set_abs_params(input_dev, ABS_PRESSURE,
				0, cfg->p.dim, cfg->p.fuzz, 0);
	input_set_abs_params(input_dev, ABS_TOOL_WIDTH,
				0, cfg->w.dim, cfg->w.fuzz, 0);
	input_set_abs_params(input_dev, ABS_X,
				0, cfg->x.dim, cfg->x.fuzz, 0);
	input_set_abs_params(input_dev, ABS_Y,
				0, cfg->y.dim, cfg->y.fuzz, 0);

	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(BTN_TOUCH, input_dev->keybit);
	__set_bit(BTN_TOOL_FINGER, input_dev->keybit);
	__set_bit(BTN_TOOL_DOUBLETAP, input_dev->keybit);
	__set_bit(BTN_TOOL_TRIPLETAP, input_dev->keybit);
	__set_bit(BTN_TOOL_QUADTAP, input_dev->keybit);
	__set_bit(BTN_LEFT, input_dev->keybit);
}