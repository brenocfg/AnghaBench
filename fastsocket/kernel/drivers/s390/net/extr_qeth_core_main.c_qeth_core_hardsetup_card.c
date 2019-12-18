#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ type; scalar_t__ diagass_support; } ;
struct TYPE_7__ {scalar_t__ supported_funcs; } ;
struct TYPE_6__ {scalar_t__ supported_funcs; } ;
struct TYPE_8__ {TYPE_2__ adp; TYPE_1__ ipa4; } ;
struct qeth_card {TYPE_5__* gdev; TYPE_4__ info; TYPE_3__ options; scalar_t__ read_or_write_problem; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  force_alloc_skb; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_DDEV (struct qeth_card*) ; 
 int /*<<< orphan*/  CARD_RDEV (struct qeth_card*) ; 
 int /*<<< orphan*/  CARD_WDEV (struct qeth_card*) ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  IPA_SETADAPTERPARMS ; 
 int /*<<< orphan*/  IPA_SETADP_SET_DIAG_ASSIST ; 
 scalar_t__ QETH_CARD_TYPE_IQD ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT_ (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  QETH_PROT_IPV4 ; 
 int /*<<< orphan*/  SETUP ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccw_device_set_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccw_device_set_online (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ qeth_adp_supported (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_determine_capabilities (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_get_channel_path_desc (struct qeth_card*) ; 
 int qeth_idx_activate_channel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_idx_read_cb ; 
 int /*<<< orphan*/  qeth_idx_write_cb ; 
 int /*<<< orphan*/  qeth_init_func_level (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_init_tokens (struct qeth_card*) ; 
 scalar_t__ qeth_is_supported (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int qeth_mpc_initialize (struct qeth_card*) ; 
 int qeth_qdio_clear_card (struct qeth_card*,int) ; 
 int /*<<< orphan*/  qeth_query_ipassists (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_query_setadapterparms (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_query_setdiagass (struct qeth_card*) ; 

int qeth_core_hardsetup_card(struct qeth_card *card)
{
	int retries = 3;
	int rc;

	QETH_DBF_TEXT(SETUP, 2, "hrdsetup");
	atomic_set(&card->force_alloc_skb, 0);
	qeth_get_channel_path_desc(card);
retry:
	if (retries < 3) {
		QETH_DBF_MESSAGE(2, "%s Retrying to do IDX activates.\n",
			dev_name(&card->gdev->dev));
		ccw_device_set_offline(CARD_DDEV(card));
		ccw_device_set_offline(CARD_WDEV(card));
		ccw_device_set_offline(CARD_RDEV(card));
		ccw_device_set_online(CARD_RDEV(card));
		ccw_device_set_online(CARD_WDEV(card));
		ccw_device_set_online(CARD_DDEV(card));
	}
	rc = qeth_qdio_clear_card(card, card->info.type != QETH_CARD_TYPE_IQD);
	if (rc == -ERESTARTSYS) {
		QETH_DBF_TEXT(SETUP, 2, "break1");
		return rc;
	} else if (rc) {
		QETH_DBF_TEXT_(SETUP, 2, "1err%d", rc);
		if (--retries < 0)
			goto out;
		else
			goto retry;
	}
	qeth_determine_capabilities(card);
	qeth_init_tokens(card);
	qeth_init_func_level(card);
	rc = qeth_idx_activate_channel(&card->read, qeth_idx_read_cb);
	if (rc == -ERESTARTSYS) {
		QETH_DBF_TEXT(SETUP, 2, "break2");
		return rc;
	} else if (rc) {
		QETH_DBF_TEXT_(SETUP, 2, "3err%d", rc);
		if (--retries < 0)
			goto out;
		else
			goto retry;
	}
	rc = qeth_idx_activate_channel(&card->write, qeth_idx_write_cb);
	if (rc == -ERESTARTSYS) {
		QETH_DBF_TEXT(SETUP, 2, "break3");
		return rc;
	} else if (rc) {
		QETH_DBF_TEXT_(SETUP, 2, "4err%d", rc);
		if (--retries < 0)
			goto out;
		else
			goto retry;
	}
	card->read_or_write_problem = 0;
	rc = qeth_mpc_initialize(card);
	if (rc) {
		QETH_DBF_TEXT_(SETUP, 2, "5err%d", rc);
		goto out;
	}

	card->options.ipa4.supported_funcs = 0;
	card->options.adp.supported_funcs = 0;
	card->info.diagass_support = 0;
	qeth_query_ipassists(card, QETH_PROT_IPV4);
	if (qeth_is_supported(card, IPA_SETADAPTERPARMS))
		qeth_query_setadapterparms(card);
	if (qeth_adp_supported(card, IPA_SETADP_SET_DIAG_ASSIST))
		qeth_query_setdiagass(card);
	return 0;
out:
	dev_warn(&card->gdev->dev, "The qeth device driver failed to recover "
		"an error on the device\n");
	QETH_DBF_MESSAGE(2, "%s Initialization in hardsetup failed! rc=%d\n",
		dev_name(&card->gdev->dev), rc);
	return rc;
}