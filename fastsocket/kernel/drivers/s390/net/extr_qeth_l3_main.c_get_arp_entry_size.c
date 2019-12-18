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
struct qeth_card {int dummy; } ;
struct qeth_arp_query_data {int reply_bits; } ;
struct qeth_arp_qi_entry7_short_ipv6 {int dummy; } ;
struct qeth_arp_qi_entry7_short {int dummy; } ;
struct qeth_arp_qi_entry7_ipv6 {int dummy; } ;
struct qeth_arp_qi_entry7 {int dummy; } ;
struct qeth_arp_qi_entry5_short_ipv6 {int dummy; } ;
struct qeth_arp_qi_entry5_short {int dummy; } ;
struct qeth_arp_qi_entry5_ipv6 {int dummy; } ;
struct qeth_arp_qi_entry5 {int dummy; } ;
struct qeth_arp_entrytype {scalar_t__ ip; } ;
typedef  int __u8 ;
typedef  int __u32 ;

/* Variables and functions */
 scalar_t__ QETHARP_IP_ADDR_V4 ; 
 scalar_t__ QETHARP_IP_ADDR_V6 ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  TRACE ; 

__attribute__((used)) static __u32 get_arp_entry_size(struct qeth_card *card,
			struct qeth_arp_query_data *qdata,
			struct qeth_arp_entrytype *type, __u8 strip_entries)
{
	__u32 rc;
	__u8 is_hsi;

	is_hsi = qdata->reply_bits == 5;
	if (type->ip == QETHARP_IP_ADDR_V4) {
		QETH_DBF_TEXT(TRACE, 4, "arpev4");
		if (strip_entries) {
			rc = is_hsi ? sizeof(struct qeth_arp_qi_entry5_short) :
				sizeof(struct qeth_arp_qi_entry7_short);
		} else {
			rc = is_hsi ? sizeof(struct qeth_arp_qi_entry5) :
				sizeof(struct qeth_arp_qi_entry7);
		}
	} else if (type->ip == QETHARP_IP_ADDR_V6) {
		QETH_DBF_TEXT(TRACE, 4, "arpev6");
		if (strip_entries) {
			rc = is_hsi ?
				sizeof(struct qeth_arp_qi_entry5_short_ipv6) :
				sizeof(struct qeth_arp_qi_entry7_short_ipv6);
		} else {
			rc = is_hsi ?
				sizeof(struct qeth_arp_qi_entry5_ipv6) :
				sizeof(struct qeth_arp_qi_entry7_ipv6);
		}
	} else {
		QETH_DBF_TEXT(TRACE, 4, "arpinv");
		rc = 0;
	}

	return rc;
}