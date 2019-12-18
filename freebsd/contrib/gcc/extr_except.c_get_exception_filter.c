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
struct function {TYPE_1__* eh; } ;
typedef  scalar_t__ rtx ;
struct TYPE_4__ {int /*<<< orphan*/  (* eh_return_filter_mode ) () ;} ;
struct TYPE_3__ {scalar_t__ filter; } ;

/* Variables and functions */
 struct function* cfun ; 
 scalar_t__ gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 TYPE_2__ targetm ; 

rtx
get_exception_filter (struct function *fun)
{
  rtx filter = fun->eh->filter;
  if (fun == cfun && ! filter)
    {
      filter = gen_reg_rtx (targetm.eh_return_filter_mode ());
      fun->eh->filter = filter;
    }
  return filter;
}