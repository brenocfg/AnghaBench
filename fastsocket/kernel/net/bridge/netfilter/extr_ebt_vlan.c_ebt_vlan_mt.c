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
struct xt_match_param {struct ebt_vlan_info* matchinfo; } ;
struct vlan_hdr {unsigned char h_vlan_encapsulated_proto; int /*<<< orphan*/  h_vlan_TCI; } ;
struct sk_buff {int dummy; } ;
struct ebt_vlan_info {int dummy; } ;
typedef  int /*<<< orphan*/  _frame ;
typedef  unsigned char __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  EBT_VLAN_ENCAP ; 
 int /*<<< orphan*/  EBT_VLAN_ID ; 
 int /*<<< orphan*/  EBT_VLAN_PRIO ; 
 int /*<<< orphan*/  EXIT_ON_MISMATCH (unsigned char,int /*<<< orphan*/ ) ; 
 scalar_t__ GET_BITMASK (int /*<<< orphan*/ ) ; 
 unsigned short VLAN_VID_MASK ; 
 unsigned short ntohs (int /*<<< orphan*/ ) ; 
 struct vlan_hdr* skb_header_pointer (struct sk_buff const*,int /*<<< orphan*/ ,int,struct vlan_hdr*) ; 

__attribute__((used)) static bool
ebt_vlan_mt(const struct sk_buff *skb, const struct xt_match_param *par)
{
	const struct ebt_vlan_info *info = par->matchinfo;
	const struct vlan_hdr *fp;
	struct vlan_hdr _frame;

	unsigned short TCI;	/* Whole TCI, given from parsed frame */
	unsigned short id;	/* VLAN ID, given from frame TCI */
	unsigned char prio;	/* user_priority, given from frame TCI */
	/* VLAN encapsulated Type/Length field, given from orig frame */
	__be16 encap;

	fp = skb_header_pointer(skb, 0, sizeof(_frame), &_frame);
	if (fp == NULL)
		return false;

	/* Tag Control Information (TCI) consists of the following elements:
	 * - User_priority. The user_priority field is three bits in length,
	 * interpreted as a binary number.
	 * - Canonical Format Indicator (CFI). The Canonical Format Indicator
	 * (CFI) is a single bit flag value. Currently ignored.
	 * - VLAN Identifier (VID). The VID is encoded as
	 * an unsigned binary number. */
	TCI = ntohs(fp->h_vlan_TCI);
	id = TCI & VLAN_VID_MASK;
	prio = (TCI >> 13) & 0x7;
	encap = fp->h_vlan_encapsulated_proto;

	/* Checking VLAN Identifier (VID) */
	if (GET_BITMASK(EBT_VLAN_ID))
		EXIT_ON_MISMATCH(id, EBT_VLAN_ID);

	/* Checking user_priority */
	if (GET_BITMASK(EBT_VLAN_PRIO))
		EXIT_ON_MISMATCH(prio, EBT_VLAN_PRIO);

	/* Checking Encapsulated Proto (Length/Type) field */
	if (GET_BITMASK(EBT_VLAN_ENCAP))
		EXIT_ON_MISMATCH(encap, EBT_VLAN_ENCAP);

	return true;
}