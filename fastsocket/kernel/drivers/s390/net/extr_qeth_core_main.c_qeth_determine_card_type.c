#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ type; scalar_t__ is_multicast_different; } ;
struct TYPE_7__ {int no_in_queues; scalar_t__ no_out_queues; int /*<<< orphan*/  default_out_queue; int /*<<< orphan*/  do_prio_queueing; } ;
struct qeth_card {TYPE_4__* gdev; TYPE_3__ info; TYPE_2__ qdio; } ;
struct TYPE_6__ {scalar_t__ dev_type; scalar_t__ dev_model; } ;
struct TYPE_10__ {TYPE_1__ id; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 TYPE_5__* CARD_RDEV (struct qeth_card*) ; 
 int ENOENT ; 
 scalar_t__ QETH_CARD_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_DEFAULT_QUEUE ; 
 size_t QETH_DEV_MODEL_IND ; 
 size_t QETH_DEV_TYPE_IND ; 
 size_t QETH_MULTICAST_IND ; 
 int /*<<< orphan*/  QETH_PRIOQ_DEFAULT ; 
 size_t QETH_QUEUE_NO_IND ; 
 int /*<<< orphan*/  SETUP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__** known_devices ; 
 int /*<<< orphan*/  qeth_get_channel_path_desc (struct qeth_card*) ; 

__attribute__((used)) static int qeth_determine_card_type(struct qeth_card *card)
{
	int i = 0;

	QETH_DBF_TEXT(SETUP, 2, "detcdtyp");

	card->qdio.do_prio_queueing = QETH_PRIOQ_DEFAULT;
	card->qdio.default_out_queue = QETH_DEFAULT_QUEUE;
	while (known_devices[i][QETH_DEV_MODEL_IND]) {
		if ((CARD_RDEV(card)->id.dev_type ==
				known_devices[i][QETH_DEV_TYPE_IND]) &&
		    (CARD_RDEV(card)->id.dev_model ==
				known_devices[i][QETH_DEV_MODEL_IND])) {
			card->info.type = known_devices[i][QETH_DEV_MODEL_IND];
			card->qdio.no_out_queues =
				known_devices[i][QETH_QUEUE_NO_IND];
			card->qdio.no_in_queues = 1;
			card->info.is_multicast_different =
				known_devices[i][QETH_MULTICAST_IND];
			qeth_get_channel_path_desc(card);
			return 0;
		}
		i++;
	}
	card->info.type = QETH_CARD_TYPE_UNKNOWN;
	dev_err(&card->gdev->dev, "The adapter hardware is of an "
		"unknown type\n");
	return -ENOENT;
}