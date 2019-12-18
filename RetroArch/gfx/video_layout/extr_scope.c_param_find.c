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
struct TYPE_5__ {TYPE_2__* param; } ;
typedef  TYPE_1__ scope_t ;
struct TYPE_6__ {int level; struct TYPE_6__* prev; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ param_t ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static param_t *param_find(scope_t *scope, const char *name, int level)
{
   param_t *param = scope->param;

   while (param && param->level >= level)
   {
      if (strcmp(param->name, name) == 0)
         return param;
      param = param->prev;
   }

   return NULL;
}