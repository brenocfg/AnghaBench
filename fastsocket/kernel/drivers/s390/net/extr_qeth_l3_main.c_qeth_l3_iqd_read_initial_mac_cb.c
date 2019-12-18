#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct qeth_reply {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  unique_id; } ;
struct TYPE_7__ {TYPE_2__ create_destroy_addr; } ;
struct TYPE_5__ {scalar_t__ return_code; } ;
struct qeth_ipa_cmd {TYPE_3__ data; TYPE_1__ hdr; } ;
struct qeth_card {TYPE_4__* dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  random_ether_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qeth_l3_iqd_read_initial_mac_cb(struct qeth_card *card,
		struct qeth_reply *reply, unsigned long data)
{
	struct qeth_ipa_cmd *cmd;

	cmd = (struct qeth_ipa_cmd *) data;
	if (cmd->hdr.return_code == 0)
		memcpy(card->dev->dev_addr,
			cmd->data.create_destroy_addr.unique_id, ETH_ALEN);
	else
		random_ether_addr(card->dev->dev_addr);

	return 0;
}