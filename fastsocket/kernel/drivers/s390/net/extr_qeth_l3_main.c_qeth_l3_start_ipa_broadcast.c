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
struct TYPE_5__ {scalar_t__ broadcast_capable; } ;
struct qeth_card {TYPE_3__* dev; TYPE_2__ info; TYPE_1__* gdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IFF_BROADCAST ; 
 int /*<<< orphan*/  IPA_CMD_ASS_CONFIGURE ; 
 int /*<<< orphan*/  IPA_CMD_ASS_ENABLE ; 
 int /*<<< orphan*/  IPA_CMD_ASS_START ; 
 int /*<<< orphan*/  IPA_FILTERING ; 
 scalar_t__ QETH_BROADCAST_WITHOUT_ECHO ; 
 scalar_t__ QETH_BROADCAST_WITH_ECHO ; 
 int /*<<< orphan*/  QETH_CARD_IFNAME (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_is_supported (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int qeth_l3_send_simple_setassparms (struct qeth_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qeth_l3_start_ipa_broadcast(struct qeth_card *card)
{
	int rc;

	QETH_DBF_TEXT(TRACE, 3, "stbrdcst");
	card->info.broadcast_capable = 0;
	if (!qeth_is_supported(card, IPA_FILTERING)) {
		dev_info(&card->gdev->dev,
			"Broadcast not supported on %s\n",
			QETH_CARD_IFNAME(card));
		rc = -EOPNOTSUPP;
		goto out;
	}
	rc = qeth_l3_send_simple_setassparms(card, IPA_FILTERING,
					  IPA_CMD_ASS_START, 0);
	if (rc) {
		dev_warn(&card->gdev->dev, "Enabling broadcast filtering for "
			"%s failed\n", QETH_CARD_IFNAME(card));
		goto out;
	}

	rc = qeth_l3_send_simple_setassparms(card, IPA_FILTERING,
					  IPA_CMD_ASS_CONFIGURE, 1);
	if (rc) {
		dev_warn(&card->gdev->dev,
			"Setting up broadcast filtering for %s failed\n",
			QETH_CARD_IFNAME(card));
		goto out;
	}
	card->info.broadcast_capable = QETH_BROADCAST_WITH_ECHO;
	dev_info(&card->gdev->dev, "Broadcast enabled\n");
	rc = qeth_l3_send_simple_setassparms(card, IPA_FILTERING,
					  IPA_CMD_ASS_ENABLE, 1);
	if (rc) {
		dev_warn(&card->gdev->dev, "Setting up broadcast echo "
			"filtering for %s failed\n", QETH_CARD_IFNAME(card));
		goto out;
	}
	card->info.broadcast_capable = QETH_BROADCAST_WITHOUT_ECHO;
out:
	if (card->info.broadcast_capable)
		card->dev->flags |= IFF_BROADCAST;
	else
		card->dev->flags &= ~IFF_BROADCAST;
	return rc;
}