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
struct qeth_cmd_buffer {scalar_t__ data; } ;
struct qeth_card {scalar_t__ state; int /*<<< orphan*/  write; } ;
struct net_device {struct qeth_card* ml_priv; } ;

/* Variables and functions */
 scalar_t__ CARD_STATE_SOFTSETUP ; 
 scalar_t__ CARD_STATE_UP ; 
 int ENODEV ; 
 scalar_t__ IPA_PDU_HEADER_SIZE ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void*,int) ; 
 int qeth_osn_send_ipa_cmd (struct qeth_card*,struct qeth_cmd_buffer*,int) ; 
 struct qeth_cmd_buffer* qeth_wait_for_buffer (int /*<<< orphan*/ *) ; 

int qeth_osn_assist(struct net_device *dev, void *data, int data_len)
{
	struct qeth_cmd_buffer *iob;
	struct qeth_card *card;
	int rc;

	QETH_DBF_TEXT(TRACE, 2, "osnsdmc");
	if (!dev)
		return -ENODEV;
	card = dev->ml_priv;
	if (!card)
		return -ENODEV;
	if ((card->state != CARD_STATE_UP) &&
	    (card->state != CARD_STATE_SOFTSETUP))
		return -ENODEV;
	iob = qeth_wait_for_buffer(&card->write);
	memcpy(iob->data+IPA_PDU_HEADER_SIZE, data, data_len);
	rc = qeth_osn_send_ipa_cmd(card, iob, data_len);
	return rc;
}