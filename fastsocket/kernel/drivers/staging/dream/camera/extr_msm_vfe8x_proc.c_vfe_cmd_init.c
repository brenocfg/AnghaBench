#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vfe_frame_extra {int dummy; } ;
struct resource {scalar_t__ start; scalar_t__ end; } ;
struct platform_device {int /*<<< orphan*/  name; } ;
struct msm_vfe_callback {scalar_t__ vfe_resp; } ;
struct msm_vfe8x_ctrl {int dummy; } ;
struct TYPE_4__ {int extlen; int /*<<< orphan*/  vfebase; scalar_t__ vfeirq; void* syncdata; int /*<<< orphan*/  tasklet_q; int /*<<< orphan*/  tasklet_lock; int /*<<< orphan*/  io_lock; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  ack_lock; int /*<<< orphan*/  extdata; struct msm_vfe_callback* resp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDBG (char*) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_TRIGGER_RISING ; 
 TYPE_1__* ctrl ; 
 int /*<<< orphan*/  disable_irq (scalar_t__) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioremap (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,scalar_t__) ; 
 int request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct resource* request_mem_region (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfe_parse_irq ; 

int vfe_cmd_init(struct msm_vfe_callback *presp,
	struct platform_device *pdev, void *sdata)
{
	struct resource	*vfemem, *vfeirq, *vfeio;
	int rc;

	vfemem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!vfemem) {
		CDBG("no mem resource?\n");
		return -ENODEV;
	}

	vfeirq = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!vfeirq) {
		CDBG("no irq resource?\n");
		return -ENODEV;
	}

	vfeio = request_mem_region(vfemem->start,
		resource_size(vfemem), pdev->name);
	if (!vfeio) {
		CDBG("VFE region already claimed\n");
		return -EBUSY;
	}

	ctrl =
	kzalloc(sizeof(struct msm_vfe8x_ctrl), GFP_KERNEL);
	if (!ctrl) {
		rc = -ENOMEM;
		goto cmd_init_failed1;
	}

	ctrl->vfeirq  = vfeirq->start;

	ctrl->vfebase =
		ioremap(vfemem->start, (vfemem->end - vfemem->start) + 1);
	if (!ctrl->vfebase) {
		rc = -ENOMEM;
		goto cmd_init_failed2;
	}

	rc = request_irq(ctrl->vfeirq, vfe_parse_irq,
		IRQF_TRIGGER_RISING, "vfe", 0);
	if (rc < 0)
		goto cmd_init_failed2;

	if (presp && presp->vfe_resp)
		ctrl->resp = presp;
	else {
		rc = -EINVAL;
		goto cmd_init_failed3;
	}

	ctrl->extdata =
		kmalloc(sizeof(struct vfe_frame_extra), GFP_KERNEL);
	if (!ctrl->extdata) {
		rc = -ENOMEM;
		goto cmd_init_failed3;
	}

	spin_lock_init(&ctrl->ack_lock);
	spin_lock_init(&ctrl->state_lock);
	spin_lock_init(&ctrl->io_lock);

	ctrl->extlen = sizeof(struct vfe_frame_extra);

	spin_lock_init(&ctrl->tasklet_lock);
	INIT_LIST_HEAD(&ctrl->tasklet_q);

	ctrl->syncdata = sdata;
	return 0;

cmd_init_failed3:
	disable_irq(ctrl->vfeirq);
	free_irq(ctrl->vfeirq, 0);
	iounmap(ctrl->vfebase);
cmd_init_failed2:
	kfree(ctrl);
cmd_init_failed1:
	release_mem_region(vfemem->start, (vfemem->end - vfemem->start) + 1);
	return rc;
}