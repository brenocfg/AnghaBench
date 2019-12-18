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
struct hci_link_key {struct hci_link_key* next; struct hci_link_key* keyres; struct hci_link_key* ires; } ;
struct hci_link {struct hci_link* next; } ;
struct hci_inq_res {struct hci_inq_res* next; struct hci_inq_res* keyres; struct hci_inq_res* ires; } ;

/* Variables and functions */
 int /*<<< orphan*/  btmemb_free (int /*<<< orphan*/ *,struct hci_link_key*) ; 
 struct hci_link* hci_active_links ; 
 int /*<<< orphan*/  hci_close (struct hci_link*) ; 
 struct hci_link_key* hci_dev ; 
 int /*<<< orphan*/  hci_init () ; 
 int /*<<< orphan*/  hci_inq_results ; 
 int /*<<< orphan*/  hci_pcbs ; 

void hci_reset_all(void)
{
	struct hci_link *link,*tlink;
	struct hci_inq_res *ires,*tires;
	struct hci_link_key *ikeys,*tikeys;

	for(link=hci_active_links;link!=NULL;) {
		tlink = link->next;
		hci_close(link);
		link = tlink;
	}
	hci_active_links = NULL;

	for(ires=hci_dev->ires;ires!=NULL;) {
		tires = ires->next;
		btmemb_free(&hci_inq_results,ires);
		ires = tires;
	}

	for(ikeys=hci_dev->keyres;ikeys!=NULL;) {
		tikeys = ikeys->next;
		btmemb_free(&hci_inq_results,ikeys);
		ikeys = tikeys;
	}
	btmemb_free(&hci_pcbs,hci_dev);

	hci_init();
}