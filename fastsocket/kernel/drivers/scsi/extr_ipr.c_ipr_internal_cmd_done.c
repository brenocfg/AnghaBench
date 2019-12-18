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
struct ipr_cmnd {int /*<<< orphan*/  completion; int /*<<< orphan*/ * sibling; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipr_internal_cmd_done(struct ipr_cmnd *ipr_cmd)
{
	if (ipr_cmd->sibling)
		ipr_cmd->sibling = NULL;
	else
		complete(&ipr_cmd->completion);
}