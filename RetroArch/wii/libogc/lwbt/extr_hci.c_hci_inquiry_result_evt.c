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
struct pbuf {scalar_t__ payload; } ;
struct hci_inq_res {int psrm; int psm; int /*<<< orphan*/ * next; int /*<<< orphan*/  co; int /*<<< orphan*/  cod; int /*<<< orphan*/  bdaddr; } ;
struct bd_addr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ires; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*) ; 
 int /*<<< orphan*/  HCI_REG (int /*<<< orphan*/ *,struct hci_inq_res*) ; 
 int MEMB_NUM_HCI_INQ ; 
 int /*<<< orphan*/  bd_addr_set (int /*<<< orphan*/ *,struct bd_addr*) ; 
 struct hci_inq_res* btmemb_alloc (int /*<<< orphan*/ *) ; 
 TYPE_1__* hci_dev ; 
 int /*<<< orphan*/  hci_inq_results ; 
 int /*<<< orphan*/  le16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void hci_inquiry_result_evt(struct pbuf *p)
{
	u8_t num_resp;
	u32_t i,resp_off;
	struct bd_addr *bdaddr;
	struct hci_inq_res *ires;

	num_resp = ((u8_t*)p->payload)[0];
	//printf("hci_inquriy_result_evt(%d)\n",num_resp);
	for(i=0;i<num_resp && i<MEMB_NUM_HCI_INQ;i++) {
		resp_off = (i*14);
		bdaddr = (void*)(((u8_t*)p->payload)+(1+resp_off));
		if((ires=btmemb_alloc(&hci_inq_results))!=NULL) {
			bd_addr_set(&(ires->bdaddr),bdaddr);
			ires->psrm = ((u8_t*)p->payload)[7+resp_off];
			ires->psm = ((u8_t*)p->payload)[8+resp_off];
			memcpy(ires->cod,((u8_t*)p->payload)+10+resp_off,3);
			ires->co = le16toh(*((u16_t*)(((u8_t*)p->payload)+13+resp_off)));
			ires->next = NULL;

			HCI_REG(&(hci_dev->ires),ires);
		} else
			ERROR("hci_inquriy_result_evt: Could not allocate memory for inquiry result\n");
	}

}