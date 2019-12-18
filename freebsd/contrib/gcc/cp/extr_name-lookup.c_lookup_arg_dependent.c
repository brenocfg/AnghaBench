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
typedef  void* tree ;
struct arg_lookup {void* functions; void* namespaces; void* classes; void* args; void* name; } ;

/* Variables and functions */
 void* NULL_TREE ; 
 int /*<<< orphan*/  POP_TIMEVAR_AND_RETURN (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ TREE_CODE (void*) ; 
 int /*<<< orphan*/  TV_NAME_LOOKUP ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  arg_assoc_args (struct arg_lookup*,void*) ; 
 int /*<<< orphan*/  error (char*,void*) ; 
 void* error_mark_node ; 
 int /*<<< orphan*/  is_overloaded_fn (void*) ; 
 void* remove_hidden_names (void*) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 

tree
lookup_arg_dependent (tree name, tree fns, tree args)
{
  struct arg_lookup k;

  timevar_push (TV_NAME_LOOKUP);

  /* Remove any hidden friend functions from the list of functions
     found so far.  They will be added back by arg_assoc_class as
     appropriate.  */
  fns = remove_hidden_names (fns);

  k.name = name;
  k.args = args;
  k.functions = fns;
  k.classes = NULL_TREE;

  /* We previously performed an optimization here by setting
     NAMESPACES to the current namespace when it was safe. However, DR
     164 says that namespaces that were already searched in the first
     stage of template processing are searched again (potentially
     picking up later definitions) in the second stage. */
  k.namespaces = NULL_TREE;

  arg_assoc_args (&k, args);

  fns = k.functions;
  
  if (fns
      && TREE_CODE (fns) != VAR_DECL
      && !is_overloaded_fn (fns))
    {
      error ("argument dependent lookup finds %q+D", fns);
      error ("  in call to %qD", name);
      fns = error_mark_node;
    }
    
  POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, fns);
}