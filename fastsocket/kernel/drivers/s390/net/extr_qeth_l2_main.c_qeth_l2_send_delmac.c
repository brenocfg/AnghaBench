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
struct TYPE_2__ {int mac_bits; } ;
struct qeth_card {TYPE_1__ info; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  IPA_CMD_DELVMAC ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int QETH_LAYER2_MAC_REGISTERED ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  qeth_l2_send_delmac_cb ; 
 int qeth_l2_send_setdelmac (struct qeth_card*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qeth_l2_send_delmac(struct qeth_card *card, __u8 *mac)
{
	QETH_DBF_TEXT(TRACE, 2, "L2Delmac");
	if (!(card->info.mac_bits & QETH_LAYER2_MAC_REGISTERED))
		return 0;
	return qeth_l2_send_setdelmac(card, mac, IPA_CMD_DELVMAC,
					  qeth_l2_send_delmac_cb);
}