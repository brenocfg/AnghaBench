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
typedef  void* u8_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct hci_inq_res {int /*<<< orphan*/ * next; int /*<<< orphan*/  co; void* psm; void* psrm; int /*<<< orphan*/  cod; int /*<<< orphan*/  bdaddr; } ;
struct bd_addr {int dummy; } ;
typedef  int /*<<< orphan*/  err_t ;
struct TYPE_2__ {int /*<<< orphan*/  ires; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_MEM ; 
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  ERR_VAL ; 
 int /*<<< orphan*/  HCI_REG (int /*<<< orphan*/ *,struct hci_inq_res*) ; 
 int /*<<< orphan*/  bd_addr_set (int /*<<< orphan*/ *,struct bd_addr*) ; 
 struct hci_inq_res* btmemb_alloc (int /*<<< orphan*/ *) ; 
 TYPE_1__* hci_dev ; 
 int /*<<< orphan*/  hci_inq_results ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void**,int) ; 

err_t hci_reg_dev_info(struct bd_addr *bdaddr,u8_t *cod,u8_t psrm,u8_t psm,u16_t co)
{
	struct hci_inq_res *ires;

	if(hci_dev==NULL) return ERR_VAL;

	if((ires=btmemb_alloc(&hci_inq_results))!=NULL) {
		bd_addr_set(&(ires->bdaddr),bdaddr);
		memcpy(ires->cod,cod,3);
		ires->psrm = psrm;
		ires->psm = psm;
		ires->co = co;
		ires->next = NULL;

		HCI_REG(&(hci_dev->ires),ires);
		return ERR_OK;
	}
	return ERR_MEM;
}