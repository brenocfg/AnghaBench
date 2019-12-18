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
struct TYPE_4__ {scalar_t__ name; } ;
typedef  TYPE_1__ macro ;

/* Variables and functions */
 TYPE_1__* macros ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 
 scalar_t__ strncmp (scalar_t__,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static macro *
lookup_macro (const char *name)
{
  macro *m;

  for (m = macros; m->name; ++m)
    if (strncmp (m->name, name, strlen(m->name)) == 0)
      return m;

  return 0;
}