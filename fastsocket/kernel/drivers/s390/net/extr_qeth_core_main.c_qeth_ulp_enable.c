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
struct qeth_cmd_buffer {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {scalar_t__ type; char* portname; scalar_t__ portno; } ;
struct TYPE_5__ {char cm_connection_r; char ulp_filter_w; } ;
struct TYPE_4__ {scalar_t__ layer2; } ;
struct qeth_card {TYPE_3__ info; TYPE_2__ token; TYPE_1__ options; int /*<<< orphan*/  write; } ;
typedef  scalar_t__ __u8 ;

/* Variables and functions */
 scalar_t__ QETH_CARD_TYPE_OSN ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int QETH_MPC_TOKEN_LENGTH ; 
 char QETH_PROT_LAYER2 ; 
 char QETH_PROT_OSN2 ; 
 char QETH_PROT_TCPIP ; 
 int /*<<< orphan*/  QETH_ULP_ENABLE_DEST_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_ULP_ENABLE_FILTER_TOKEN (int /*<<< orphan*/ ) ; 
 scalar_t__* QETH_ULP_ENABLE_LINKNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_ULP_ENABLE_PORTNAME_AND_LL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_ULP_ENABLE_PROT_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SETUP ; 
 char* ULP_ENABLE ; 
 int ULP_ENABLE_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int qeth_send_control_data (struct qeth_card*,int,struct qeth_cmd_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qeth_ulp_enable_cb ; 
 struct qeth_cmd_buffer* qeth_wait_for_buffer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qeth_ulp_enable(struct qeth_card *card)
{
	int rc;
	char prot_type;
	struct qeth_cmd_buffer *iob;

	/*FIXME: trace view callbacks*/
	QETH_DBF_TEXT(SETUP, 2, "ulpenabl");

	iob = qeth_wait_for_buffer(&card->write);
	memcpy(iob->data, ULP_ENABLE, ULP_ENABLE_SIZE);

	*(QETH_ULP_ENABLE_LINKNUM(iob->data)) =
		(__u8) card->info.portno;
	if (card->options.layer2)
		if (card->info.type == QETH_CARD_TYPE_OSN)
			prot_type = QETH_PROT_OSN2;
		else
			prot_type = QETH_PROT_LAYER2;
	else
		prot_type = QETH_PROT_TCPIP;

	memcpy(QETH_ULP_ENABLE_PROT_TYPE(iob->data), &prot_type, 1);
	memcpy(QETH_ULP_ENABLE_DEST_ADDR(iob->data),
	       &card->token.cm_connection_r, QETH_MPC_TOKEN_LENGTH);
	memcpy(QETH_ULP_ENABLE_FILTER_TOKEN(iob->data),
	       &card->token.ulp_filter_w, QETH_MPC_TOKEN_LENGTH);
	memcpy(QETH_ULP_ENABLE_PORTNAME_AND_LL(iob->data),
	       card->info.portname, 9);
	rc = qeth_send_control_data(card, ULP_ENABLE_SIZE, iob,
				    qeth_ulp_enable_cb, NULL);
	return rc;

}