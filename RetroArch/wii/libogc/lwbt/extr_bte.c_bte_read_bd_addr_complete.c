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
typedef  scalar_t__ u8_t ;
struct TYPE_2__ {int /*<<< orphan*/ * addr; } ;
struct hci_pcb {TYPE_1__ bdaddr; } ;
struct bt_state {scalar_t__ usrdata; } ;
struct bd_addr {int /*<<< orphan*/ * addr; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_CONN ; 
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  ERR_VAL ; 
 scalar_t__ HCI_INFO_PARAM_OGF ; 
 scalar_t__ HCI_R_BD_ADDR_OCF ; 
 scalar_t__ HCI_SUCCESS ; 
 int /*<<< orphan*/  LOG (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  __bte_cmdfinish (struct bt_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i ; 

err_t bte_read_bd_addr_complete(void *arg,struct hci_pcb *pcb,u8_t ogf,u8_t ocf,u8_t result)
{
    struct bd_addr *bdaddr;
    struct bt_state *state = (struct bt_state*)arg;

    if(!pcb) return ERR_CONN;

    LOG("bte_read_bd_addr_complete(%02x,%p)\n", result, &pcb->bdaddr);

    if(state==NULL) return ERR_VAL;

    if(!(ogf==HCI_INFO_PARAM_OGF && ocf==HCI_R_BD_ADDR_OCF)) return __bte_cmdfinish(state,ERR_CONN);

    if(result == HCI_SUCCESS) {
        bdaddr = (struct bd_addr *)state->usrdata;
        if (bdaddr != NULL) {
            bdaddr->addr[0] = pcb->bdaddr.addr[5];
            bdaddr->addr[1] = pcb->bdaddr.addr[4];
            bdaddr->addr[2] = pcb->bdaddr.addr[3];
            bdaddr->addr[3] = pcb->bdaddr.addr[2];
            bdaddr->addr[4] = pcb->bdaddr.addr[1];
            bdaddr->addr[5] = pcb->bdaddr.addr[0];
        }
        LOG("bte_read_bd_addr_complete(%02x,%p,%d)\n",result,bdaddr,i);
        __bte_cmdfinish(state,ERR_OK);
        return ERR_OK;
    }

    return __bte_cmdfinish(state,ERR_VAL);
}