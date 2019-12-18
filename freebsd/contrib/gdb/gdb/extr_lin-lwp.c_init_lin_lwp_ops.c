#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* to_shortname; char* to_longname; char* to_doc; int /*<<< orphan*/  to_magic; int /*<<< orphan*/  to_has_thread_control; int /*<<< orphan*/  to_stratum; int /*<<< orphan*/  to_insert_exec_catchpoint; int /*<<< orphan*/  to_insert_vfork_catchpoint; int /*<<< orphan*/  to_insert_fork_catchpoint; int /*<<< orphan*/  to_post_attach; int /*<<< orphan*/  to_post_startup_inferior; int /*<<< orphan*/  to_pid_to_str; int /*<<< orphan*/  to_thread_alive; int /*<<< orphan*/  to_mourn_inferior; int /*<<< orphan*/  to_create_inferior; int /*<<< orphan*/  to_kill; int /*<<< orphan*/  to_xfer_memory; int /*<<< orphan*/  to_store_registers; int /*<<< orphan*/  to_fetch_registers; int /*<<< orphan*/  to_wait; int /*<<< orphan*/  to_resume; int /*<<< orphan*/  to_detach; int /*<<< orphan*/  to_attach; int /*<<< orphan*/  to_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPS_MAGIC ; 
 int /*<<< orphan*/  child_insert_exec_catchpoint ; 
 int /*<<< orphan*/  child_insert_fork_catchpoint ; 
 int /*<<< orphan*/  child_insert_vfork_catchpoint ; 
 int /*<<< orphan*/  child_post_attach ; 
 int /*<<< orphan*/  child_post_startup_inferior ; 
 int /*<<< orphan*/  fetch_inferior_registers ; 
 int /*<<< orphan*/  lin_lwp_attach ; 
 int /*<<< orphan*/  lin_lwp_create_inferior ; 
 int /*<<< orphan*/  lin_lwp_detach ; 
 int /*<<< orphan*/  lin_lwp_kill ; 
 int /*<<< orphan*/  lin_lwp_mourn_inferior ; 
 int /*<<< orphan*/  lin_lwp_open ; 
 TYPE_1__ lin_lwp_ops ; 
 int /*<<< orphan*/  lin_lwp_pid_to_str ; 
 int /*<<< orphan*/  lin_lwp_resume ; 
 int /*<<< orphan*/  lin_lwp_thread_alive ; 
 int /*<<< orphan*/  lin_lwp_wait ; 
 int /*<<< orphan*/  lin_lwp_xfer_memory ; 
 int /*<<< orphan*/  store_inferior_registers ; 
 int /*<<< orphan*/  tc_schedlock ; 
 int /*<<< orphan*/  thread_stratum ; 

__attribute__((used)) static void
init_lin_lwp_ops (void)
{
#if 0
  lin_lwp_ops.to_open = lin_lwp_open;
#endif
  lin_lwp_ops.to_shortname = "lwp-layer";
  lin_lwp_ops.to_longname = "lwp-layer";
  lin_lwp_ops.to_doc = "Low level threads support (LWP layer)";
  lin_lwp_ops.to_attach = lin_lwp_attach;
  lin_lwp_ops.to_detach = lin_lwp_detach;
  lin_lwp_ops.to_resume = lin_lwp_resume;
  lin_lwp_ops.to_wait = lin_lwp_wait;
  /* fetch_inferior_registers and store_inferior_registers will
     honor the LWP id, so we can use them directly.  */
  lin_lwp_ops.to_fetch_registers = fetch_inferior_registers;
  lin_lwp_ops.to_store_registers = store_inferior_registers;
  lin_lwp_ops.to_xfer_memory = lin_lwp_xfer_memory;
  lin_lwp_ops.to_kill = lin_lwp_kill;
  lin_lwp_ops.to_create_inferior = lin_lwp_create_inferior;
  lin_lwp_ops.to_mourn_inferior = lin_lwp_mourn_inferior;
  lin_lwp_ops.to_thread_alive = lin_lwp_thread_alive;
  lin_lwp_ops.to_pid_to_str = lin_lwp_pid_to_str;
  lin_lwp_ops.to_post_startup_inferior = child_post_startup_inferior;
  lin_lwp_ops.to_post_attach = child_post_attach;
  lin_lwp_ops.to_insert_fork_catchpoint = child_insert_fork_catchpoint;
  lin_lwp_ops.to_insert_vfork_catchpoint = child_insert_vfork_catchpoint;
  lin_lwp_ops.to_insert_exec_catchpoint = child_insert_exec_catchpoint;

  lin_lwp_ops.to_stratum = thread_stratum;
  lin_lwp_ops.to_has_thread_control = tc_schedlock;
  lin_lwp_ops.to_magic = OPS_MAGIC;
}