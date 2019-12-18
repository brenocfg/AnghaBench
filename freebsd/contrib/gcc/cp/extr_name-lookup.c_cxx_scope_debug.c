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
struct TYPE_4__ {int /*<<< orphan*/  this_entity; } ;
typedef  TYPE_1__ cxx_scope ;

/* Variables and functions */
 char* cxx_scope_descriptor (TYPE_1__*) ; 
 int /*<<< orphan*/  verbatim (char*,char const*,char const*,void*,int,...) ; 

__attribute__((used)) static void
cxx_scope_debug (cxx_scope *scope, int line, const char *action)
{
  const char *desc = cxx_scope_descriptor (scope);
  if (scope->this_entity)
    verbatim ("%s %s(%E) %p %d\n", action, desc,
	      scope->this_entity, (void *) scope, line);
  else
    verbatim ("%s %s %p %d\n", action, desc, (void *) scope, line);
}