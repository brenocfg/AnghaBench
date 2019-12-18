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
 scalar_t__ DECL_CONTEXT (scalar_t__) ; 
 scalar_t__ DECL_P (scalar_t__) ; 
 scalar_t__ nonstatic_local_decl_p (scalar_t__) ; 

int
cp_auto_var_in_fn_p (tree var, tree fn)
{
  return (DECL_P (var) && DECL_CONTEXT (var) == fn
	  && nonstatic_local_decl_p (var));
}