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
typedef  int u8_t ;
typedef  int u16_t ;
struct pbuf {int /*<<< orphan*/  tot_len; scalar_t__ payload; } ;
struct hci_link {int /*<<< orphan*/  bdaddr; } ;
struct hci_inq_res {int psrm; int psm; int co; int /*<<< orphan*/  bdaddr; struct hci_inq_res* next; } ;
struct bd_addr {int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  err_t ;
struct TYPE_2__ {int pkt_type; struct hci_inq_res* ires; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*) ; 
 int /*<<< orphan*/  ERR_MEM ; 
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  HCI_CREATE_CONN_OCF ; 
 int /*<<< orphan*/  HCI_CREATE_CONN_PLEN ; 
 int /*<<< orphan*/  HCI_LINK_CTRL_OGF ; 
 int /*<<< orphan*/  HCI_REG (int /*<<< orphan*/ *,struct hci_link*) ; 
 int /*<<< orphan*/  PBUF_RAM ; 
 int /*<<< orphan*/  PBUF_RAW ; 
 scalar_t__ bd_addr_cmp (int /*<<< orphan*/ *,struct bd_addr*) ; 
 int /*<<< orphan*/  bd_addr_set (int /*<<< orphan*/ *,struct bd_addr*) ; 
 struct pbuf* btpbuf_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btpbuf_free (struct pbuf*) ; 
 int /*<<< orphan*/  hci_active_links ; 
 struct pbuf* hci_cmd_ass (struct pbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* hci_dev ; 
 struct hci_link* hci_new () ; 
 int htole16 (int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  physbusif_output (struct pbuf*,int /*<<< orphan*/ ) ; 

err_t lp_connect_req(struct bd_addr *bdaddr, u8_t allow_role_switch)
{
	u8_t page_scan_repetition_mode, page_scan_mode;
	u16_t clock_offset;
	struct pbuf *p;
	struct hci_link *link = hci_new();
	struct hci_inq_res *inqres;

	if(link == NULL) {
		ERROR("lp_connect_req: Could not allocate memory for link\n");
		return ERR_MEM; /* Could not allocate memory for link */
	}

	bd_addr_set(&(link->bdaddr), bdaddr);
	HCI_REG(&(hci_active_links), link);

	/* Check if module has been discovered in a recent inquiry */
	for(inqres = hci_dev->ires; inqres != NULL; inqres = inqres->next) {
		if(bd_addr_cmp(&inqres->bdaddr, bdaddr)) {
			page_scan_repetition_mode = inqres->psrm;
			page_scan_mode = inqres->psm;
			clock_offset = inqres->co;
			break;
		}
	}
	if(inqres == NULL) {
		/* No information on parameters from an inquiry. Using default values */
		page_scan_repetition_mode = 0x01; /* Assuming worst case: time between
											 successive page scans starting
											 <= 2.56s */
		page_scan_mode = 0x00; /* Assumes the device uses mandatory scanning, most
		devices use this. If no conn is established, try
		again w this parm set to optional page scanning */
		clock_offset = 0x00; /* If the device was not found in a recent inquiry
		this  information is irrelevant */
	}

	if((p = btpbuf_alloc(PBUF_RAW, HCI_CREATE_CONN_PLEN, PBUF_RAM)) == NULL) {
		ERROR("lp_connect_req: Could not allocate memory for pbuf\n");
		return ERR_MEM; /* Could not allocate memory for pbuf */
	}

	/* Assembling command packet */
	p = hci_cmd_ass(p, HCI_CREATE_CONN_OCF, HCI_LINK_CTRL_OGF, HCI_CREATE_CONN_PLEN);
	/* Assembling cmd prameters */
	memcpy(((u8_t *)p->payload)+4, bdaddr->addr, 6);
	((u16_t *)p->payload)[5] = htole16(hci_dev->pkt_type);
	((u8_t *)p->payload)[12] = page_scan_repetition_mode;
	((u8_t *)p->payload)[13] = page_scan_mode;
	((u16_t *)p->payload)[7] = htole16(clock_offset);
	((u8_t *)p->payload)[16] = allow_role_switch;

	physbusif_output(p, p->tot_len);
	btpbuf_free(p);

	return ERR_OK;
}