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
typedef  void* tree ;
struct TYPE_2__ {void** decl; } ;

/* Variables and functions */
 void* NULL_TREE ; 
 void* build_int_cst (void*,unsigned int) ; 
 TYPE_1__* fname_vars ; 
 void* saved_function_name_decls ; 
 void* tree_cons (void*,void*,void*) ; 

void
start_fname_decls (void)
{
  unsigned ix;
  tree saved = NULL_TREE;

  for (ix = 0; fname_vars[ix].decl; ix++)
    {
      tree decl = *fname_vars[ix].decl;

      if (decl)
	{
	  saved = tree_cons (decl, build_int_cst (NULL_TREE, ix), saved);
	  *fname_vars[ix].decl = NULL_TREE;
	}
    }
  if (saved || saved_function_name_decls)
    /* Normally they'll have been NULL, so only push if we've got a
       stack, or they are non-NULL.  */
    saved_function_name_decls = tree_cons (saved, NULL_TREE,
					   saved_function_name_decls);
}