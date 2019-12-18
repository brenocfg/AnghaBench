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
struct TYPE_9__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  addr; } ;
struct TYPE_10__ {TYPE_4__ a4; TYPE_1__ a6; } ;
struct qeth_ipaddr {scalar_t__ proto; TYPE_5__ u; int /*<<< orphan*/ * mac; } ;
struct TYPE_7__ {int /*<<< orphan*/  ip4; int /*<<< orphan*/ * ip6; int /*<<< orphan*/  mac; } ;
struct TYPE_8__ {TYPE_2__ setdelipm; } ;
struct qeth_ipa_cmd {TYPE_3__ data; } ;
struct qeth_cmd_buffer {scalar_t__ data; } ;
struct qeth_card {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 scalar_t__ IPA_PDU_HEADER_SIZE ; 
 int OSA_ADDR_LEN ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ QETH_PROT_IPV6 ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct qeth_cmd_buffer* qeth_get_ipacmd_buffer (struct qeth_card*,int,scalar_t__) ; 
 int qeth_send_ipa_cmd (struct qeth_card*,struct qeth_cmd_buffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qeth_l3_send_setdelmc(struct qeth_card *card,
			struct qeth_ipaddr *addr, int ipacmd)
{
	int rc;
	struct qeth_cmd_buffer *iob;
	struct qeth_ipa_cmd *cmd;

	QETH_DBF_TEXT(TRACE, 4, "setdelmc");

	iob = qeth_get_ipacmd_buffer(card, ipacmd, addr->proto);
	cmd = (struct qeth_ipa_cmd *)(iob->data+IPA_PDU_HEADER_SIZE);
	memcpy(&cmd->data.setdelipm.mac, addr->mac, OSA_ADDR_LEN);
	if (addr->proto == QETH_PROT_IPV6)
		memcpy(cmd->data.setdelipm.ip6, &addr->u.a6.addr,
		       sizeof(struct in6_addr));
	else
		memcpy(&cmd->data.setdelipm.ip4, &addr->u.a4.addr, 4);

	rc = qeth_send_ipa_cmd(card, iob, NULL, NULL);

	return rc;
}