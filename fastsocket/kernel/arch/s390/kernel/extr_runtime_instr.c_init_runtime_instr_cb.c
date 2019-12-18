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
struct runtime_instr_cb {int buf_limit; int home_space; int int_requested; int pstate; int pstate_set_buf; int pstate_sample; int pstate_collect; int valid; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 scalar_t__ HOME_SPACE_MODE ; 
 int /*<<< orphan*/  PAGE_DEFAULT_KEY ; 
 scalar_t__ user_mode ; 

__attribute__((used)) static void init_runtime_instr_cb(struct runtime_instr_cb *cb)
{
	cb->buf_limit = 0xfff;
	if (user_mode == HOME_SPACE_MODE)
		cb->home_space = 1;
	cb->int_requested = 1;
	cb->pstate = 1;
	cb->pstate_set_buf = 1;
	cb->pstate_sample = 1;
	cb->pstate_collect = 1;
	cb->key = PAGE_DEFAULT_KEY;
	cb->valid = 1;
}