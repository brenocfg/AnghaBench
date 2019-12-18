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
struct hci_inq_res {int psrm; int psm; int co; int /*<<< orphan*/  bdaddr; struct hci_inq_res* next; } ;
struct bd_addr {int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  err_t ;
struct TYPE_2__ {struct hci_inq_res* ires; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*) ; 
 int /*<<< orphan*/  ERR_MEM ; 
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  HCI_LINK_CTRL_OGF ; 
 int /*<<< orphan*/  HCI_R_REMOTE_NAME_OCF ; 
 int /*<<< orphan*/  HCI_R_REMOTE_NAME_PLEN ; 
 int /*<<< orphan*/  PBUF_RAM ; 
 int /*<<< orphan*/  PBUF_RAW ; 
 scalar_t__ bd_addr_cmp (int /*<<< orphan*/ *,struct bd_addr*) ; 
 struct pbuf* btpbuf_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btpbuf_free (struct pbuf*) ; 
 struct pbuf* hci_cmd_ass (struct pbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* hci_dev ; 
 int htole16 (int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  physbusif_output (struct pbuf*,int /*<<< orphan*/ ) ; 

err_t hci_read_remote_name(struct bd_addr *bdaddr)
{
	u16_t clock_offset;
	struct pbuf *p = NULL;
	struct hci_inq_res *ires;
	u8_t page_scan_repetition_mode, page_scan_mode;

	for(ires=hci_dev->ires;ires!=NULL;ires=ires->next) {
		if(bd_addr_cmp(&(ires->bdaddr),bdaddr)) {
			page_scan_repetition_mode = ires->psrm;
			page_scan_mode = ires->psm;
			clock_offset = ires->co;
			break;
		}
	}

	if(ires==NULL) {
		page_scan_repetition_mode = 0x01;
		page_scan_mode = 0x00;
		clock_offset = 0x00;
	}

	if((p=btpbuf_alloc(PBUF_RAW,HCI_R_REMOTE_NAME_PLEN,PBUF_RAM))==NULL) {
		ERROR("hci_read_remote_name: Could not allocate memory for pbuf\n");
		return ERR_MEM;
	}

	/* Assembling command packet */
	p = hci_cmd_ass(p,HCI_R_REMOTE_NAME_OCF,HCI_LINK_CTRL_OGF,HCI_R_REMOTE_NAME_PLEN);
	/* Assembling cmd prameters */
	memcpy(((u8_t *)p->payload+4),bdaddr->addr,6);
	((u8_t*)p->payload)[10] = page_scan_repetition_mode;
	((u8_t*)p->payload)[11] = page_scan_mode;
	((u16_t*)p->payload)[6] = htole16(clock_offset);

	physbusif_output(p, p->tot_len);
	btpbuf_free(p);

	return ERR_OK;

}