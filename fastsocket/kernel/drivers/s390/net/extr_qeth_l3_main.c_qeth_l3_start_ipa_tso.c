#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ large_send; } ;
struct qeth_card {TYPE_3__* dev; TYPE_2__ options; TYPE_1__* gdev; } ;
struct TYPE_6__ {int features; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IPA_CMD_ASS_START ; 
 int /*<<< orphan*/  IPA_OUTBOUND_TSO ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int /*<<< orphan*/  QETH_CARD_IFNAME (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ QETH_LARGE_SEND_NO ; 
 scalar_t__ QETH_LARGE_SEND_TSO ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_is_supported (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int qeth_l3_send_simple_setassparms (struct qeth_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qeth_l3_start_ipa_tso(struct qeth_card *card)
{
	int rc;

	QETH_DBF_TEXT(TRACE, 3, "sttso");

	if (!qeth_is_supported(card, IPA_OUTBOUND_TSO)) {
		dev_info(&card->gdev->dev,
			"Outbound TSO not supported on %s\n",
			QETH_CARD_IFNAME(card));
		rc = -EOPNOTSUPP;
	} else {
		rc = qeth_l3_send_simple_setassparms(card, IPA_OUTBOUND_TSO,
						IPA_CMD_ASS_START, 0);
		if (rc)
			dev_warn(&card->gdev->dev, "Starting outbound TCP "
				"segmentation offload for %s failed\n",
				QETH_CARD_IFNAME(card));
		else
			dev_info(&card->gdev->dev,
				"Outbound TSO enabled\n");
	}
	if (rc && (card->options.large_send == QETH_LARGE_SEND_TSO)) {
		card->options.large_send = QETH_LARGE_SEND_NO;
		card->dev->features &= ~(NETIF_F_TSO | NETIF_F_SG);
	}
	return rc;
}