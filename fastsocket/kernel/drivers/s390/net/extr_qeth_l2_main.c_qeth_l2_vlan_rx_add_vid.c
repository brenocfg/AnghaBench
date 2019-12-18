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
struct qeth_vlan_vid {unsigned short vid; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct qeth_card {int /*<<< orphan*/  vlanlock; int /*<<< orphan*/  vid_list; TYPE_1__ info; } ;
struct net_device {struct qeth_card* ml_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IPA_CMD_SETVLAN ; 
 scalar_t__ QETH_CARD_TYPE_OSM ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT_ (int /*<<< orphan*/ ,int,char*,unsigned short) ; 
 int /*<<< orphan*/  QETH_RECOVER_THREAD ; 
 int /*<<< orphan*/  TRACE ; 
 struct qeth_vlan_vid* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qeth_l2_send_setdelvlan (struct qeth_card*,unsigned short,int /*<<< orphan*/ ) ; 
 scalar_t__ qeth_wait_for_threads (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qeth_l2_vlan_rx_add_vid(struct net_device *dev, unsigned short vid)
{
	struct qeth_card *card = dev->ml_priv;
	struct qeth_vlan_vid *id;

	QETH_DBF_TEXT_(TRACE, 4, "aid:%d", vid);
	if (!vid)
		return;
	if (card->info.type == QETH_CARD_TYPE_OSM) {
		QETH_DBF_TEXT(TRACE, 3, "aidOSM");
		return;
	}
	if (qeth_wait_for_threads(card, QETH_RECOVER_THREAD)) {
		QETH_DBF_TEXT(TRACE, 3, "aidREC");
		return;
	}
	id = kmalloc(sizeof(struct qeth_vlan_vid), GFP_ATOMIC);
	if (id) {
		id->vid = vid;
		qeth_l2_send_setdelvlan(card, vid, IPA_CMD_SETVLAN);
		spin_lock_bh(&card->vlanlock);
		list_add_tail(&id->list, &card->vid_list);
		spin_unlock_bh(&card->vlanlock);
	}
}