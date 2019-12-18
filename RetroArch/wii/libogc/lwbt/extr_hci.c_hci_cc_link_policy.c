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
typedef  int u8_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct pbuf {scalar_t__ payload; } ;
struct hci_link {int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  connhdl; struct hci_link* next; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_EVENT_WLP_COMPLETE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int HCI_SUCCESS ; 
#define  HCI_W_LINK_POLICY 128 
 int /*<<< orphan*/  LOG (char*) ; 
 struct hci_link* hci_active_links ; 
 int /*<<< orphan*/  hci_dev ; 
 int /*<<< orphan*/  le16toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_cc_link_policy(u8_t ocf,struct pbuf *p)
{
	err_t ret;
	struct hci_link *link;

	(void)ret;

	switch(ocf) {
		case HCI_W_LINK_POLICY:
			if(((u8_t*)p->payload)[0]==HCI_SUCCESS) {
				for(link=hci_active_links;link!=NULL;link=link->next) {
					if(link->connhdl==le16toh(*((u16_t*)(((u8_t*)p->payload)+1)))) break;
				}
				if(link==NULL) {
					LOG("hci_cc_link_policy: Connection does not exist\n");
					break;
				}
				HCI_EVENT_WLP_COMPLETE(hci_dev,&link->bdaddr,ret);
			} else {
				LOG("Unsuccessful HCI_W_LINK_POLICY.\n");
			}
			break;
	}
}