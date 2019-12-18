#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int argc; struct argument* argv; } ;
struct TYPE_3__ {TYPE_2__ invocation; int /*<<< orphan*/  value; } ;
struct argument {scalar_t__ type; TYPE_1__ a; } ;

/* Variables and functions */
 scalar_t__ AT_FUNCTION ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  rmsgpack_dom_value_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void query_argument_free(struct argument *arg)
{
   unsigned i;

   if (arg->type != AT_FUNCTION)
   {
      rmsgpack_dom_value_free(&arg->a.value);
      return;
   }

   for (i = 0; i < arg->a.invocation.argc; i++)
      query_argument_free(&arg->a.invocation.argv[i]);

   free((void*)arg->a.invocation.argv);
}