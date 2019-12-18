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
struct cp_binding_level {scalar_t__ kind; } ;

/* Variables and functions */
 struct cp_binding_level* innermost_nonclass_level () ; 
 scalar_t__ sk_namespace ; 
 scalar_t__ sk_template_parms ; 

bool
toplevel_bindings_p (void)
{
  struct cp_binding_level *b = innermost_nonclass_level ();

  return b->kind == sk_namespace || b->kind == sk_template_parms;
}