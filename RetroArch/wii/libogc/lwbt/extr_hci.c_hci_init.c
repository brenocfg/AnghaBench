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
struct hci_pcb {int dummy; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*) ; 
 int /*<<< orphan*/  ERR_MEM ; 
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/ * btmemb_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btmemb_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btmemr_init () ; 
 int /*<<< orphan*/  btpbuf_init () ; 
 int /*<<< orphan*/ * hci_active_links ; 
 int /*<<< orphan*/ * hci_dev ; 
 int /*<<< orphan*/  hci_inq_results ; 
 int /*<<< orphan*/  hci_link_key_results ; 
 int /*<<< orphan*/  hci_links ; 
 int /*<<< orphan*/  hci_pcbs ; 
 int /*<<< orphan*/ * hci_tmp_link ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

err_t hci_init(void)
{
	btmemr_init();
	btpbuf_init();

	btmemb_init(&hci_pcbs);
	btmemb_init(&hci_links);
	btmemb_init(&hci_inq_results);
	btmemb_init(&hci_link_key_results);

	if((hci_dev=btmemb_alloc(&hci_pcbs))==NULL) {
		ERROR("hci_init: Could not allocate memory for hci_dev\n");
		return ERR_MEM;
	}
	memset(hci_dev,0,sizeof(struct hci_pcb));

	hci_active_links = NULL;
	hci_tmp_link = NULL;

	return ERR_OK;
}