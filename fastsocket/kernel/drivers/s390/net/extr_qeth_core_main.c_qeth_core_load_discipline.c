#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* ccwgdriver; } ;
struct qeth_card {TYPE_1__* gdev; TYPE_2__ discipline; } ;
typedef  enum qeth_discipline_id { ____Placeholder_qeth_discipline_id } qeth_discipline_id ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  QETH_DISCIPLINE_LAYER2 129 
#define  QETH_DISCIPLINE_LAYER3 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qeth_l2_ccwgroup_driver ; 
 int /*<<< orphan*/  qeth_l3_ccwgroup_driver ; 
 int /*<<< orphan*/  qeth_mod_mutex ; 
 int /*<<< orphan*/  symbol_get (int /*<<< orphan*/ ) ; 
 void* try_then_request_module (int /*<<< orphan*/ ,char*) ; 

int qeth_core_load_discipline(struct qeth_card *card,
		enum qeth_discipline_id discipline)
{
	int rc = 0;
	mutex_lock(&qeth_mod_mutex);
	switch (discipline) {
	case QETH_DISCIPLINE_LAYER3:
		card->discipline.ccwgdriver = try_then_request_module(
			symbol_get(qeth_l3_ccwgroup_driver),
			"qeth_l3");
		break;
	case QETH_DISCIPLINE_LAYER2:
		card->discipline.ccwgdriver = try_then_request_module(
			symbol_get(qeth_l2_ccwgroup_driver),
			"qeth_l2");
		break;
	}
	if (!card->discipline.ccwgdriver) {
		dev_err(&card->gdev->dev, "There is no kernel module to "
			"support discipline %d\n", discipline);
		rc = -EINVAL;
	}
	mutex_unlock(&qeth_mod_mutex);
	return rc;
}