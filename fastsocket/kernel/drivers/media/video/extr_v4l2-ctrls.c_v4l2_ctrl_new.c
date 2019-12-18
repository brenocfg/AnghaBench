#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct v4l2_ctrl_ops {int dummy; } ;
struct v4l2_ctrl_handler {int /*<<< orphan*/  lock; int /*<<< orphan*/  ctrls; scalar_t__ error; } ;
struct TYPE_2__ {char* string; scalar_t__ val; } ;
struct v4l2_ctrl {char const* name; int type; char const* const* qmenu; char* string; int /*<<< orphan*/  node; scalar_t__ minimum; TYPE_1__ cur; scalar_t__ default_value; scalar_t__ val; void* priv; scalar_t__ step; scalar_t__ maximum; scalar_t__ flags; scalar_t__ id; struct v4l2_ctrl_ops const* ops; struct v4l2_ctrl_handler* handler; } ;
typedef  scalar_t__ s32 ;
typedef  enum v4l2_ctrl_type { ____Placeholder_v4l2_ctrl_type } v4l2_ctrl_type ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ V4L2_CID_PRIVATE_BASE ; 
 scalar_t__ V4L2_CTRL_FLAG_READ_ONLY ; 
 scalar_t__ V4L2_CTRL_FLAG_WRITE_ONLY ; 
 int V4L2_CTRL_TYPE_BOOLEAN ; 
 int V4L2_CTRL_TYPE_BUTTON ; 
 int V4L2_CTRL_TYPE_CTRL_CLASS ; 
 int V4L2_CTRL_TYPE_INTEGER ; 
 int V4L2_CTRL_TYPE_MENU ; 
 int V4L2_CTRL_TYPE_STRING ; 
 scalar_t__ handler_new_ref (struct v4l2_ctrl_handler*,struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  handler_set_err (struct v4l2_ctrl_handler*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct v4l2_ctrl*) ; 
 struct v4l2_ctrl* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,char,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct v4l2_ctrl *v4l2_ctrl_new(struct v4l2_ctrl_handler *hdl,
			const struct v4l2_ctrl_ops *ops,
			u32 id, const char *name, enum v4l2_ctrl_type type,
			s32 min, s32 max, u32 step, s32 def,
			u32 flags, const char * const *qmenu, void *priv)
{
	struct v4l2_ctrl *ctrl;
	unsigned sz_extra = 0;

	if (hdl->error)
		return NULL;

	/* Sanity checks */
	if (id == 0 || name == NULL || id >= V4L2_CID_PRIVATE_BASE ||
	    max < min ||
	    (type == V4L2_CTRL_TYPE_INTEGER && step == 0) ||
	    (type == V4L2_CTRL_TYPE_MENU && qmenu == NULL) ||
	    (type == V4L2_CTRL_TYPE_STRING && max == 0)) {
		handler_set_err(hdl, -ERANGE);
		return NULL;
	}
	if ((type == V4L2_CTRL_TYPE_INTEGER ||
	     type == V4L2_CTRL_TYPE_MENU ||
	     type == V4L2_CTRL_TYPE_BOOLEAN) &&
	    (def < min || def > max)) {
		handler_set_err(hdl, -ERANGE);
		return NULL;
	}

	if (type == V4L2_CTRL_TYPE_BUTTON)
		flags |= V4L2_CTRL_FLAG_WRITE_ONLY;
	else if (type == V4L2_CTRL_TYPE_CTRL_CLASS)
		flags |= V4L2_CTRL_FLAG_READ_ONLY;
	else if (type == V4L2_CTRL_TYPE_STRING)
		sz_extra += 2 * (max + 1);

	ctrl = kzalloc(sizeof(*ctrl) + sz_extra, GFP_KERNEL);
	if (ctrl == NULL) {
		handler_set_err(hdl, -ENOMEM);
		return NULL;
	}

	INIT_LIST_HEAD(&ctrl->node);
	ctrl->handler = hdl;
	ctrl->ops = ops;
	ctrl->id = id;
	ctrl->name = name;
	ctrl->type = type;
	ctrl->flags = flags;
	ctrl->minimum = min;
	ctrl->maximum = max;
	ctrl->step = step;
	ctrl->qmenu = qmenu;
	ctrl->priv = priv;
	ctrl->cur.val = ctrl->val = ctrl->default_value = def;

	if (ctrl->type == V4L2_CTRL_TYPE_STRING) {
		ctrl->cur.string = (char *)&ctrl[1] + sz_extra - (max + 1);
		ctrl->string = (char *)&ctrl[1] + sz_extra - 2 * (max + 1);
		if (ctrl->minimum)
			memset(ctrl->cur.string, ' ', ctrl->minimum);
	}
	if (handler_new_ref(hdl, ctrl)) {
		kfree(ctrl);
		return NULL;
	}
	mutex_lock(&hdl->lock);
	list_add_tail(&ctrl->node, &hdl->ctrls);
	mutex_unlock(&hdl->lock);
	return ctrl;
}