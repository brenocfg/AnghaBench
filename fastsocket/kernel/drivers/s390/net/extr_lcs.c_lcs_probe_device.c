#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct lcs_card {scalar_t__ thread_running_mask; scalar_t__ thread_allowed_mask; scalar_t__ thread_start_mask; int /*<<< orphan*/  kernel_thread_starter; struct ccwgroup_device* gdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct ccwgroup_device {TYPE_1__** cdev; TYPE_2__ dev; } ;
struct TYPE_5__ {void* handler; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LCS_DBF_TEXT_ (int,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_2__*,struct lcs_card*) ; 
 int /*<<< orphan*/  get_device (TYPE_2__*) ; 
 struct lcs_card* lcs_alloc_card () ; 
 int /*<<< orphan*/  lcs_attr_group ; 
 int /*<<< orphan*/  lcs_free_card (struct lcs_card*) ; 
 void* lcs_irq ; 
 int /*<<< orphan*/  lcs_start_kernel_thread ; 
 int /*<<< orphan*/  put_device (TYPE_2__*) ; 
 int /*<<< orphan*/  setup ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lcs_probe_device(struct ccwgroup_device *ccwgdev)
{
	struct lcs_card *card;
	int ret;

	if (!get_device(&ccwgdev->dev))
		return -ENODEV;

	LCS_DBF_TEXT(2, setup, "add_dev");
        card = lcs_alloc_card();
        if (!card) {
		LCS_DBF_TEXT_(2, setup, "  rc%d", -ENOMEM);
		put_device(&ccwgdev->dev);
                return -ENOMEM;
        }
	ret = sysfs_create_group(&ccwgdev->dev.kobj, &lcs_attr_group);
	if (ret) {
		lcs_free_card(card);
		put_device(&ccwgdev->dev);
		return ret;
        }
	dev_set_drvdata(&ccwgdev->dev, card);
	ccwgdev->cdev[0]->handler = lcs_irq;
	ccwgdev->cdev[1]->handler = lcs_irq;
	card->gdev = ccwgdev;
	INIT_WORK(&card->kernel_thread_starter, lcs_start_kernel_thread);
	card->thread_start_mask = 0;
	card->thread_allowed_mask = 0;
	card->thread_running_mask = 0;
        return 0;
}