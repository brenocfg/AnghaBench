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
struct TYPE_3__ {scalar_t__ checksum_type; } ;
struct qeth_card {TYPE_2__* gdev; TYPE_1__ options; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPA_INBOUND_CHECKSUM ; 
 scalar_t__ NO_CHECKSUMMING ; 
 int /*<<< orphan*/  QETH_CARD_IFNAME (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ SW_CHECKSUMMING ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  qeth_is_supported (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int qeth_l3_send_checksum_command (struct qeth_card*) ; 

__attribute__((used)) static int qeth_l3_start_ipa_checksum(struct qeth_card *card)
{
	int rc = 0;

	QETH_DBF_TEXT(TRACE, 3, "strtcsum");

	if (card->options.checksum_type == NO_CHECKSUMMING) {
		dev_info(&card->gdev->dev,
			"Using no checksumming on %s.\n",
			QETH_CARD_IFNAME(card));
		return 0;
	}
	if (card->options.checksum_type == SW_CHECKSUMMING) {
		dev_info(&card->gdev->dev,
			"Using SW checksumming on %s.\n",
			QETH_CARD_IFNAME(card));
		return 0;
	}
	if (!qeth_is_supported(card, IPA_INBOUND_CHECKSUM)) {
		dev_info(&card->gdev->dev,
			"Inbound HW Checksumming not "
			"supported on %s,\ncontinuing "
			"using Inbound SW Checksumming\n",
			QETH_CARD_IFNAME(card));
		card->options.checksum_type = SW_CHECKSUMMING;
		return 0;
	}
	rc = qeth_l3_send_checksum_command(card);
	if (!rc)
		dev_info(&card->gdev->dev,
			"HW Checksumming (inbound) enabled\n");

	return rc;
}