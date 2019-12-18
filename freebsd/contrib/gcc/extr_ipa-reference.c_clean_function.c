#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct cgraph_node {int /*<<< orphan*/  decl; } ;
typedef  TYPE_1__* ipa_reference_vars_info_t ;
typedef  TYPE_2__* ipa_reference_local_vars_info_t ;
typedef  TYPE_2__* ipa_reference_global_vars_info_t ;
struct TYPE_9__ {TYPE_2__* reference_vars_info; } ;
struct TYPE_8__ {scalar_t__ statics_read; scalar_t__ statics_written; scalar_t__ statics_not_read; scalar_t__ statics_not_written; } ;
struct TYPE_7__ {TYPE_2__* global; TYPE_2__* local; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_FREE (scalar_t__) ; 
 scalar_t__ all_module_statics ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_5__* get_function_ann (int /*<<< orphan*/ ) ; 
 TYPE_1__* get_reference_vars_info_from_cgraph (struct cgraph_node*) ; 

__attribute__((used)) static void
clean_function (struct cgraph_node *fn)
{
  ipa_reference_vars_info_t info = get_reference_vars_info_from_cgraph (fn);
  ipa_reference_local_vars_info_t l = info->local;
  ipa_reference_global_vars_info_t g = info->global;
  
  if (l)
    {
      if (l->statics_read
	  && l->statics_read != all_module_statics)
	BITMAP_FREE (l->statics_read);
      if (l->statics_written
	  &&l->statics_written != all_module_statics)
	BITMAP_FREE (l->statics_written);
      free (l);
    }
  
  if (g)
    {
      if (g->statics_read
	  && g->statics_read != all_module_statics)
	BITMAP_FREE (g->statics_read);
      
      if (g->statics_written
	  && g->statics_written != all_module_statics)
	BITMAP_FREE (g->statics_written);
      
      if (g->statics_not_read
	  && g->statics_not_read != all_module_statics)
	BITMAP_FREE (g->statics_not_read);
      
      if (g->statics_not_written
	  && g->statics_not_written != all_module_statics)
	BITMAP_FREE (g->statics_not_written);
      free (g);
    }

  
  free (get_function_ann (fn->decl)->reference_vars_info);
  get_function_ann (fn->decl)->reference_vars_info = NULL;
}