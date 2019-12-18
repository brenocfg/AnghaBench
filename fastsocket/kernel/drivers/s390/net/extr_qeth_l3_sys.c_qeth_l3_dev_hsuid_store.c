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
struct TYPE_9__ {int* s6_addr32; char* s6_addr; } ;
struct TYPE_11__ {scalar_t__ pfxlen; TYPE_3__ addr; } ;
struct TYPE_12__ {TYPE_5__ a6; } ;
struct qeth_ipaddr {void* type; TYPE_6__ u; } ;
struct TYPE_10__ {scalar_t__ cq; char* hsuid; scalar_t__ sniffer; } ;
struct TYPE_7__ {scalar_t__ type; } ;
struct qeth_card {scalar_t__ state; TYPE_4__ options; TYPE_2__* dev; TYPE_1__ info; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_8__ {int /*<<< orphan*/  perm_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASCEBC (char*,int) ; 
 scalar_t__ CARD_STATE_DOWN ; 
 scalar_t__ CARD_STATE_RECOVER ; 
 size_t EINVAL ; 
 size_t ENOMEM ; 
 size_t EPERM ; 
 scalar_t__ QETH_CARD_TYPE_IQD ; 
 int /*<<< orphan*/  QETH_CQ_DISABLED ; 
 int /*<<< orphan*/  QETH_CQ_ENABLED ; 
 scalar_t__ QETH_CQ_NOTAVAILABLE ; 
 void* QETH_IP_TYPE_NORMAL ; 
 int /*<<< orphan*/  QETH_PROT_IPV6 ; 
 struct qeth_card* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  kfree (struct qeth_ipaddr*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ qeth_configure_cq (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_l3_add_ip (struct qeth_card*,struct qeth_ipaddr*) ; 
 int /*<<< orphan*/  qeth_l3_delete_ip (struct qeth_card*,struct qeth_ipaddr*) ; 
 struct qeth_ipaddr* qeth_l3_get_addr_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_l3_set_ip_addr_list (struct qeth_card*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static ssize_t qeth_l3_dev_hsuid_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct qeth_card *card = dev_get_drvdata(dev);
	struct qeth_ipaddr *addr;
	char *tmp;
	int i;

	if (!card)
		return -EINVAL;

	if (card->info.type != QETH_CARD_TYPE_IQD)
		return -EPERM;
	if (card->state != CARD_STATE_DOWN &&
	    card->state != CARD_STATE_RECOVER)
		return -EPERM;
	if (card->options.sniffer)
		return -EPERM;
	if (card->options.cq == QETH_CQ_NOTAVAILABLE)
		return -EPERM;

	tmp = strsep((char **)&buf, "\n");
	if (strlen(tmp) > 8)
		return -EINVAL;

	if (card->options.hsuid[0]) {
		/* delete old ip address */
		addr = qeth_l3_get_addr_buffer(QETH_PROT_IPV6);
		if (addr != NULL) {
			addr->u.a6.addr.s6_addr32[0] = 0xfe800000;
			addr->u.a6.addr.s6_addr32[1] = 0x00000000;
			for (i = 8; i < 16; i++)
				addr->u.a6.addr.s6_addr[i] =
					card->options.hsuid[i - 8];
			addr->u.a6.pfxlen = 0;
			addr->type = QETH_IP_TYPE_NORMAL;
		} else
			return -ENOMEM;
		if (!qeth_l3_delete_ip(card, addr))
			kfree(addr);
		qeth_l3_set_ip_addr_list(card);
	}

	if (strlen(tmp) == 0) {
		/* delete ip address only */
		card->options.hsuid[0] = '\0';
		if (card->dev)
			memcpy(card->dev->perm_addr, card->options.hsuid, 9);
		qeth_configure_cq(card, QETH_CQ_DISABLED);
		return count;
	}

	if (qeth_configure_cq(card, QETH_CQ_ENABLED))
		return -EPERM;

	for (i = 0; i < 8; i++)
		card->options.hsuid[i] = ' ';
	card->options.hsuid[8] = '\0';
	strncpy(card->options.hsuid, tmp, strlen(tmp));
	ASCEBC(card->options.hsuid, 8);
	if (card->dev)
		memcpy(card->dev->perm_addr, card->options.hsuid, 9);

	addr = qeth_l3_get_addr_buffer(QETH_PROT_IPV6);
	if (addr != NULL) {
		addr->u.a6.addr.s6_addr32[0] = 0xfe800000;
		addr->u.a6.addr.s6_addr32[1] = 0x00000000;
		for (i = 8; i < 16; i++)
			addr->u.a6.addr.s6_addr[i] = card->options.hsuid[i - 8];
		addr->u.a6.pfxlen = 0;
		addr->type = QETH_IP_TYPE_NORMAL;
	} else
		return -ENOMEM;
	if (!qeth_l3_add_ip(card, addr))
		kfree(addr);
	qeth_l3_set_ip_addr_list(card);

	return count;
}