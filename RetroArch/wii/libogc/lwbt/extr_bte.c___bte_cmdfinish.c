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
typedef  int /*<<< orphan*/  u32 ;
struct bt_state {int hci_cmddone; int /*<<< orphan*/  hci_cmdq; int /*<<< orphan*/  usrdata; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  last_err; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_VAL ; 
 int /*<<< orphan*/  LWP_ThreadSignal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline s32 __bte_cmdfinish(struct bt_state *state,err_t err)
{
	u32 level;

	if(!state) return ERR_VAL;

	_CPU_ISR_Disable(level);
	state->last_err = err;
	state->hci_cmddone = 1;
	if(state->cb!=NULL)
		state->cb(err,state->usrdata);
	else
		LWP_ThreadSignal(state->hci_cmdq);
	_CPU_ISR_Restore(level);

	return err;
}