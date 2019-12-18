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
struct v4l2_queryctrl {int id; scalar_t__ type; } ;
struct file {int dummy; } ;
struct cx231xx_fh {struct cx231xx* dev; } ;
struct cx231xx {int dummy; } ;
struct TYPE_2__ {struct v4l2_queryctrl v; } ;

/* Variables and functions */
 int CX231XX_CTLS ; 
 int EINVAL ; 
 int V4L2_CID_BASE ; 
 int V4L2_CID_LASTP1 ; 
 int /*<<< orphan*/  call_all (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_queryctrl*) ; 
 int check_dev (struct cx231xx*) ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  ctrl_classes ; 
 TYPE_1__* cx231xx_ctls ; 
 int /*<<< orphan*/  memset (struct v4l2_queryctrl*,int /*<<< orphan*/ ,int) ; 
 struct v4l2_queryctrl no_ctl ; 
 int /*<<< orphan*/  queryctrl ; 
 scalar_t__ unlikely (int) ; 
 int v4l2_ctrl_next (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vidioc_queryctrl(struct file *file, void *priv,
			    struct v4l2_queryctrl *qc)
{
	struct cx231xx_fh *fh = priv;
	struct cx231xx *dev = fh->dev;
	int id = qc->id;
	int i;
	int rc;

	rc = check_dev(dev);
	if (rc < 0)
		return rc;

	qc->id = v4l2_ctrl_next(ctrl_classes, qc->id);
	if (unlikely(qc->id == 0))
		return -EINVAL;

	memset(qc, 0, sizeof(*qc));

	qc->id = id;

	if (qc->id < V4L2_CID_BASE || qc->id >= V4L2_CID_LASTP1)
		return -EINVAL;

	for (i = 0; i < CX231XX_CTLS; i++)
		if (cx231xx_ctls[i].v.id == qc->id)
			break;

	if (i == CX231XX_CTLS) {
		*qc = no_ctl;
		return 0;
	}
	*qc = cx231xx_ctls[i].v;

	call_all(dev, core, queryctrl, qc);

	if (qc->type)
		return 0;
	else
		return -EINVAL;
}