#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ bool_; } ;
struct rmsgpack_dom_value {scalar_t__ type; TYPE_1__ val; } ;
struct argument {int dummy; } ;

/* Variables and functions */
 scalar_t__ RDT_BOOL ; 

__attribute__((used)) static struct rmsgpack_dom_value query_func_is_true(
      struct rmsgpack_dom_value input,
      unsigned argc, const struct argument *argv)
{
   struct rmsgpack_dom_value res;

   res.type      = RDT_BOOL;
   res.val.bool_ = 0;

   if (argc > 0 || input.type != RDT_BOOL)
      res.val.bool_ = 0;
   else
      res.val.bool_ = input.val.bool_;

   return res;
}