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
typedef  scalar_t__ u8_t ;
struct hci_pcb {int dummy; } ;
struct bt_state {scalar_t__ hci_inited; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_CONN ; 
 int /*<<< orphan*/  ERR_OK ; 
 scalar_t__ HCI_SUCCESS ; 
 int /*<<< orphan*/  __bte_cmdfinish (struct bt_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_cmd_complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  physbusif_close () ; 

__attribute__((used)) static err_t __bte_shutdown_finished(void *arg,struct hci_pcb *pcb,u8_t ogf,u8_t ocf,u8_t result)
{
	err_t err;
	struct bt_state *state = (struct bt_state*)arg;

	if(state==NULL) return ERR_OK;

	state->hci_inited = 0;
	hci_cmd_complete(NULL);
	if(result==HCI_SUCCESS)
		err = ERR_OK;
	else
		err = ERR_CONN;

	physbusif_close();
	return __bte_cmdfinish(state,err);
}