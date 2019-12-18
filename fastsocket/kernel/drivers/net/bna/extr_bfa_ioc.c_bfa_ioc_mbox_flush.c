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
struct bfa_mbox_cmd {int dummy; } ;
struct bfa_ioc_mbox_mod {int /*<<< orphan*/  cmd_q; } ;
struct bfa_ioc {struct bfa_ioc_mbox_mod mbox_mod; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_q_deq (int /*<<< orphan*/ *,struct bfa_mbox_cmd**) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bfa_ioc_mbox_flush(struct bfa_ioc *ioc)
{
	struct bfa_ioc_mbox_mod *mod = &ioc->mbox_mod;
	struct bfa_mbox_cmd *cmd;

	while (!list_empty(&mod->cmd_q))
		bfa_q_deq(&mod->cmd_q, &cmd);
}