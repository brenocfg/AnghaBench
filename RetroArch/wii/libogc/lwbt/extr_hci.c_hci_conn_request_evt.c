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
struct pbuf {scalar_t__ payload; } ;
struct hci_link {int /*<<< orphan*/  bdaddr; } ;
struct bd_addr {int dummy; } ;
typedef  scalar_t__ err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*) ; 
 scalar_t__ ERR_OK ; 
 int /*<<< orphan*/  HCI_EVENT_CONN_REQ (int /*<<< orphan*/ ,struct bd_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HCI_REG (int /*<<< orphan*/ *,struct hci_link*) ; 
 int /*<<< orphan*/  LOG (char*) ; 
 int /*<<< orphan*/  bd_addr_set (int /*<<< orphan*/ *,struct bd_addr*) ; 
 int /*<<< orphan*/  hci_accecpt_conn_request (struct bd_addr*,int) ; 
 int /*<<< orphan*/  hci_active_links ; 
 int /*<<< orphan*/  hci_dev ; 
 struct hci_link* hci_get_link (struct bd_addr*) ; 
 struct hci_link* hci_new () ; 

__attribute__((used)) static void hci_conn_request_evt(struct pbuf *p)
{
	u8_t *cod;
	u8_t link_type;
	err_t ret = ERR_OK;
	struct bd_addr *bdaddr;
	struct hci_link *link;

	LOG("hci_conn_request_evt()\n");
	bdaddr = (void*)((u8_t*)p->payload);
	cod = (((u8_t*)p->payload)+6);
	link_type = *(((u8_t*)p->payload)+9);

	HCI_EVENT_CONN_REQ(hci_dev,bdaddr,cod,link_type,ret);
	if(ret==ERR_OK) {
		link = hci_get_link(bdaddr);
		if(link==NULL) {
			if((link=hci_new())==NULL) {
				ERROR("hci_conn_request_evt: Could not allocate memory for link. Disconnect\n");
				return;
			}

			bd_addr_set(&(link->bdaddr),bdaddr);
			HCI_REG(&(hci_active_links),link);
		}
		hci_accecpt_conn_request(bdaddr,0x00);
	} else {
	}
}