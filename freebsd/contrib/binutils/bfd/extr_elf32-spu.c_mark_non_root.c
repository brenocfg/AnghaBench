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
struct function_info {void* visit1; void* non_root; struct call_info* call_list; } ;
struct call_info {struct function_info* fun; struct call_info* next; } ;

/* Variables and functions */
 void* TRUE ; 

__attribute__((used)) static void
mark_non_root (struct function_info *fun)
{
  struct call_info *call;

  fun->visit1 = TRUE;
  for (call = fun->call_list; call; call = call->next)
    {
      call->fun->non_root = TRUE;
      if (!call->fun->visit1)
	mark_non_root (call->fun);
    }
}