#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  recover; int /*<<< orphan*/ * output_handler; int /*<<< orphan*/ * input_handler; int /*<<< orphan*/  start_poll; } ;
struct TYPE_5__ {scalar_t__ hwtrap; } ;
struct TYPE_4__ {int layer2; } ;
struct qeth_card {TYPE_3__ discipline; TYPE_2__ info; TYPE_1__ options; int /*<<< orphan*/  mc_list; int /*<<< orphan*/  vid_list; } ;
struct ccwgroup_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  qdio_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct qeth_card* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qeth_l2_recover ; 
 scalar_t__ qeth_qdio_input_handler ; 
 scalar_t__ qeth_qdio_output_handler ; 
 int /*<<< orphan*/  qeth_qdio_start_poll ; 

__attribute__((used)) static int qeth_l2_probe_device(struct ccwgroup_device *gdev)
{
	struct qeth_card *card = dev_get_drvdata(&gdev->dev);

	INIT_LIST_HEAD(&card->vid_list);
	INIT_LIST_HEAD(&card->mc_list);
	card->options.layer2 = 1;
	card->info.hwtrap = 0;
	card->discipline.start_poll = qeth_qdio_start_poll;
	card->discipline.input_handler = (qdio_handler_t *)
		qeth_qdio_input_handler;
	card->discipline.output_handler = (qdio_handler_t *)
		qeth_qdio_output_handler;
	card->discipline.recover = qeth_l2_recover;
	return 0;
}