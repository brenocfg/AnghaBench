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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {scalar_t__ pfxlen; int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {scalar_t__ mask; int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_2__ a6; TYPE_1__ a4; } ;
struct qeth_ipaddr {int /*<<< orphan*/  del_flags; int /*<<< orphan*/  set_flags; int /*<<< orphan*/  type; TYPE_3__ u; } ;
struct qeth_card {int /*<<< orphan*/  ip_lock; int /*<<< orphan*/ * ip_tbd_list; int /*<<< orphan*/  ip_list; } ;
typedef  enum qeth_prot_versions { ____Placeholder_qeth_prot_versions } qeth_prot_versions ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_IPA_DELIP_VIPA_FLAG ; 
 int /*<<< orphan*/  QETH_IPA_SETIP_VIPA_FLAG ; 
 int /*<<< orphan*/  QETH_IP_TYPE_VIPA ; 
 int QETH_PROT_IPV4 ; 
 int QETH_PROT_IPV6 ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  kfree (struct qeth_ipaddr*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  qeth_l3_add_ip (struct qeth_card*,struct qeth_ipaddr*) ; 
 scalar_t__ qeth_l3_address_exists_in_list (int /*<<< orphan*/ *,struct qeth_ipaddr*,int /*<<< orphan*/ ) ; 
 struct qeth_ipaddr* qeth_l3_get_addr_buffer (int) ; 
 int /*<<< orphan*/  qeth_l3_set_ip_addr_list (struct qeth_card*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int qeth_l3_add_vipa(struct qeth_card *card, enum qeth_prot_versions proto,
	      const u8 *addr)
{
	struct qeth_ipaddr *ipaddr;
	unsigned long flags;
	int rc = 0;

	ipaddr = qeth_l3_get_addr_buffer(proto);
	if (ipaddr) {
		if (proto == QETH_PROT_IPV4) {
			QETH_DBF_TEXT(TRACE, 2, "addvipa4");
			memcpy(&ipaddr->u.a4.addr, addr, 4);
			ipaddr->u.a4.mask = 0;
		} else if (proto == QETH_PROT_IPV6) {
			QETH_DBF_TEXT(TRACE, 2, "addvipa6");
			memcpy(&ipaddr->u.a6.addr, addr, 16);
			ipaddr->u.a6.pfxlen = 0;
		}
		ipaddr->type = QETH_IP_TYPE_VIPA;
		ipaddr->set_flags = QETH_IPA_SETIP_VIPA_FLAG;
		ipaddr->del_flags = QETH_IPA_DELIP_VIPA_FLAG;
	} else
		return -ENOMEM;
	spin_lock_irqsave(&card->ip_lock, flags);
	if (qeth_l3_address_exists_in_list(&card->ip_list, ipaddr, 0) ||
	    qeth_l3_address_exists_in_list(card->ip_tbd_list, ipaddr, 0))
		rc = -EEXIST;
	spin_unlock_irqrestore(&card->ip_lock, flags);
	if (rc) {
		return rc;
	}
	if (!qeth_l3_add_ip(card, ipaddr))
		kfree(ipaddr);
	qeth_l3_set_ip_addr_list(card);
	return rc;
}