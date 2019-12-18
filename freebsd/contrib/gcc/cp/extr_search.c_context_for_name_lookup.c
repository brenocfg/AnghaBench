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
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ ANON_AGGR_TYPE_P (scalar_t__) ; 
 scalar_t__ DECL_CONTEXT (scalar_t__) ; 
 scalar_t__ TYPE_CONTEXT (scalar_t__) ; 
 scalar_t__ TYPE_P (scalar_t__) ; 
 scalar_t__ global_namespace ; 

tree
context_for_name_lookup (tree decl)
{
  /* [class.union]

     For the purposes of name lookup, after the anonymous union
     definition, the members of the anonymous union are considered to
     have been defined in the scope in which the anonymous union is
     declared.  */
  tree context = DECL_CONTEXT (decl);

  while (context && TYPE_P (context) && ANON_AGGR_TYPE_P (context))
    context = TYPE_CONTEXT (context);
  if (!context)
    context = global_namespace;

  return context;
}