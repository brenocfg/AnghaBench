#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qeth_card {TYPE_1__* gdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_DBF_HEX (int /*<<< orphan*/ ,int,struct qeth_card**,int) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_RECOVER_THREAD ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  __qeth_l3_set_offline (TYPE_1__*,int) ; 
 int __qeth_l3_set_online (TYPE_1__*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  qeth_clear_recovery_task (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_clear_thread_running_bit (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_clear_thread_start_bit (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_close_dev (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_do_run_thread (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_set_recovery_task (struct qeth_card*) ; 

__attribute__((used)) static int qeth_l3_recover(void *ptr)
{
	struct qeth_card *card;
	int rc = 0;

	card = (struct qeth_card *) ptr;
	QETH_DBF_TEXT(TRACE, 2, "recover1");
	QETH_DBF_HEX(TRACE, 2, &card, sizeof(void *));
	if (!qeth_do_run_thread(card, QETH_RECOVER_THREAD))
		return 0;
	QETH_DBF_TEXT(TRACE, 2, "recover2");
	dev_warn(&card->gdev->dev,
		"A recovery process has been started for the device\n");
	qeth_set_recovery_task(card);
	__qeth_l3_set_offline(card->gdev, 1);
	rc = __qeth_l3_set_online(card->gdev, 1);
	if (!rc)
		dev_info(&card->gdev->dev,
			"Device successfully recovered!\n");
	else {
		qeth_close_dev(card);
		dev_warn(&card->gdev->dev, "The qeth device driver "
				"failed to recover an error on the device\n");
	}
	qeth_clear_recovery_task(card);
	qeth_clear_thread_start_bit(card, QETH_RECOVER_THREAD);
	qeth_clear_thread_running_bit(card, QETH_RECOVER_THREAD);
	return 0;
}