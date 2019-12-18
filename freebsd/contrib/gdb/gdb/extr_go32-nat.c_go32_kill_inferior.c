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
 int /*<<< orphan*/  child_cmd ; 
 int /*<<< orphan*/  go32_ops ; 
 int /*<<< orphan*/  redir_cmdline_delete (int /*<<< orphan*/ *) ; 
 scalar_t__ resume_is_step ; 
 int resume_signal ; 
 int /*<<< orphan*/  unpush_target (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
go32_kill_inferior (void)
{
  redir_cmdline_delete (&child_cmd);
  resume_signal = -1;
  resume_is_step = 0;
  unpush_target (&go32_ops);
}