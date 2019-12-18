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
typedef  int u32 ;
struct v4l2_queryctrl {int id; } ;
struct saa7164_vbi_fh {struct saa7164_port* port; } ;
struct saa7164_port {int /*<<< orphan*/  vbi_params; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int EINVAL ; 
 int V4L2_CTRL_FLAG_NEXT_CTRL ; 
 int fill_queryctrl (int /*<<< orphan*/ *,struct v4l2_queryctrl*) ; 
 int /*<<< orphan*/  memset (struct v4l2_queryctrl*,int /*<<< orphan*/ ,int) ; 
 scalar_t__* saa7164_v4l2_ctrls ; 

__attribute__((used)) static int vidioc_queryctrl(struct file *file, void *priv,
	struct v4l2_queryctrl *c)
{
	struct saa7164_vbi_fh *fh = priv;
	struct saa7164_port *port = fh->port;
	int i, next;
	u32 id = c->id;

	memset(c, 0, sizeof(*c));

	next = !!(id & V4L2_CTRL_FLAG_NEXT_CTRL);
	c->id = id & ~V4L2_CTRL_FLAG_NEXT_CTRL;

	for (i = 0; i < ARRAY_SIZE(saa7164_v4l2_ctrls); i++) {
		if (next) {
			if (c->id < saa7164_v4l2_ctrls[i])
				c->id = saa7164_v4l2_ctrls[i];
			else
				continue;
		}

		if (c->id == saa7164_v4l2_ctrls[i])
			return fill_queryctrl(&port->vbi_params, c);

		if (c->id < saa7164_v4l2_ctrls[i])
			break;
	}

	return -EINVAL;
}