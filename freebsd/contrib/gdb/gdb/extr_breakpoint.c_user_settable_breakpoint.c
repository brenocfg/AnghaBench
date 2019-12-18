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
struct breakpoint {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ bp_access_watchpoint ; 
 scalar_t__ bp_breakpoint ; 
 scalar_t__ bp_catch_catch ; 
 scalar_t__ bp_catch_exec ; 
 scalar_t__ bp_catch_fork ; 
 scalar_t__ bp_catch_load ; 
 scalar_t__ bp_catch_throw ; 
 scalar_t__ bp_catch_unload ; 
 scalar_t__ bp_catch_vfork ; 
 scalar_t__ bp_hardware_breakpoint ; 
 scalar_t__ bp_hardware_watchpoint ; 
 scalar_t__ bp_read_watchpoint ; 
 scalar_t__ bp_watchpoint ; 

__attribute__((used)) static int
user_settable_breakpoint (const struct breakpoint *b)
{
  return (b->type == bp_breakpoint
	  || b->type == bp_catch_load
	  || b->type == bp_catch_unload
	  || b->type == bp_catch_fork
	  || b->type == bp_catch_vfork
	  || b->type == bp_catch_exec
	  || b->type == bp_catch_catch
	  || b->type == bp_catch_throw
	  || b->type == bp_hardware_breakpoint
	  || b->type == bp_watchpoint
	  || b->type == bp_read_watchpoint
	  || b->type == bp_access_watchpoint
	  || b->type == bp_hardware_watchpoint);
}