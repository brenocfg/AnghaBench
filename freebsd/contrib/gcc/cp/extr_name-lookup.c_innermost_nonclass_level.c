#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ kind; struct TYPE_4__* level_chain; } ;
typedef  TYPE_1__ cxx_scope ;

/* Variables and functions */
 TYPE_1__* current_binding_level ; 
 scalar_t__ sk_class ; 

__attribute__((used)) static cxx_scope *
innermost_nonclass_level (void)
{
  cxx_scope *b;

  b = current_binding_level;
  while (b->kind == sk_class)
    b = b->level_chain;

  return b;
}