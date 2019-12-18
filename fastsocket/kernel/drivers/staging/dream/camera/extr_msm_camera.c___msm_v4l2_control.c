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
struct msm_sync {int dummy; } ;
struct msm_queue_cmd {struct msm_ctrl_cmd* command; int /*<<< orphan*/  type; } ;
struct msm_ctrl_cmd {scalar_t__ length; int /*<<< orphan*/  value; int /*<<< orphan*/  timeout_ms; } ;
struct msm_control_device_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CDBG (char*,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct msm_queue_cmd*) ; 
 int /*<<< orphan*/  MSM_CAM_Q_V4L2_REQ ; 
 int PTR_ERR (struct msm_queue_cmd*) ; 
 struct msm_queue_cmd* __msm_control (struct msm_sync*,struct msm_control_device_queue*,struct msm_queue_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct msm_queue_cmd*) ; 
 struct msm_queue_cmd* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int __msm_v4l2_control(struct msm_sync *sync,
		struct msm_ctrl_cmd *out)
{
	int rc = 0;

	struct msm_queue_cmd *qcmd = NULL, *rcmd = NULL;
	struct msm_ctrl_cmd *ctrl;
	struct msm_control_device_queue FIXME;

	/* wake up config thread, 4 is for V4L2 application */
	qcmd = kmalloc(sizeof(struct msm_queue_cmd), GFP_KERNEL);
	if (!qcmd) {
		pr_err("msm_control: cannot allocate buffer\n");
		rc = -ENOMEM;
		goto end;
	}
	qcmd->type = MSM_CAM_Q_V4L2_REQ;
	qcmd->command = out;

	rcmd = __msm_control(sync, &FIXME, qcmd, out->timeout_ms);
	if (IS_ERR(rcmd)) {
		rc = PTR_ERR(rcmd);
		goto end;
	}

	ctrl = (struct msm_ctrl_cmd *)(rcmd->command);
	/* FIXME: we should just set out->length = ctrl->length; */
	BUG_ON(out->length < ctrl->length);
	memcpy(out->value, ctrl->value, ctrl->length);

end:
	if (rcmd) kfree(rcmd);
	CDBG("__msm_v4l2_control: end rc = %d\n", rc);
	return rc;
}