#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct push_switch_platform_info {int irq_flags; scalar_t__ name; int /*<<< orphan*/  irq_handler; } ;
struct TYPE_4__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct push_switch {struct platform_device* pdev; TYPE_1__ debounce; int /*<<< orphan*/  work; } ;
struct TYPE_5__ {struct push_switch_platform_info* platform_data; } ;
struct platform_device {TYPE_2__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ DRV_NAME ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_DISABLED ; 
 int /*<<< orphan*/  dev_attr_switch ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int device_create_file (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int,struct platform_device*) ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct push_switch*) ; 
 struct push_switch* kzalloc (int,int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct push_switch*) ; 
 int request_irq (int,int /*<<< orphan*/ ,int,scalar_t__,struct platform_device*) ; 
 int /*<<< orphan*/  switch_timer ; 
 int /*<<< orphan*/  switch_work_handler ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int switch_drv_probe(struct platform_device *pdev)
{
	struct push_switch_platform_info *psw_info;
	struct push_switch *psw;
	int ret, irq;

	psw = kzalloc(sizeof(struct push_switch), GFP_KERNEL);
	if (unlikely(!psw))
		return -ENOMEM;

	irq = platform_get_irq(pdev, 0);
	if (unlikely(irq < 0)) {
		ret = -ENODEV;
		goto err;
	}

	psw_info = pdev->dev.platform_data;
	BUG_ON(!psw_info);

	ret = request_irq(irq, psw_info->irq_handler,
			  IRQF_DISABLED | psw_info->irq_flags,
			  psw_info->name ? psw_info->name : DRV_NAME, pdev);
	if (unlikely(ret < 0))
		goto err;

	if (psw_info->name) {
		ret = device_create_file(&pdev->dev, &dev_attr_switch);
		if (unlikely(ret)) {
			dev_err(&pdev->dev, "Failed creating device attrs\n");
			ret = -EINVAL;
			goto err_irq;
		}
	}

	INIT_WORK(&psw->work, switch_work_handler);
	init_timer(&psw->debounce);

	psw->debounce.function = switch_timer;
	psw->debounce.data = (unsigned long)psw;

	/* Workqueue API brain-damage */
	psw->pdev = pdev;

	platform_set_drvdata(pdev, psw);

	return 0;

err_irq:
	free_irq(irq, pdev);
err:
	kfree(psw);
	return ret;
}