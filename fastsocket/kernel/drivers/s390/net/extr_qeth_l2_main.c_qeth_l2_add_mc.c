#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct qeth_mc_mac {int is_vmac; int /*<<< orphan*/  list; int /*<<< orphan*/  mc_addrlen; int /*<<< orphan*/  mc_addr; } ;
struct qeth_card {int /*<<< orphan*/  mc_list; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IPA_CMD_SETVMAC ; 
 int /*<<< orphan*/  OSA_ADDR_LEN ; 
 int /*<<< orphan*/  kfree (struct qeth_mc_mac*) ; 
 struct qeth_mc_mac* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int qeth_l2_send_setdelmac (struct qeth_card*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int qeth_l2_send_setgroupmac (struct qeth_card*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qeth_l2_add_mc(struct qeth_card *card, __u8 *mac, int vmac)
{
	struct qeth_mc_mac *mc;
	int rc;

	mc = kmalloc(sizeof(struct qeth_mc_mac), GFP_ATOMIC);

	if (!mc)
		return;

	memcpy(mc->mc_addr, mac, OSA_ADDR_LEN);
	mc->mc_addrlen = OSA_ADDR_LEN;
	mc->is_vmac = vmac;

	if (vmac) {
		rc = qeth_l2_send_setdelmac(card, mac, IPA_CMD_SETVMAC,
					NULL);
	} else {
		rc = qeth_l2_send_setgroupmac(card, mac);
	}

	if (!rc)
		list_add_tail(&mc->list, &card->mc_list);
	else
		kfree(mc);
}