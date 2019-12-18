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
typedef  int /*<<< orphan*/  ttstate_t ;
typedef  int /*<<< orphan*/  lwpid_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_process_first_stopped_thread_id (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static lwpid_t
get_active_tid_of_pid (int pid)
{
  ttstate_t thread_state;

  return get_process_first_stopped_thread_id (pid, &thread_state);
}