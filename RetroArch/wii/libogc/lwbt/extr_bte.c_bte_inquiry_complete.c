#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8_t ;
typedef  scalar_t__ u16_t ;
struct inquiry_info_ex {int psrm; int psm; int co; int /*<<< orphan*/  cod; int /*<<< orphan*/  bdaddr; } ;
struct hci_pcb {int dummy; } ;
struct TYPE_4__ {int* addr; } ;
struct hci_inq_res {int* cod; int psrm; int psm; int co; struct hci_inq_res* next; TYPE_2__ bdaddr; } ;
struct bt_state {int dummy; } ;
typedef  int /*<<< orphan*/  err_t ;
struct TYPE_3__ {int num_founddevs; scalar_t__ num_maxdevs; struct inquiry_info_ex* info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_OK ; 
 scalar_t__ HCI_SUCCESS ; 
 int /*<<< orphan*/  __bte_cmdfinish (struct bt_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bd_addr_set (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_1__ btstate ; 
 int /*<<< orphan*/  free (struct inquiry_info_ex*) ; 
 int /*<<< orphan*/  hci_inquiry (int,int,scalar_t__,int /*<<< orphan*/  (*) (void*,struct hci_pcb*,struct hci_inq_res*,scalar_t__)) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

err_t bte_inquiry_complete(void *arg,struct hci_pcb *pcb,struct hci_inq_res *ires,u16_t result)
{
	u8_t i;
	struct hci_inq_res *p;
	struct bt_state *state = (struct bt_state*)arg;

	if(result==HCI_SUCCESS) {
		if(ires!=NULL) {

			if(btstate.info!=NULL) free(btstate.info);
			btstate.info = NULL;
			btstate.num_maxdevs = 0;
			btstate.num_founddevs = 0;

			p = ires;
			while(p!=NULL) {
				btstate.num_founddevs++;
				p = p->next;
			}

			p = ires;
			btstate.info = (struct inquiry_info_ex*)malloc(sizeof(struct inquiry_info_ex)*btstate.num_founddevs);
			for(i=0;i<btstate.num_founddevs && p!=NULL;i++) {
				bd_addr_set(&(btstate.info[i].bdaddr),&(p->bdaddr));
				memcpy(btstate.info[i].cod,p->cod,3);
				btstate.info[i].psrm = p->psrm;
				btstate.info[i].psm = p->psm;
				btstate.info[i].co = p->co;

				printf("bdaddr: %02x:%02x:%02x:%02x:%02x:%02x\n",p->bdaddr.addr[0],p->bdaddr.addr[1],p->bdaddr.addr[2],p->bdaddr.addr[3],p->bdaddr.addr[4],p->bdaddr.addr[5]);
				printf("cod:    %02x%02x%02x\n",p->cod[0],p->cod[1],p->cod[2]);
				printf("psrm:   %02x\n",p->psrm);
				printf("psm:   %02x\n",p->psm);
				printf("co:   %04x\n",p->co);
				p = p->next;
			}
			__bte_cmdfinish(state,ERR_OK);
		} else
			hci_inquiry(0x009E8B33,0x03,btstate.num_maxdevs,bte_inquiry_complete);
	}
	return ERR_OK;
}