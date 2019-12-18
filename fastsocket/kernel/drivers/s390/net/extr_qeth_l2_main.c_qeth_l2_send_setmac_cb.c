#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct qeth_reply {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  mac; } ;
struct TYPE_10__ {TYPE_3__ setdelmac; } ;
struct TYPE_7__ {int return_code; } ;
struct qeth_ipa_cmd {TYPE_4__ data; TYPE_1__ hdr; } ;
struct TYPE_8__ {int /*<<< orphan*/  mac_bits; } ;
struct qeth_card {TYPE_6__* dev; TYPE_5__* gdev; TYPE_2__ info; } ;
struct TYPE_12__ {int /*<<< orphan*/  name; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_11__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
#define  IPA_RC_L2_DUP_LAYER3_MAC 131 
#define  IPA_RC_L2_DUP_MAC 130 
#define  IPA_RC_L2_MAC_NOT_AUTH_BY_ADP 129 
#define  IPA_RC_L2_MAC_NOT_AUTH_BY_HYP 128 
 int /*<<< orphan*/  OSA_ADDR_LEN ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT_ (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  QETH_LAYER2_MAC_REGISTERED ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qeth_l2_send_setmac_cb(struct qeth_card *card,
			   struct qeth_reply *reply,
			   unsigned long data)
{
	struct qeth_ipa_cmd *cmd;

	QETH_DBF_TEXT(TRACE, 2, "L2Smaccb");
	cmd = (struct qeth_ipa_cmd *) data;
	if (cmd->hdr.return_code) {
		QETH_DBF_TEXT_(TRACE, 2, "L2er%x", cmd->hdr.return_code);
		card->info.mac_bits &= ~QETH_LAYER2_MAC_REGISTERED;
		switch (cmd->hdr.return_code) {
		case IPA_RC_L2_DUP_MAC:
		case IPA_RC_L2_DUP_LAYER3_MAC:
			dev_warn(&card->gdev->dev,
				"MAC address %pM already exists\n",
				cmd->data.setdelmac.mac);
			break;
		case IPA_RC_L2_MAC_NOT_AUTH_BY_HYP:
		case IPA_RC_L2_MAC_NOT_AUTH_BY_ADP:
			dev_warn(&card->gdev->dev,
				"MAC address %pM is not authorized\n",
				cmd->data.setdelmac.mac);
			break;
		default:
			break;
		}
		cmd->hdr.return_code = -EIO;
	} else {
		card->info.mac_bits |= QETH_LAYER2_MAC_REGISTERED;
		memcpy(card->dev->dev_addr, cmd->data.setdelmac.mac,
		       OSA_ADDR_LEN);
		dev_info(&card->gdev->dev,
			"MAC address %pM successfully registered on "
			"device %s\n",
			card->dev->dev_addr, card->dev->name);
	}
	return 0;
}