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
typedef  int /*<<< orphan*/  diva_os_spin_lock_magic_t ;

/* Variables and functions */
 int /*<<< orphan*/ * TraceFilter ; 
 int /*<<< orphan*/  dbg_q_lock ; 
 int /*<<< orphan*/  diva_os_enter_spin_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  diva_os_leave_spin_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 int strlen (int /*<<< orphan*/ *) ; 

int diva_get_trace_filter (int max_length, char* filter) {
  diva_os_spin_lock_magic_t old_irql;
  int len;

  diva_os_enter_spin_lock (&dbg_q_lock, &old_irql, "read_filter");
  len = strlen (&TraceFilter[0]) + 1;
  if (max_length >= len) {
    memcpy (filter, &TraceFilter[0], len);
  }
  diva_os_leave_spin_lock (&dbg_q_lock, &old_irql, "read_filter");

  return (len);
}