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
struct TYPE_2__ {scalar_t__ guestlan; } ;
struct qeth_card {TYPE_1__ info; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IPA_ARP_PROCESSING ; 
 int /*<<< orphan*/  IPA_CMD_ASS_ARP_SET_NO_ENTRIES ; 
 int /*<<< orphan*/  QETH_CARD_IFNAME (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  qeth_is_supported (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_l3_arp_get_error_cause (int*) ; 
 int qeth_l3_send_simple_setassparms (struct qeth_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qeth_l3_arp_set_no_entries(struct qeth_card *card, int no_entries)
{
	int tmp;
	int rc;

	QETH_DBF_TEXT(TRACE, 3, "arpstnoe");

	/*
	 * currently GuestLAN only supports the ARP assist function
	 * IPA_CMD_ASS_ARP_QUERY_INFO, but not IPA_CMD_ASS_ARP_SET_NO_ENTRIES;
	 * thus we say EOPNOTSUPP for this ARP function
	 */
	if (card->info.guestlan)
		return -EOPNOTSUPP;
	if (!qeth_is_supported(card, IPA_ARP_PROCESSING)) {
		return -EOPNOTSUPP;
	}
	rc = qeth_l3_send_simple_setassparms(card, IPA_ARP_PROCESSING,
					  IPA_CMD_ASS_ARP_SET_NO_ENTRIES,
					  no_entries);
	if (rc) {
		tmp = rc;
		QETH_DBF_MESSAGE(2, "Could not set number of ARP entries on "
			"%s: %s (0x%x/%d)\n", QETH_CARD_IFNAME(card),
			qeth_l3_arp_get_error_cause(&rc), tmp, tmp);
	}
	return rc;
}