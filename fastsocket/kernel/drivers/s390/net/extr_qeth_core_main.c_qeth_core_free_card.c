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
struct qeth_card {int /*<<< orphan*/  qeth_service_level; struct qeth_card* ip_tbd_list; scalar_t__ dev; int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_DBF_HEX (int /*<<< orphan*/ ,int,struct qeth_card**,int) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  SETUP ; 
 int /*<<< orphan*/  free_netdev (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_clean_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qeth_free_qdio_buffers (struct qeth_card*) ; 
 int /*<<< orphan*/  unregister_service_level (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qeth_core_free_card(struct qeth_card *card)
{

	QETH_DBF_TEXT(SETUP, 2, "freecrd");
	QETH_DBF_HEX(SETUP, 2, &card, sizeof(void *));
	qeth_clean_channel(&card->read);
	qeth_clean_channel(&card->write);
	if (card->dev)
		free_netdev(card->dev);
	kfree(card->ip_tbd_list);
	qeth_free_qdio_buffers(card);
	unregister_service_level(&card->qeth_service_level);
	kfree(card);
}