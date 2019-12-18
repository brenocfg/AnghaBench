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
struct hci_link {int /*<<< orphan*/  bdaddr; struct hci_link* next; } ;
struct bd_addr {int dummy; } ;

/* Variables and functions */
 scalar_t__ bd_addr_cmp (int /*<<< orphan*/ *,struct bd_addr*) ; 
 struct hci_link* hci_active_links ; 

struct hci_link* hci_get_link(struct bd_addr *bdaddr)
{
	struct hci_link *link;

	for(link=hci_active_links;link!=NULL;link=link->next) {
		if(bd_addr_cmp(&(link->bdaddr),bdaddr)) break;
	}
	return link;
}