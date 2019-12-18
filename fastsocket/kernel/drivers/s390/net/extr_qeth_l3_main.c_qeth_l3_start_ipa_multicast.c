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
struct qeth_card {TYPE_1__* dev; TYPE_2__* gdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IFF_MULTICAST ; 
 int /*<<< orphan*/  IPA_CMD_ASS_START ; 
 int /*<<< orphan*/  IPA_MULTICASTING ; 
 int /*<<< orphan*/  QETH_CARD_IFNAME (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_is_supported (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int qeth_l3_send_simple_setassparms (struct qeth_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qeth_l3_start_ipa_multicast(struct qeth_card *card)
{
	int rc;

	QETH_DBF_TEXT(TRACE, 3, "stmcast");

	if (!qeth_is_supported(card, IPA_MULTICASTING)) {
		dev_info(&card->gdev->dev,
			"Multicast not supported on %s\n",
			QETH_CARD_IFNAME(card));
		return -EOPNOTSUPP;
	}

	rc = qeth_l3_send_simple_setassparms(card, IPA_MULTICASTING,
					  IPA_CMD_ASS_START, 0);
	if (rc) {
		dev_warn(&card->gdev->dev,
			"Starting multicast support for %s failed\n",
			QETH_CARD_IFNAME(card));
	} else {
		dev_info(&card->gdev->dev, "Multicast enabled\n");
		card->dev->flags |= IFF_MULTICAST;
	}
	return rc;
}