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
typedef  int /*<<< orphan*/  u8_t ;
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
 int /*<<< orphan*/  HCI_DISCONN_OCF ; 
 int /*<<< orphan*/  HCI_DISCONN_PLEN ; 
 int /*<<< orphan*/  HCI_LINK_CTRL_OGF ; 
 int /*<<< orphan*/  PBUF_RAM ; 
 int /*<<< orphan*/  PBUF_RAW ; 
 struct pbuf* btpbuf_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btpbuf_free (struct pbuf*) ; 
 struct pbuf* hci_cmd_ass (struct pbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hci_link* hci_get_link (struct bd_addr*) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  physbusif_output (struct pbuf*,int /*<<< orphan*/ ) ; 

err_t hci_disconnect(struct bd_addr *bdaddr, u8_t reason)
{
	struct pbuf *p;
	struct hci_link *link;

	link = hci_get_link(bdaddr);

	if(link == NULL) {
		ERROR("hci_disconnect: Connection does not exist\n");
		return ERR_CONN; /* Connection does not exist */
	}
	if((p = btpbuf_alloc(PBUF_RAW, HCI_DISCONN_PLEN, PBUF_RAM)) == NULL) {
		ERROR("hci_disconnect: Could not allocate memory for pbuf\n");
		return ERR_MEM; /* Could not allocate memory for pbuf */
	}
	/* Assembling command packet */
	p = hci_cmd_ass(p, HCI_DISCONN_OCF, HCI_LINK_CTRL_OGF, HCI_DISCONN_PLEN);

	/* Assembling cmd prameters */
	((u16_t *)p->payload)[2] = htole16(link->connhdl);
	((u8_t *)p->payload)[6] = reason;

	physbusif_output(p, p->tot_len);
	btpbuf_free(p);

	return ERR_OK;
}