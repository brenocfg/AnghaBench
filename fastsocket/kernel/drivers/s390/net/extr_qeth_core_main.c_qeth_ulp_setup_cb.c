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
struct qeth_reply {int dummy; } ;
struct qeth_cmd_buffer {int /*<<< orphan*/  rc; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int /*<<< orphan*/  ulp_connection_r; } ;
struct qeth_card {TYPE_1__* gdev; TYPE_2__ token; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMLINK ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT_ (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_MPC_TOKEN_LENGTH ; 
 int /*<<< orphan*/  QETH_ULP_SETUP_RESP_CONNECTION_TOKEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SETUP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qeth_ulp_setup_cb(struct qeth_card *card, struct qeth_reply *reply,
		unsigned long data)
{
	struct qeth_cmd_buffer *iob;

	QETH_DBF_TEXT(SETUP, 2, "ulpstpcb");

	iob = (struct qeth_cmd_buffer *) data;
	memcpy(&card->token.ulp_connection_r,
	       QETH_ULP_SETUP_RESP_CONNECTION_TOKEN(iob->data),
	       QETH_MPC_TOKEN_LENGTH);
	if (!strncmp("00S", QETH_ULP_SETUP_RESP_CONNECTION_TOKEN(iob->data),
		     3)) {
		QETH_DBF_TEXT(SETUP, 2, "olmlimit");
		dev_err(&card->gdev->dev, "A connection could not be "
			"established because of an OLM limit\n");
		iob->rc = -EMLINK;
	}
	QETH_DBF_TEXT_(SETUP, 2, "  rc%d", iob->rc);
	return 0;
}