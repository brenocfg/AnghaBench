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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_ctrl_handler {int dummy; } ;
struct v4l2_ctrl_config {scalar_t__ type; void* menu_skip_mask; void* step; int /*<<< orphan*/  qmenu; void* def; void* max; void* min; int /*<<< orphan*/  id; int /*<<< orphan*/ * ops; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;
struct v4l2_ctrl {int dummy; } ;
typedef  void* s32 ;

/* Variables and functions */
 scalar_t__ V4L2_CTRL_TYPE_MENU ; 
 int /*<<< orphan*/  cx2341x_ctrl_fill (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,void**,void**,void**,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx2341x_get_menu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx2341x_ops ; 
 struct v4l2_ctrl* v4l2_ctrl_new_custom (struct v4l2_ctrl_handler*,struct v4l2_ctrl_config*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct v4l2_ctrl *cx2341x_ctrl_new_custom(struct v4l2_ctrl_handler *hdl,
			u32 id, s32 min, s32 max, s32 step, s32 def)
{
	struct v4l2_ctrl_config cfg;

	cx2341x_ctrl_fill(id, &cfg.name, &cfg.type, &min, &max, &step, &def, &cfg.flags);
	cfg.ops = &cx2341x_ops;
	cfg.id = id;
	cfg.min = min;
	cfg.max = max;
	cfg.def = def;
	if (cfg.type == V4L2_CTRL_TYPE_MENU) {
		cfg.step = 0;
		cfg.menu_skip_mask = step;
		cfg.qmenu = cx2341x_get_menu(id);
	} else {
		cfg.step = step;
		cfg.menu_skip_mask = 0;
	}
	return v4l2_ctrl_new_custom(hdl, &cfg, NULL);
}