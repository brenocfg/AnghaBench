#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int bool_; } ;
struct rmsgpack_dom_value {scalar_t__ type; TYPE_3__ val; } ;
struct TYPE_4__ {int /*<<< orphan*/  argv; int /*<<< orphan*/  argc; int /*<<< orphan*/  (* func ) (struct rmsgpack_dom_value,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__ invocation; int /*<<< orphan*/  value; } ;
struct argument {scalar_t__ type; TYPE_2__ a; } ;

/* Variables and functions */
 scalar_t__ AT_VALUE ; 
 scalar_t__ RDT_BOOL ; 
 scalar_t__ RDT_MAP ; 
 scalar_t__ RDT_NULL ; 
 struct rmsgpack_dom_value func_equals (struct rmsgpack_dom_value,int,struct argument*) ; 
 struct rmsgpack_dom_value query_func_is_true (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct rmsgpack_dom_value* rmsgpack_dom_value_map_value (struct rmsgpack_dom_value*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct rmsgpack_dom_value,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rmsgpack_dom_value query_func_all_map(
      struct rmsgpack_dom_value input,
      unsigned argc, const struct argument *argv)
{
   unsigned i;
   struct argument arg;
   struct rmsgpack_dom_value res;
   struct rmsgpack_dom_value nil_value;
   struct rmsgpack_dom_value *value = NULL;

   res.type       = RDT_BOOL;
   res.val.bool_  = 1;

   nil_value.type = RDT_NULL;

   if (argc % 2 != 0)
   {
      res.val.bool_ = 0;
      return res;
   }

   if (input.type != RDT_MAP)
      return res;

   for (i = 0; i < argc; i += 2)
   {
      arg = argv[i];
      if (arg.type != AT_VALUE)
      {
         res.val.bool_ = 0;
         goto clean;
      }
      value = rmsgpack_dom_value_map_value(&input, &arg.a.value);
      if (!value) /* All missing fields are nil */
         value = &nil_value;
      arg = argv[i + 1];
      if (arg.type == AT_VALUE)
         res = func_equals(*value, 1, &arg);
      else
      {
         res = query_func_is_true(arg.a.invocation.func(
                  *value,
                  arg.a.invocation.argc,
                  arg.a.invocation.argv
                  ), 0, NULL);
         value = NULL;
      }
      if (!res.val.bool_)
         break;
   }
clean:
   return res;
}