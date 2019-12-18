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
struct hci_link {int dummy; } ;
struct bd_addr {int dummy; } ;

/* Variables and functions */
 struct hci_link* hci_get_link (struct bd_addr*) ; 

u8_t lp_is_connected(struct bd_addr *bdaddr)
{
	struct hci_link *link;

	link = hci_get_link(bdaddr);

	if(link == NULL) {
		return 0;
	}
	return 1;
}