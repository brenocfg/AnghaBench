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
struct pbuf {scalar_t__ payload; } ;
struct hci_link_key {int /*<<< orphan*/ * next; int /*<<< orphan*/  key; int /*<<< orphan*/  bdaddr; } ;
struct bd_addr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  keyres; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*) ; 
 int /*<<< orphan*/  HCI_REG (int /*<<< orphan*/ *,struct hci_link_key*) ; 
 int MEMB_NUM_HCI_LINK_KEY ; 
 int /*<<< orphan*/  bd_addr_set (int /*<<< orphan*/ *,struct bd_addr*) ; 
 struct hci_link_key* btmemb_alloc (int /*<<< orphan*/ *) ; 
 TYPE_1__* hci_dev ; 
 int /*<<< orphan*/  hci_link_key_results ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void hci_return_link_key_evt(struct pbuf *p)
{
	u8_t num_keys;
	u32_t i,resp_off;
	struct bd_addr *bdaddr;
	struct hci_link_key *keyres;

	num_keys = ((u8_t*)p->payload)[0];
	//printf("hci_return_link_key_evt(%d)\n",num_keys);
	for(i=0;i<num_keys && i<MEMB_NUM_HCI_LINK_KEY;i++) {
		resp_off = (i*22);
		bdaddr = (void*)(((u8_t*)p->payload)+1+resp_off);
		if((keyres=btmemb_alloc(&hci_link_key_results))!=NULL) {
			bd_addr_set(&(keyres->bdaddr),bdaddr);
			memcpy(keyres->key,((u8_t*)p->payload)+7+resp_off,16);
			keyres->next = NULL;

			//printf("link key evt: %02x:%02x:%02x:%02x:%02x:%02x\n",bdaddr->addr[0],bdaddr->addr[1],bdaddr->addr[2],bdaddr->addr[3],bdaddr->addr[4],bdaddr->addr[5]);
			HCI_REG(&(hci_dev->keyres),keyres);
		} else
			ERROR("hci_return_link_key_evt: Could not allocate memory for link key result\n");
	}

}