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
struct qeth_ipaddr {int /*<<< orphan*/  type; } ;
struct qeth_card {int /*<<< orphan*/  ip_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_IP_TYPE_DEL_ALL_MC ; 
 int /*<<< orphan*/  QETH_PROT_IPV4 ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  __qeth_l3_insert_ip_todo (struct qeth_card*,struct qeth_ipaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qeth_ipaddr*) ; 
 struct qeth_ipaddr* qeth_l3_get_addr_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void qeth_l3_delete_mc_addresses(struct qeth_card *card)
{
	struct qeth_ipaddr *iptodo;
	unsigned long flags;

	QETH_DBF_TEXT(TRACE, 4, "delmc");
	iptodo = qeth_l3_get_addr_buffer(QETH_PROT_IPV4);
	if (!iptodo) {
		QETH_DBF_TEXT(TRACE, 2, "dmcnomem");
		return;
	}
	iptodo->type = QETH_IP_TYPE_DEL_ALL_MC;
	spin_lock_irqsave(&card->ip_lock, flags);
	if (!__qeth_l3_insert_ip_todo(card, iptodo, 0))
		kfree(iptodo);
	spin_unlock_irqrestore(&card->ip_lock, flags);
}