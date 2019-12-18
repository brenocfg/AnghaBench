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
struct TYPE_4__ {int /*<<< orphan*/  seq_print; } ;
struct TYPE_3__ {int layer2; } ;
struct qeth_card {struct qeth_card* ip_tbd_list; int /*<<< orphan*/  read; TYPE_2__ qeth_service_level; TYPE_1__ options; int /*<<< orphan*/  write; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  QETH_DBF_HEX (int /*<<< orphan*/ ,int,struct qeth_card**,int) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  SETUP ; 
 int /*<<< orphan*/  kfree (struct qeth_card*) ; 
 void* kzalloc (int,int) ; 
 int /*<<< orphan*/  qeth_clean_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qeth_core_sl_print ; 
 scalar_t__ qeth_setup_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_service_level (TYPE_2__*) ; 

__attribute__((used)) static struct qeth_card *qeth_alloc_card(void)
{
	struct qeth_card *card;

	QETH_DBF_TEXT(SETUP, 2, "alloccrd");
	card = kzalloc(sizeof(struct qeth_card), GFP_DMA|GFP_KERNEL);
	if (!card)
		goto out;
	QETH_DBF_HEX(SETUP, 2, &card, sizeof(void *));
	card->ip_tbd_list = kzalloc(sizeof(struct list_head), GFP_KERNEL);
	if (!card->ip_tbd_list) {
		QETH_DBF_TEXT(SETUP, 0, "iptbdnom");
		goto out_card;
	}
	if (qeth_setup_channel(&card->read))
		goto out_ip;
	if (qeth_setup_channel(&card->write))
		goto out_channel;
	card->options.layer2 = -1;
	card->qeth_service_level.seq_print = qeth_core_sl_print;
	register_service_level(&card->qeth_service_level);
	return card;

out_channel:
	qeth_clean_channel(&card->read);
out_ip:
	kfree(card->ip_tbd_list);
out_card:
	kfree(card);
out:
	return NULL;
}