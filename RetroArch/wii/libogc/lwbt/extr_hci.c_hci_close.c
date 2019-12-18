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
struct hci_link {int /*<<< orphan*/ * p; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  HCI_RMV (int /*<<< orphan*/ *,struct hci_link*) ; 
 int /*<<< orphan*/  btmemb_free (int /*<<< orphan*/ *,struct hci_link*) ; 
 int /*<<< orphan*/  btpbuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_active_links ; 
 int /*<<< orphan*/  hci_links ; 

err_t hci_close(struct hci_link *link)
{
	if(link->p != NULL) {
		btpbuf_free(link->p);
	}

	HCI_RMV(&(hci_active_links), link);
	btmemb_free(&hci_links, link);
	link = NULL;
	return ERR_OK;
}