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
typedef  int /*<<< orphan*/  u8 ;
struct qeth_cmd_buffer {int dummy; } ;
struct TYPE_2__ {scalar_t__ guestlan; } ;
struct qeth_card {TYPE_1__ info; } ;
struct qeth_arp_cache_entry {scalar_t__ ipaddr; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IPA_ARP_PROCESSING ; 
 int /*<<< orphan*/  IPA_CMD_ASS_ARP_ADD_ENTRY ; 
 int /*<<< orphan*/  QETH_CARD_IFNAME (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_PROT_IPV4 ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  qeth_is_supported (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_l3_arp_get_error_cause (int*) ; 
 int /*<<< orphan*/  qeth_l3_default_setassparms_cb ; 
 struct qeth_cmd_buffer* qeth_l3_get_setassparms_cmd (struct qeth_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_l3_ipaddr4_to_string (int /*<<< orphan*/ *,char*) ; 
 int qeth_l3_send_setassparms (struct qeth_card*,struct qeth_cmd_buffer*,int,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qeth_l3_arp_add_entry(struct qeth_card *card,
				struct qeth_arp_cache_entry *entry)
{
	struct qeth_cmd_buffer *iob;
	char buf[16];
	int tmp;
	int rc;

	QETH_DBF_TEXT(TRACE, 3, "arpadent");

	/*
	 * currently GuestLAN only supports the ARP assist function
	 * IPA_CMD_ASS_ARP_QUERY_INFO, but not IPA_CMD_ASS_ARP_ADD_ENTRY;
	 * thus we say EOPNOTSUPP for this ARP function
	 */
	if (card->info.guestlan)
		return -EOPNOTSUPP;
	if (!qeth_is_supported(card, IPA_ARP_PROCESSING)) {
		return -EOPNOTSUPP;
	}

	iob = qeth_l3_get_setassparms_cmd(card, IPA_ARP_PROCESSING,
				       IPA_CMD_ASS_ARP_ADD_ENTRY,
				       sizeof(struct qeth_arp_cache_entry),
				       QETH_PROT_IPV4);
	rc = qeth_l3_send_setassparms(card, iob,
				   sizeof(struct qeth_arp_cache_entry),
				   (unsigned long) entry,
				   qeth_l3_default_setassparms_cb, NULL);
	if (rc) {
		tmp = rc;
		qeth_l3_ipaddr4_to_string((u8 *)entry->ipaddr, buf);
		QETH_DBF_MESSAGE(2, "Could not add ARP entry for address %s "
			"on %s: %s (0x%x/%d)\n", buf, QETH_CARD_IFNAME(card),
			qeth_l3_arp_get_error_cause(&rc), tmp, tmp);
	}
	return rc;
}