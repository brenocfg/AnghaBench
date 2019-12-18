#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cgraph_node {struct cgraph_edge* callees; } ;
struct cgraph_edge {struct cgraph_node* callee; struct cgraph_edge* next_callee; } ;
typedef  TYPE_1__* ipa_reference_vars_info_t ;
typedef  TYPE_2__* ipa_reference_global_vars_info_t ;
struct TYPE_5__ {scalar_t__ statics_read; scalar_t__ statics_written; } ;
struct TYPE_4__ {TYPE_2__* global; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_FREE (scalar_t__) ; 
 scalar_t__ all_module_statics ; 
 int /*<<< orphan*/  bitmap_ior_into (scalar_t__,scalar_t__) ; 
 struct cgraph_node* cgraph_master_clone (struct cgraph_node*) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 TYPE_1__* get_reference_vars_info_from_cgraph (struct cgraph_node*) ; 

__attribute__((used)) static void
propagate_bits (struct cgraph_node *x)
{
  ipa_reference_vars_info_t x_info = get_reference_vars_info_from_cgraph (x);
  ipa_reference_global_vars_info_t x_global = x_info->global;

  struct cgraph_edge *e;
  for (e = x->callees; e; e = e->next_callee) 
    {
      struct cgraph_node *y = e->callee;

      /* Only look at the master nodes and skip external nodes.  */
      y = cgraph_master_clone (y);
      if (y)
	{
	  if (get_reference_vars_info_from_cgraph (y))
	    {
	      ipa_reference_vars_info_t y_info = get_reference_vars_info_from_cgraph (y);
	      ipa_reference_global_vars_info_t y_global = y_info->global;
	      
	      if (x_global->statics_read
		  != all_module_statics)
		{
		  if (y_global->statics_read 
		      == all_module_statics)
		    {
		      BITMAP_FREE (x_global->statics_read);
		      x_global->statics_read 
			= all_module_statics;
		    }
		  /* Skip bitmaps that are pointer equal to node's bitmap
		     (no reason to spin within the cycle).  */
		  else if (x_global->statics_read 
			   != y_global->statics_read)
		    bitmap_ior_into (x_global->statics_read,
				     y_global->statics_read);
		}
	      
	      if (x_global->statics_written 
		  != all_module_statics)
		{
		  if (y_global->statics_written 
		      == all_module_statics)
		    {
		      BITMAP_FREE (x_global->statics_written);
		      x_global->statics_written 
			= all_module_statics;
		    }
		  /* Skip bitmaps that are pointer equal to node's bitmap
		     (no reason to spin within the cycle).  */
		  else if (x_global->statics_written 
			   != y_global->statics_written)
		    bitmap_ior_into (x_global->statics_written,
				     y_global->statics_written);
		}
	    }
	  else 
	    {
	      gcc_unreachable ();
	    }
	}
    }
}