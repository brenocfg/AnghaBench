#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ level; TYPE_2__* param; } ;
typedef  TYPE_1__ scope_t ;
struct TYPE_7__ {scalar_t__ level; struct TYPE_7__* prev; } ;
typedef  TYPE_2__ param_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  param_deinit (TYPE_2__*) ; 

void scope_pop(scope_t *scope)
{
   param_t *param;

   --scope->level;

   while ((param = scope->param))
   {
      if (param->level <= scope->level)
         break;

      scope->param = param->prev;
      param_deinit(param);
      free(param);
   }
}