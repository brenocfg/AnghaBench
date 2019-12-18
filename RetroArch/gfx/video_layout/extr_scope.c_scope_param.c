#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* param; int /*<<< orphan*/  level; } ;
typedef  TYPE_1__ scope_t ;
struct TYPE_8__ {char* value; struct TYPE_8__* prev; int /*<<< orphan*/  level; int /*<<< orphan*/ * generator; void* name; } ;
typedef  TYPE_2__ param_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 void* init_string (char const*) ; 
 scalar_t__ malloc (int) ; 
 TYPE_2__* param_find (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 char const* scope_eval (TYPE_1__*,char const*) ; 

void scope_param(scope_t *scope, const char *name, const char *value)
{
   param_t *param;
   char *eval_name = init_string(scope_eval(scope, name));
   char *eval_value = init_string(scope_eval(scope, value));

   if ((param = param_find(scope, eval_name, scope->level)))
   {
      free(param->value);
      param->value = eval_value;
   }
   else
   {
      param = (param_t*)malloc(sizeof(param_t));
      param->name = init_string(name);
      param->value = eval_value;
      param->generator = NULL;
      param->level = scope->level;
      param->prev = scope->param;
      scope->param = param;
   }

   free(eval_name);
}