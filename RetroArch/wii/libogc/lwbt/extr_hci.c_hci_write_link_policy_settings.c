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
typedef  int /*<<< orphan*/  u16_t ;
struct pbuf {int /*<<< orphan*/  tot_len; scalar_t__ payload; } ;
struct hci_link {int /*<<< orphan*/  connhdl; } ;
struct bd_addr {int dummy; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*) ; 
 int /*<<< orphan*/  ERR_CONN ; 
 int /*<<< orphan*/  ERR_MEM ; 
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  HCI_LINK_POLICY_OGF ; 
 int /*<<< orphan*/  HCI_W_LINK_POLICY_OCF ; 
 int /*<<< orphan*/  HCI_W_LINK_POLICY_PLEN ; 
 int /*<<< orphan*/  PBUF_RAM ; 
 int /*<<< orphan*/  PBUF_TRANSPORT ; 
 struct pbuf* btpbuf_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btpbuf_free (struct pbuf*) ; 
 struct pbuf* hci_cmd_ass (struct pbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hci_link* hci_get_link (struct bd_addr*) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  physbusif_output (struct pbuf*,int /*<<< orphan*/ ) ; 

err_t hci_write_link_policy_settings(struct bd_addr *bdaddr, u16_t link_policy)
{
	struct pbuf *p;
	struct hci_link *link;

	/* Check if an ACL connection exists */
	link = hci_get_link(bdaddr);

	if(link == NULL) {
		ERROR("hci_write_link_policy_settings: ACL connection does not exist\n");
		return ERR_CONN;
	}

	if( (p = btpbuf_alloc(PBUF_TRANSPORT, HCI_W_LINK_POLICY_PLEN, PBUF_RAM)) == NULL) { /* Alloc len of packet */
		ERROR("hci_write_link_policy_settings: Could not allocate memory for pbuf\n");
		return ERR_MEM;
	}
	/* Assembling command packet */
	p = hci_cmd_ass(p, HCI_W_LINK_POLICY_OCF, HCI_LINK_POLICY_OGF, HCI_W_LINK_POLICY_PLEN);

	/* Assembling cmd prameters */
	((u16_t *)p->payload)[2] = htole16(link->connhdl);
	((u16_t *)p->payload)[3] = htole16(link_policy);

	physbusif_output(p, p->tot_len);
	btpbuf_free(p);
	return ERR_OK;
}