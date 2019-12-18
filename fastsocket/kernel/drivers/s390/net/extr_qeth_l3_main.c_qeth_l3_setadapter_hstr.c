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
struct TYPE_2__ {scalar_t__ broadcast_mode; scalar_t__ macaddr_mode; } ;
struct qeth_card {TYPE_1__ options; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_BUS_ID (struct qeth_card*) ; 
 int /*<<< orphan*/  IPA_SETADP_ALTER_MAC_ADDRESS ; 
 int /*<<< orphan*/  IPA_SETADP_SET_BROADCAST_MODE ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ QETH_TR_BROADCAST_LOCAL ; 
 scalar_t__ QETH_TR_MACADDR_CANONICAL ; 
 int /*<<< orphan*/  TRACE ; 
 scalar_t__ qeth_adp_supported (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int qeth_l3_send_setadp_mode (struct qeth_card*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int qeth_l3_setadapter_hstr(struct qeth_card *card)
{
	int rc;

	QETH_DBF_TEXT(TRACE, 4, "adphstr");

	if (qeth_adp_supported(card, IPA_SETADP_SET_BROADCAST_MODE)) {
		rc = qeth_l3_send_setadp_mode(card,
					IPA_SETADP_SET_BROADCAST_MODE,
					card->options.broadcast_mode);
		if (rc)
			QETH_DBF_MESSAGE(2, "couldn't set broadcast mode on "
				   "device %s: x%x\n",
				   CARD_BUS_ID(card), rc);
		rc = qeth_l3_send_setadp_mode(card,
					IPA_SETADP_ALTER_MAC_ADDRESS,
					card->options.macaddr_mode);
		if (rc)
			QETH_DBF_MESSAGE(2, "couldn't set macaddr mode on "
				   "device %s: x%x\n", CARD_BUS_ID(card), rc);
		return rc;
	}
	if (card->options.broadcast_mode == QETH_TR_BROADCAST_LOCAL)
		QETH_DBF_MESSAGE(2, "set adapter parameters not available "
			   "to set broadcast mode, using ALLRINGS "
			   "on device %s:\n", CARD_BUS_ID(card));
	if (card->options.macaddr_mode == QETH_TR_MACADDR_CANONICAL)
		QETH_DBF_MESSAGE(2, "set adapter parameters not available "
			   "to set macaddr mode, using NONCANONICAL "
			   "on device %s:\n", CARD_BUS_ID(card));
	return 0;
}