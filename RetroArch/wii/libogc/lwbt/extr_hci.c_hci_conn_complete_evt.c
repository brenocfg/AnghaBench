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
struct pbuf {scalar_t__ payload; } ;
struct bd_addr {int /*<<< orphan*/ * addr; } ;
struct hci_link {struct bd_addr bdaddr; void* connhdl; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*) ; 
 int /*<<< orphan*/  ERR_CONN ; 
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  HCI_CONN_TERMINATED_BY_LOCAL_HOST ; 
 int /*<<< orphan*/  HCI_EVENT_CONN_COMPLETE (int /*<<< orphan*/ ,struct bd_addr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_OTHER_END_TERMINATED_CONN_LOW_RESOURCES ; 
#define  HCI_PAGE_TIMEOUT 129 
 int /*<<< orphan*/  HCI_REG (int /*<<< orphan*/ *,struct hci_link*) ; 
#define  HCI_SUCCESS 128 
 int /*<<< orphan*/  LOG (char*,struct hci_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bd_addr_set (struct bd_addr*,struct bd_addr*) ; 
 int /*<<< orphan*/  hci_active_links ; 
 int /*<<< orphan*/  hci_close (struct hci_link*) ; 
 int /*<<< orphan*/  hci_dev ; 
 int /*<<< orphan*/  hci_disconnect (struct bd_addr*,int /*<<< orphan*/ ) ; 
 struct hci_link* hci_get_link (struct bd_addr*) ; 
 struct hci_link* hci_new () ; 
 void* le16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lp_connect_cfm (struct bd_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lp_connect_ind (struct bd_addr*) ; 
 int /*<<< orphan*/  lp_disconnect_ind (struct bd_addr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_conn_complete_evt(struct pbuf *p)
{
	err_t ret;
	struct bd_addr *bdaddr;
	struct hci_link *link;

	(void)ret;

	bdaddr = (void*)(((u8_t*)p->payload)+3);
	link = hci_get_link(bdaddr);
	LOG("hci_conn_complete_evt(%p,%02x - %02x:%02x:%02x:%02x:%02x:%02x)\n",link,((u8_t*)p->payload)[0],bdaddr->addr[0],bdaddr->addr[1],bdaddr->addr[2],bdaddr->addr[3],bdaddr->addr[4],bdaddr->addr[5]);
	switch(((u8_t*)p->payload)[0]) {
		case HCI_SUCCESS:
			if(link==NULL) {
				if((link=hci_new())==NULL) {
					ERROR("hci_conn_complete_evt: Could not allocate memory for link. Disconnect\n");
					hci_disconnect(bdaddr, HCI_OTHER_END_TERMINATED_CONN_LOW_RESOURCES);
					lp_disconnect_ind(bdaddr,HCI_CONN_TERMINATED_BY_LOCAL_HOST);
					break;
				}
				bd_addr_set(&(link->bdaddr),bdaddr);
				link->connhdl = le16toh(*((u16_t*)(((u8_t*)p->payload)+1)));
				HCI_REG(&(hci_active_links),link);
				HCI_EVENT_CONN_COMPLETE(hci_dev,bdaddr,ret);
				lp_connect_ind(&(link->bdaddr));
			} else {
				link->connhdl = le16toh(*((u16_t*)(((u8_t*)p->payload)+1)));
				HCI_EVENT_CONN_COMPLETE(hci_dev,bdaddr,ret);
				lp_connect_cfm(&(link->bdaddr),((u8_t*)p->payload)[10],ERR_OK);
			}
			break;
		case HCI_PAGE_TIMEOUT:
			break;
		default:
			if(link!=NULL) {
				hci_close(link);
				lp_connect_cfm(bdaddr,((u8_t*)p->payload)[10],ERR_CONN);
			}
			break;
	}
}