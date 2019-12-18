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
struct niu_vlan_rdc {int /*<<< orphan*/  rdc_num; int /*<<< orphan*/  vlan_pref; } ;
struct niu_parent {int /*<<< orphan*/ * flow_key; int /*<<< orphan*/ * tcam_key; } ;
struct niu_classifier {int num_alt_mac_mappings; struct niu_altmac_rdc* alt_mac_mappings; struct niu_vlan_rdc* vlan_mappings; int /*<<< orphan*/  h2_init; int /*<<< orphan*/  h1_init; } ;
struct niu_altmac_rdc {int /*<<< orphan*/  mac_pref; int /*<<< orphan*/  rdc_num; int /*<<< orphan*/  alt_mac_num; } ;
struct niu {int /*<<< orphan*/  port; struct niu_classifier clas; struct niu_parent* parent; } ;

/* Variables and functions */
 int CLASS_CODE_SCTP_IPV6 ; 
 int CLASS_CODE_USER_PROG1 ; 
 int ENET_VLAN_TBL_NUM_ENTRIES ; 
 int /*<<< orphan*/  H1POLY ; 
 int /*<<< orphan*/  H2POLY ; 
 int niu_init_hostinfo (struct niu*) ; 
 int niu_set_alt_mac_rdc_table (struct niu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int niu_set_flow_key (struct niu*,int,int /*<<< orphan*/ ) ; 
 int niu_set_ip_frag_rule (struct niu*) ; 
 int niu_set_tcam_key (struct niu*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcam_enable (struct niu*,int) ; 
 int /*<<< orphan*/  vlan_tbl_write (struct niu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int niu_init_classifier_hw(struct niu *np)
{
	struct niu_parent *parent = np->parent;
	struct niu_classifier *cp = &np->clas;
	int i, err;

	nw64(H1POLY, cp->h1_init);
	nw64(H2POLY, cp->h2_init);

	err = niu_init_hostinfo(np);
	if (err)
		return err;

	for (i = 0; i < ENET_VLAN_TBL_NUM_ENTRIES; i++) {
		struct niu_vlan_rdc *vp = &cp->vlan_mappings[i];

		vlan_tbl_write(np, i, np->port,
			       vp->vlan_pref, vp->rdc_num);
	}

	for (i = 0; i < cp->num_alt_mac_mappings; i++) {
		struct niu_altmac_rdc *ap = &cp->alt_mac_mappings[i];

		err = niu_set_alt_mac_rdc_table(np, ap->alt_mac_num,
						ap->rdc_num, ap->mac_pref);
		if (err)
			return err;
	}

	for (i = CLASS_CODE_USER_PROG1; i <= CLASS_CODE_SCTP_IPV6; i++) {
		int index = i - CLASS_CODE_USER_PROG1;

		err = niu_set_tcam_key(np, i, parent->tcam_key[index]);
		if (err)
			return err;
		err = niu_set_flow_key(np, i, parent->flow_key[index]);
		if (err)
			return err;
	}

	err = niu_set_ip_frag_rule(np);
	if (err)
		return err;

	tcam_enable(np, 1);

	return 0;
}