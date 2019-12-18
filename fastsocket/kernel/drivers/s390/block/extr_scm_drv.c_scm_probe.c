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
struct TYPE_2__ {scalar_t__ oper_state; } ;
struct scm_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; TYPE_1__ attrs; } ;
struct scm_blk_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ OP_STATE_GOOD ; 
 int /*<<< orphan*/  SCM_LOG (int,char*) ; 
 int /*<<< orphan*/  SCM_LOG_STATE (int,struct scm_device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct scm_blk_dev*) ; 
 int /*<<< orphan*/  kfree (struct scm_blk_dev*) ; 
 struct scm_blk_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int scm_blk_dev_setup (struct scm_blk_dev*,struct scm_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int scm_probe(struct scm_device *scmdev)
{
	struct scm_blk_dev *bdev;
	int ret;

	SCM_LOG(2, "probe");
	SCM_LOG_STATE(2, scmdev);

	if (scmdev->attrs.oper_state != OP_STATE_GOOD)
		return -EINVAL;

	bdev = kzalloc(sizeof(*bdev), GFP_KERNEL);
	if (!bdev)
		return -ENOMEM;

	spin_lock_irq(&scmdev->lock);
	dev_set_drvdata(&scmdev->dev, bdev);
	spin_unlock_irq(&scmdev->lock);

	ret = scm_blk_dev_setup(bdev, scmdev);
	if (ret) {
		spin_lock_irq(&scmdev->lock);
		dev_set_drvdata(&scmdev->dev, NULL);
		spin_unlock_irq(&scmdev->lock);
		kfree(bdev);
		goto out;
	}

out:
	return ret;
}