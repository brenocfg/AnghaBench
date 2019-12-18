#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ level; TYPE_4__* param; } ;
typedef  TYPE_3__ scope_t ;
struct TYPE_10__ {scalar_t__ level; int /*<<< orphan*/  value; TYPE_5__* generator; struct TYPE_10__* prev; } ;
typedef  TYPE_4__ param_t ;
struct TYPE_8__ {float val_dec; int val_int; } ;
struct TYPE_7__ {scalar_t__ val_int; scalar_t__ val_dec; } ;
struct TYPE_11__ {int shift; TYPE_2__ value; TYPE_1__ increment; scalar_t__ is_decimal; } ;
typedef  TYPE_5__ generator_t ;

/* Variables and functions */
 int SCOPE_BUFFER_SIZE ; 
 int /*<<< orphan*/  set_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,float) ; 

void scope_repeat(scope_t *scope)
{
   param_t *param;

   for (
         param = scope->param;
         param && param->level >= scope->level;
         param = param->prev)
   {
      generator_t *gen;
      if ((gen = param->generator))
      {
         char tmp[SCOPE_BUFFER_SIZE];
         tmp[0] = '\0';

         if (gen->is_decimal)
         {
            gen->value.val_dec += gen->increment.val_dec;
            if (gen->shift > 0)
               gen->value.val_dec = (float)((int)gen->value.val_dec << gen->shift);
            else if (gen->shift < 0)
               gen->value.val_dec = (float)((int)gen->value.val_dec >> -gen->shift);
            sprintf(tmp, "%f", gen->value.val_dec);
         }
         else
         {
            gen->value.val_int += gen->increment.val_int;
            if(gen->shift > 0)
               gen->value.val_int <<= gen->shift;
            else if (gen->shift < 0)
               gen->value.val_int >>= -gen->shift;
            sprintf(tmp, "%d", gen->value.val_int);
         }

         set_string(&param->value, tmp);
      }
   }
}