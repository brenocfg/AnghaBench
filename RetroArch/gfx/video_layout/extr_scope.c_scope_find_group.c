#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ view_t ;
struct TYPE_6__ {int groups_count; TYPE_1__* groups; } ;
typedef  TYPE_2__ scope_t ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

view_t *scope_find_group(scope_t *scope, const char *name)
{
   int i;

   for (i = 0; i < scope->groups_count; ++i)
   {
      if (strcmp(name, scope->groups[i].name) == 0)
         return &scope->groups[i];
   }

   return NULL;
}