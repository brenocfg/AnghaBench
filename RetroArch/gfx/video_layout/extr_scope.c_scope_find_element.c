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
struct TYPE_5__ {int elements_count; TYPE_2__* elements; } ;
typedef  TYPE_1__ scope_t ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ element_t ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

element_t *scope_find_element(scope_t *scope, const char *name)
{
   int i;

   for (i = 0; i < scope->elements_count; ++i)
   {
      if (strcmp(name, scope->elements[i].name) == 0)
         return &scope->elements[i];
   }

   return NULL;
}