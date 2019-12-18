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
typedef  int u32_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct pbuf {int /*<<< orphan*/  tot_len; scalar_t__ payload; } ;
struct hci_inq_res {struct hci_inq_res* next; } ;
typedef  int /*<<< orphan*/  err_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* inq_complete ) (void*,struct hci_pcb*,struct hci_inq_res*,int /*<<< orphan*/ ) ;struct hci_inq_res* ires; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*) ; 
 int /*<<< orphan*/  ERR_MEM ; 
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  HCI_LINK_CTRL_OGF ; 
 int /*<<< orphan*/  HCI_PERIODIC_INQUIRY_OCF ; 
 int /*<<< orphan*/  HCI_PERIODIC_INQUIRY_PLEN ; 
 int /*<<< orphan*/  PBUF_RAM ; 
 int /*<<< orphan*/  PBUF_RAW ; 
 int /*<<< orphan*/  btmemb_free (int /*<<< orphan*/ *,struct hci_inq_res*) ; 
 struct pbuf* btpbuf_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btpbuf_free (struct pbuf*) ; 
 struct pbuf* hci_cmd_ass (struct pbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* hci_dev ; 
 int /*<<< orphan*/  hci_inq_results ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  physbusif_output (struct pbuf*,int /*<<< orphan*/ ) ; 

err_t hci_periodic_inquiry(u32_t lap,u16_t min_period,u16_t max_period,u8_t inq_len,u8_t num_resp,err_t (*inq_complete)(void *arg,struct hci_pcb *pcb,struct hci_inq_res *ires,u16_t result))
{
	struct pbuf *p = NULL;
	struct hci_inq_res *tmpres;

	/* Free any previous inquiry result list */
	while(hci_dev->ires != NULL) {
		tmpres = hci_dev->ires;
		hci_dev->ires = hci_dev->ires->next;
		btmemb_free(&hci_inq_results,tmpres);
	}

	hci_dev->inq_complete = inq_complete;
	if((p=btpbuf_alloc(PBUF_RAW,HCI_PERIODIC_INQUIRY_PLEN,PBUF_RAM))==NULL) {
		ERROR("hci_periodic_inquiry: Could not allocate memory for pbuf\n");
		return ERR_MEM;
	}

	/* Assembling command packet */
	p = hci_cmd_ass(p,HCI_PERIODIC_INQUIRY_OCF,HCI_LINK_CTRL_OGF,HCI_PERIODIC_INQUIRY_PLEN);

	/* Assembling cmd prameters */
	((u16_t*)p->payload)[2] = htole16(max_period);
	((u16_t*)p->payload)[3] = htole16(min_period);
	((u8_t*)p->payload)[8] = (lap&0xff);
	((u8_t*)p->payload)[9] = (lap>>8);
	((u8_t*)p->payload)[10] = (lap>>16);

	((u8_t*)p->payload)[11] = inq_len;
	((u8_t*)p->payload)[12] = num_resp;

	physbusif_output(p,p->tot_len);
	btpbuf_free(p);

	return ERR_OK;
}