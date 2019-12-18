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
struct qeth_rx {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  large_send; int /*<<< orphan*/  sniffer; } ;
struct TYPE_5__ {scalar_t__ hwtrap; } ;
struct qeth_card {int state; int lan_online; int /*<<< orphan*/  discipline_mutex; int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/  dev; TYPE_3__ options; TYPE_2__* gdev; int /*<<< orphan*/  rx; TYPE_1__ info; } ;
struct TYPE_8__ {int /*<<< orphan*/  kobj; } ;
struct ccwgroup_device {TYPE_4__ dev; } ;
typedef  enum qeth_card_states { ____Placeholder_qeth_card_states } qeth_card_states ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CARD_DDEV (struct qeth_card*) ; 
 int /*<<< orphan*/  CARD_RDEV (struct qeth_card*) ; 
 int CARD_STATE_DOWN ; 
 int CARD_STATE_HARDSETUP ; 
 int CARD_STATE_RECOVER ; 
 int CARD_STATE_SOFTSETUP ; 
 int /*<<< orphan*/  CARD_WDEV (struct qeth_card*) ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int /*<<< orphan*/  QETH_DBF_HEX (int /*<<< orphan*/ ,int,struct qeth_card**,int) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT_ (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  QETH_DIAGS_CMD_TRAP ; 
 int /*<<< orphan*/  QETH_DIAGS_TRAP_ARM ; 
 int /*<<< orphan*/  SETUP ; 
 int /*<<< orphan*/  __qeth_l3_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccw_device_set_offline (int /*<<< orphan*/ ) ; 
 int ccw_device_set_online (int /*<<< orphan*/ ) ; 
 struct qeth_card* dev_get_drvdata (TYPE_4__*) ; 
 int /*<<< orphan*/  dev_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_disable (int /*<<< orphan*/ ) ; 
 int qeth_core_hardsetup_card (struct qeth_card*) ; 
 scalar_t__ qeth_hw_trap (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int qeth_init_qdio_queues (struct qeth_card*) ; 
 scalar_t__ qeth_is_diagass_supported (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_l3_set_ip_addr_list (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_l3_set_large_send (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_l3_set_multicast_list (int /*<<< orphan*/ ) ; 
 int qeth_l3_setadapter_parms (struct qeth_card*) ; 
 int qeth_l3_setrouting_v4 (struct qeth_card*) ; 
 int qeth_l3_setrouting_v6 (struct qeth_card*) ; 
 scalar_t__ qeth_l3_setup_netdev (struct qeth_card*) ; 
 int qeth_l3_start_ipassists (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_l3_stop_card (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_print_status_message (struct qeth_card*) ; 
 int qeth_send_startlan (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_set_allowed_threads (struct qeth_card*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static int __qeth_l3_set_online(struct ccwgroup_device *gdev, int recovery_mode)
{
	struct qeth_card *card = dev_get_drvdata(&gdev->dev);
	int rc = 0;
	enum qeth_card_states recover_flag;

	BUG_ON(!card);
	mutex_lock(&card->discipline_mutex);
	mutex_lock(&card->conf_mutex);
	QETH_DBF_TEXT(SETUP, 2, "setonlin");
	QETH_DBF_HEX(SETUP, 2, &card, sizeof(void *));

	recover_flag = card->state;
	rc = ccw_device_set_online(CARD_RDEV(card));
	if (rc) {
		QETH_DBF_TEXT_(SETUP, 2, "1err%d", rc);
		rc = -EIO;
		goto out;
	}
	rc = ccw_device_set_online(CARD_WDEV(card));
	if (rc) {
		QETH_DBF_TEXT_(SETUP, 2, "1err%d", rc);
		rc = -EIO;
		goto out;
	}
	rc = ccw_device_set_online(CARD_DDEV(card));
	if (rc) {
		QETH_DBF_TEXT_(SETUP, 2, "1err%d", rc);
		rc = -EIO;
		goto out;
	}

	rc = qeth_core_hardsetup_card(card);
	if (rc) {
		QETH_DBF_TEXT_(SETUP, 2, "2err%d", rc);
		goto out_remove;
	}

	if (!card->dev && qeth_l3_setup_netdev(card))
		goto out_remove;

	if (qeth_is_diagass_supported(card, QETH_DIAGS_CMD_TRAP)) {
		if (card->info.hwtrap &&
		    qeth_hw_trap(card, QETH_DIAGS_TRAP_ARM))
			card->info.hwtrap = 0;
	} else
		card->info.hwtrap = 0;

	card->state = CARD_STATE_HARDSETUP;
	memset(&card->rx, 0, sizeof(struct qeth_rx));
	qeth_print_status_message(card);

	/* softsetup */
	QETH_DBF_TEXT(SETUP, 2, "softsetp");

	rc = qeth_send_startlan(card);
	if (rc) {
		QETH_DBF_TEXT_(SETUP, 2, "1err%d", rc);
		if (rc == 0xe080) {
			dev_warn(&card->gdev->dev,
				"The LAN is offline\n");
			card->lan_online = 0;
			goto contin;
		}
		rc = -ENODEV;
		goto out_remove;
	} else
		card->lan_online = 1;

contin:
	rc = qeth_l3_setadapter_parms(card);
	if (rc)
		QETH_DBF_TEXT_(SETUP, 2, "2err%d", rc);
	if (!card->options.sniffer) {
		rc = qeth_l3_start_ipassists(card);
		if (rc) {
			QETH_DBF_TEXT_(SETUP, 2, "3err%d", rc);
			goto out_remove;
		}
		qeth_l3_set_large_send(card, card->options.large_send);
		rc = qeth_l3_setrouting_v4(card);
		if (rc)
			QETH_DBF_TEXT_(SETUP, 2, "4err%d", rc);
		rc = qeth_l3_setrouting_v6(card);
		if (rc)
			QETH_DBF_TEXT_(SETUP, 2, "5err%d", rc);
	}
	netif_tx_disable(card->dev);

	rc = qeth_init_qdio_queues(card);
	if (rc) {
		QETH_DBF_TEXT_(SETUP, 2, "6err%d", rc);
		goto out_remove;
	}
	card->state = CARD_STATE_SOFTSETUP;

	qeth_set_allowed_threads(card, 0xffffffff, 0);
	qeth_l3_set_ip_addr_list(card);
	if (card->lan_online)
		netif_carrier_on(card->dev);
	else
		netif_carrier_off(card->dev);
	if (recover_flag == CARD_STATE_RECOVER) {
		if (recovery_mode)
			__qeth_l3_open(card->dev);
		else {
			rtnl_lock();
			dev_open(card->dev);
			rtnl_unlock();
		}
		qeth_l3_set_multicast_list(card->dev);
	}
	/* let user_space know that device is online */
	kobject_uevent(&gdev->dev.kobj, KOBJ_CHANGE);
out:
	mutex_unlock(&card->conf_mutex);
	mutex_unlock(&card->discipline_mutex);
	return rc;
out_remove:
	qeth_l3_stop_card(card, 0);
	ccw_device_set_offline(CARD_DDEV(card));
	ccw_device_set_offline(CARD_WDEV(card));
	ccw_device_set_offline(CARD_RDEV(card));
	if (recover_flag == CARD_STATE_RECOVER)
		card->state = CARD_STATE_RECOVER;
	else
		card->state = CARD_STATE_DOWN;
	mutex_unlock(&card->conf_mutex);
	mutex_unlock(&card->discipline_mutex);
	return -ENODEV;
}