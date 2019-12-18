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
struct breakpoint {int thread; } ;

/* Variables and functions */
 scalar_t__ in_thread_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int pid_to_thread_id (int /*<<< orphan*/ ) ; 

void
breakpoint_re_set_thread (struct breakpoint *b)
{
  if (b->thread != -1)
    {
      if (in_thread_list (inferior_ptid))
	b->thread = pid_to_thread_id (inferior_ptid);
    }
}