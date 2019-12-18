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
struct TYPE_2__ {scalar_t__ type; } ;
struct qeth_card {TYPE_1__ info; } ;

/* Variables and functions */
 scalar_t__ QETH_CARD_TYPE_IQD ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT_ (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  SETUP ; 
 int qeth_alloc_qdio_buffers (struct qeth_card*) ; 
 int qeth_cm_enable (struct qeth_card*) ; 
 int qeth_cm_setup (struct qeth_card*) ; 
 int qeth_dm_act (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_free_qdio_buffers (struct qeth_card*) ; 
 int qeth_issue_next_read (struct qeth_card*) ; 
 int qeth_qdio_activate (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_qdio_clear_card (struct qeth_card*,int) ; 
 int qeth_qdio_establish (struct qeth_card*) ; 
 int qeth_ulp_enable (struct qeth_card*) ; 
 int qeth_ulp_setup (struct qeth_card*) ; 

__attribute__((used)) static int qeth_mpc_initialize(struct qeth_card *card)
{
	int rc;

	QETH_DBF_TEXT(SETUP, 2, "mpcinit");

	rc = qeth_issue_next_read(card);
	if (rc) {
		QETH_DBF_TEXT_(SETUP, 2, "1err%d", rc);
		return rc;
	}
	rc = qeth_cm_enable(card);
	if (rc) {
		QETH_DBF_TEXT_(SETUP, 2, "2err%d", rc);
		goto out_qdio;
	}
	rc = qeth_cm_setup(card);
	if (rc) {
		QETH_DBF_TEXT_(SETUP, 2, "3err%d", rc);
		goto out_qdio;
	}
	rc = qeth_ulp_enable(card);
	if (rc) {
		QETH_DBF_TEXT_(SETUP, 2, "4err%d", rc);
		goto out_qdio;
	}
	rc = qeth_ulp_setup(card);
	if (rc) {
		QETH_DBF_TEXT_(SETUP, 2, "5err%d", rc);
		goto out_qdio;
	}
	rc = qeth_alloc_qdio_buffers(card);
	if (rc) {
		QETH_DBF_TEXT_(SETUP, 2, "5err%d", rc);
		goto out_qdio;
	}
	rc = qeth_qdio_establish(card);
	if (rc) {
		QETH_DBF_TEXT_(SETUP, 2, "6err%d", rc);
		qeth_free_qdio_buffers(card);
		goto out_qdio;
	}
	rc = qeth_qdio_activate(card);
	if (rc) {
		QETH_DBF_TEXT_(SETUP, 2, "7err%d", rc);
		goto out_qdio;
	}
	rc = qeth_dm_act(card);
	if (rc) {
		QETH_DBF_TEXT_(SETUP, 2, "8err%d", rc);
		goto out_qdio;
	}

	return 0;
out_qdio:
	qeth_qdio_clear_card(card, card->info.type != QETH_CARD_TYPE_IQD);
	return rc;
}