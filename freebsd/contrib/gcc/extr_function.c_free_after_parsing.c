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
struct function {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* final ) (struct function*) ;} ;
struct TYPE_4__ {TYPE_1__ function; } ;

/* Variables and functions */
 TYPE_2__ lang_hooks ; 
 int /*<<< orphan*/  stub1 (struct function*) ; 

void
free_after_parsing (struct function *f)
{
  /* f->expr->forced_labels is used by code generation.  */
  /* f->emit->regno_reg_rtx is used by code generation.  */
  /* f->varasm is used by code generation.  */
  /* f->eh->eh_return_stub_label is used by code generation.  */

  lang_hooks.function.final (f);
}