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
struct function_info {void* marking; void* visit2; struct call_info* call_list; } ;
struct call_info {struct call_info* next; struct function_info* fun; } ;
struct bfd_link_info {TYPE_1__* callbacks; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* info ) (int /*<<< orphan*/ ,char const*,char const*) ;} ;

/* Variables and functions */
 void* FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* func_name (struct function_info*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*,char const*) ; 

__attribute__((used)) static void
call_graph_traverse (struct function_info *fun, struct bfd_link_info *info)
{
  struct call_info **callp, *call;

  fun->visit2 = TRUE;
  fun->marking = TRUE;

  callp = &fun->call_list;
  while ((call = *callp) != NULL)
    {
      if (!call->fun->visit2)
	call_graph_traverse (call->fun, info);
      else if (call->fun->marking)
	{
	  const char *f1 = func_name (fun);
	  const char *f2 = func_name (call->fun);

	  info->callbacks->info (_("Stack analysis will ignore the call "
				   "from %s to %s\n"),
				 f1, f2);
	  *callp = call->next;
	  continue;
	}
      callp = &call->next;
    }
  fun->marking = FALSE;
}