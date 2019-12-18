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
struct qeth_card {int /*<<< orphan*/ * dev; int /*<<< orphan*/  wait_q; } ;
struct ccwgroup_device {scalar_t__ state; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CCWGROUP_ONLINE ; 
 struct qeth_card* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qeth_l3_clear_ip_list (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_l3_clear_ipato_list (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_l3_remove_device_attributes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qeth_l3_set_offline (struct ccwgroup_device*) ; 
 int /*<<< orphan*/  qeth_set_allowed_threads (struct qeth_card*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qeth_threads_running (struct qeth_card*,int) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qeth_l3_remove_device(struct ccwgroup_device *cgdev)
{
	struct qeth_card *card = dev_get_drvdata(&cgdev->dev);

	qeth_l3_remove_device_attributes(&cgdev->dev);

	qeth_set_allowed_threads(card, 0, 1);
	wait_event(card->wait_q, qeth_threads_running(card, 0xffffffff) == 0);

	if (cgdev->state == CCWGROUP_ONLINE)
		qeth_l3_set_offline(cgdev);

	if (card->dev) {
		unregister_netdev(card->dev);
		card->dev = NULL;
	}

	qeth_l3_clear_ip_list(card, 0);
	qeth_l3_clear_ipato_list(card);
	return;
}