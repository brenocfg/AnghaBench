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
struct TYPE_3__ {scalar_t__ link_type; } ;
struct qeth_card {TYPE_1__ info; TYPE_2__* gdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPA_SETADAPTERPARMS ; 
 int /*<<< orphan*/  IPA_SETADP_ALTER_MAC_ADDRESS ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ QETH_LINK_TYPE_HSTR ; 
 scalar_t__ QETH_LINK_TYPE_LANE_TR ; 
 int /*<<< orphan*/  SETUP ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ qeth_adp_supported (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_is_supported (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int qeth_l3_setadapter_hstr (struct qeth_card*) ; 
 int qeth_query_setadapterparms (struct qeth_card*) ; 
 int qeth_setadpparms_change_macaddr (struct qeth_card*) ; 

__attribute__((used)) static int qeth_l3_setadapter_parms(struct qeth_card *card)
{
	int rc;

	QETH_DBF_TEXT(SETUP, 2, "setadprm");

	if (!qeth_is_supported(card, IPA_SETADAPTERPARMS)) {
		dev_info(&card->gdev->dev,
			"set adapter parameters not supported.\n");
		QETH_DBF_TEXT(SETUP, 2, " notsupp");
		return 0;
	}
	rc = qeth_query_setadapterparms(card);
	if (rc) {
		QETH_DBF_MESSAGE(2, "%s couldn't set adapter parameters: "
			"0x%x\n", dev_name(&card->gdev->dev), rc);
		return rc;
	}
	if (qeth_adp_supported(card, IPA_SETADP_ALTER_MAC_ADDRESS)) {
		rc = qeth_setadpparms_change_macaddr(card);
		if (rc)
			dev_warn(&card->gdev->dev, "Reading the adapter MAC"
				" address failed\n");
	}

	if ((card->info.link_type == QETH_LINK_TYPE_HSTR) ||
	    (card->info.link_type == QETH_LINK_TYPE_LANE_TR))
		rc = qeth_l3_setadapter_hstr(card);

	return rc;
}