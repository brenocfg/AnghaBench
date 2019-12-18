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
struct bt_state {int /*<<< orphan*/  last_err; int /*<<< orphan*/  hci_cmdq; int /*<<< orphan*/  hci_cmddone; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_VAL ; 
 int /*<<< orphan*/  LWP_ThreadSleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline s32 __bte_waitcmdfinish(struct bt_state *state)
{
	u32 level;
	s32 ret;

	if(!state) return ERR_VAL;

	_CPU_ISR_Disable(level);
	while(!state->hci_cmddone)
		LWP_ThreadSleep(state->hci_cmdq);
	ret = state->last_err;
	_CPU_ISR_Restore(level);

	return ret;
}