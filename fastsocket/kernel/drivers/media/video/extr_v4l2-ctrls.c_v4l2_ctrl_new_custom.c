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
struct v4l2_ctrl_config {char* name; char** qmenu; int type; int /*<<< orphan*/  is_volatile; int /*<<< orphan*/  is_private; int /*<<< orphan*/  menu_skip_mask; int /*<<< orphan*/  id; int /*<<< orphan*/  ops; int /*<<< orphan*/  def; int /*<<< orphan*/  step; int /*<<< orphan*/  max; int /*<<< orphan*/  min; int /*<<< orphan*/  flags; } ;
struct v4l2_ctrl {int /*<<< orphan*/  is_volatile; int /*<<< orphan*/  is_private; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  enum v4l2_ctrl_type { ____Placeholder_v4l2_ctrl_type } v4l2_ctrl_type ;

/* Variables and functions */
 scalar_t__ V4L2_CTRL_TYPE_MENU ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_fill (int /*<<< orphan*/ ,char const**,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char** v4l2_ctrl_get_menu (int /*<<< orphan*/ ) ; 
 struct v4l2_ctrl* v4l2_ctrl_new (struct v4l2_ctrl_handler*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const* const*,void*) ; 

struct v4l2_ctrl *v4l2_ctrl_new_custom(struct v4l2_ctrl_handler *hdl,
			const struct v4l2_ctrl_config *cfg, void *priv)
{
	bool is_menu;
	struct v4l2_ctrl *ctrl;
	const char *name = cfg->name;
	const char * const *qmenu = cfg->qmenu;
	enum v4l2_ctrl_type type = cfg->type;
	u32 flags = cfg->flags;
	s32 min = cfg->min;
	s32 max = cfg->max;
	u32 step = cfg->step;
	s32 def = cfg->def;

	if (name == NULL)
		v4l2_ctrl_fill(cfg->id, &name, &type, &min, &max, &step,
								&def, &flags);

	is_menu = (cfg->type == V4L2_CTRL_TYPE_MENU);
	if (is_menu)
		WARN_ON(step);
	else
		WARN_ON(cfg->menu_skip_mask);
	if (is_menu && qmenu == NULL)
		qmenu = v4l2_ctrl_get_menu(cfg->id);

	ctrl = v4l2_ctrl_new(hdl, cfg->ops, cfg->id, name,
			type, min, max,
			is_menu ? cfg->menu_skip_mask : step,
			def, flags, qmenu, priv);
	if (ctrl) {
		ctrl->is_private = cfg->is_private;
		ctrl->is_volatile = cfg->is_volatile;
	}
	return ctrl;
}