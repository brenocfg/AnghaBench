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
struct bfa_msgq_cmdq {scalar_t__ bytes_to_copy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_msgq_cmdq_copy_rsp (struct bfa_msgq_cmdq*) ; 

__attribute__((used)) static void
bfa_msgq_cmdq_copy_next(void *arg)
{
	struct bfa_msgq_cmdq *cmdq = (struct bfa_msgq_cmdq *)arg;

	if (cmdq->bytes_to_copy)
		bfa_msgq_cmdq_copy_rsp(cmdq);
}