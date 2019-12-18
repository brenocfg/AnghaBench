#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* ccwgdriver; } ;
struct TYPE_5__ {scalar_t__ type; } ;
struct qeth_card {int /*<<< orphan*/  list; TYPE_3__ discipline; TYPE_1__ info; } ;
struct ccwgroup_device {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  rwlock; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* remove ) (struct ccwgroup_device*) ;} ;

/* Variables and functions */
 scalar_t__ QETH_CARD_TYPE_OSN ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  SETUP ; 
 struct qeth_card* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 TYPE_4__ qeth_core_card_list ; 
 int /*<<< orphan*/  qeth_core_free_card (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_core_free_discipline (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_core_remove_device_attributes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qeth_core_remove_osn_attributes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ccwgroup_device*) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void qeth_core_remove_device(struct ccwgroup_device *gdev)
{
	unsigned long flags;
	struct qeth_card *card = dev_get_drvdata(&gdev->dev);

	QETH_DBF_TEXT(SETUP, 2, "removedv");

	if (card->info.type == QETH_CARD_TYPE_OSN) {
		qeth_core_remove_osn_attributes(&gdev->dev);
	} else {
		qeth_core_remove_device_attributes(&gdev->dev);
	}

	if (card->discipline.ccwgdriver) {
		card->discipline.ccwgdriver->remove(gdev);
		qeth_core_free_discipline(card);
	}

	write_lock_irqsave(&qeth_core_card_list.rwlock, flags);
	list_del(&card->list);
	write_unlock_irqrestore(&qeth_core_card_list.rwlock, flags);
	qeth_core_free_card(card);
	dev_set_drvdata(&gdev->dev, NULL);
	put_device(&gdev->dev);
	return;
}