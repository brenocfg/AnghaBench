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
struct TYPE_6__ {scalar_t__ bool_; } ;
struct rmsgpack_dom_value {TYPE_3__ val; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int /*<<< orphan*/  argv; int /*<<< orphan*/  argc; int /*<<< orphan*/  (* func ) (struct rmsgpack_dom_value,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__ invocation; } ;
struct argument {scalar_t__ type; TYPE_2__ a; } ;

/* Variables and functions */
 scalar_t__ AT_VALUE ; 
 int /*<<< orphan*/  RDT_BOOL ; 
 struct rmsgpack_dom_value func_equals (struct rmsgpack_dom_value,int,struct argument const*) ; 
 struct rmsgpack_dom_value query_func_is_true (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct rmsgpack_dom_value,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rmsgpack_dom_value query_func_operator_and(
      struct rmsgpack_dom_value input,
      unsigned argc, const struct argument * argv)
{
   unsigned i;
   struct rmsgpack_dom_value res;

   res.type      = RDT_BOOL;
   res.val.bool_ = 0;

   for (i = 0; i < argc; i++)
   {
      if (argv[i].type == AT_VALUE)
         res = func_equals(input, 1, &argv[i]);
      else
      {
         res = query_func_is_true(
               argv[i].a.invocation.func(input,
                  argv[i].a.invocation.argc,
                  argv[i].a.invocation.argv
                  ),
               0, NULL);
      }

      if (!res.val.bool_)
         return res;
   }
   return res;
}