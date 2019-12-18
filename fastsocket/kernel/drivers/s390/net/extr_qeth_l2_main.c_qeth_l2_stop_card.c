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
struct TYPE_4__ {scalar_t__ state; } ;
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  mac_bits; } ;
struct qeth_card {scalar_t__ state; TYPE_2__ write; TYPE_2__ read; TYPE_1__ info; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CARD_STATE_DOWN ; 
 scalar_t__ CARD_STATE_HARDSETUP ; 
 scalar_t__ CARD_STATE_SOFTSETUP ; 
 scalar_t__ CARD_STATE_UP ; 
 scalar_t__ CH_STATE_UP ; 
 scalar_t__ QETH_CARD_TYPE_OSN ; 
 int /*<<< orphan*/  QETH_DBF_HEX (int /*<<< orphan*/ ,int,struct qeth_card**,int) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_LAYER2_MAC_REGISTERED ; 
 int /*<<< orphan*/  SETUP ; 
 int /*<<< orphan*/  dev_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_clear_cmd_buffers (TYPE_2__*) ; 
 int /*<<< orphan*/  qeth_clear_ipacmd_list (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_clear_qdio_buffers (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_clear_working_pool_list (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_l2_del_all_mc (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_l2_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_qdio_clear_card (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_set_allowed_threads (struct qeth_card*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static int qeth_l2_stop_card(struct qeth_card *card, int recovery_mode)
{
	int rc = 0;

	QETH_DBF_TEXT(SETUP , 2, "stopcard");
	QETH_DBF_HEX(SETUP, 2, &card, sizeof(void *));

	qeth_set_allowed_threads(card, 0, 1);
	if (card->read.state == CH_STATE_UP &&
	    card->write.state == CH_STATE_UP &&
	    (card->state == CARD_STATE_UP)) {
		if (recovery_mode &&
		    card->info.type != QETH_CARD_TYPE_OSN) {
			qeth_l2_stop(card->dev);
		} else {
			rtnl_lock();
			dev_close(card->dev);
			rtnl_unlock();
		}
		card->info.mac_bits &= ~QETH_LAYER2_MAC_REGISTERED;
		card->state = CARD_STATE_SOFTSETUP;
	}
	if (card->state == CARD_STATE_SOFTSETUP) {
		qeth_l2_del_all_mc(card, 0);
		qeth_clear_ipacmd_list(card);
		card->state = CARD_STATE_HARDSETUP;
	}
	if (card->state == CARD_STATE_HARDSETUP) {
		qeth_qdio_clear_card(card, 0);
		qeth_clear_qdio_buffers(card);
		qeth_clear_working_pool_list(card);
		card->state = CARD_STATE_DOWN;
	}
	if (card->state == CARD_STATE_DOWN) {
		qeth_clear_cmd_buffers(&card->read);
		qeth_clear_cmd_buffers(&card->write);
	}
	return rc;
}