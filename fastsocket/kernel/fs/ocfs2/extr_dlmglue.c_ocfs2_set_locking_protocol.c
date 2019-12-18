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

/* Variables and functions */
 int /*<<< orphan*/  lproto ; 
 int /*<<< orphan*/  ocfs2_stack_glue_set_locking_protocol (int /*<<< orphan*/ *) ; 

void ocfs2_set_locking_protocol(void)
{
	ocfs2_stack_glue_set_locking_protocol(&lproto);
}