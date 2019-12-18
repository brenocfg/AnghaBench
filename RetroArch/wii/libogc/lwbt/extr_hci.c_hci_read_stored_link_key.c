#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8_t ;
struct pbuf {int /*<<< orphan*/  tot_len; scalar_t__ payload; } ;
struct hci_link_key {struct hci_link_key* next; } ;
typedef  int /*<<< orphan*/  err_t ;
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {TYPE_1__ bdaddr; struct hci_link_key* keyres; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*) ; 
 int /*<<< orphan*/  ERR_MEM ; 
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  HCI_HC_BB_OGF ; 
 int /*<<< orphan*/  HCI_R_STORED_LINK_KEY_OCF ; 
 int /*<<< orphan*/  HCI_R_STORED_LINK_KEY_PLEN ; 
 int /*<<< orphan*/  PBUF_RAM ; 
 int /*<<< orphan*/  PBUF_RAW ; 
 int /*<<< orphan*/  btmemb_free (int /*<<< orphan*/ *,struct hci_link_key*) ; 
 struct pbuf* btpbuf_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btpbuf_free (struct pbuf*) ; 
 struct pbuf* hci_cmd_ass (struct pbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* hci_dev ; 
 int /*<<< orphan*/  hci_link_key_results ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  physbusif_output (struct pbuf*,int /*<<< orphan*/ ) ; 

err_t hci_read_stored_link_key()
{
	struct pbuf *p = NULL;
	struct hci_link_key *tmpres;

	/* Free any previous link key result list */
	while(hci_dev->keyres != NULL) {
		tmpres = hci_dev->keyres;
		hci_dev->keyres = hci_dev->keyres->next;
		btmemb_free(&hci_link_key_results,tmpres);
	}

	if((p=btpbuf_alloc(PBUF_RAW,HCI_R_STORED_LINK_KEY_PLEN,PBUF_RAM))==NULL) {
		ERROR("hci_read_stored_link_keys: Could not allocate memory for pbuf\n");
		return ERR_MEM;
	}

	p = hci_cmd_ass(p,HCI_R_STORED_LINK_KEY_OCF,HCI_HC_BB_OGF,HCI_R_STORED_LINK_KEY_PLEN);

	memcpy((void*)((u8_t*)p->payload + 4),hci_dev->bdaddr.addr,6);
	((u8_t*)p->payload)[10] = 1;

	physbusif_output(p,p->tot_len);
	btpbuf_free(p);

	return ERR_OK;
}