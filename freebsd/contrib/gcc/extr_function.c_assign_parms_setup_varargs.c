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
struct assign_parm_data_one {int /*<<< orphan*/  passed_type; int /*<<< orphan*/  promoted_mode; } ;
struct assign_parm_data_all {int pretend_args_size; int /*<<< orphan*/  args_so_far; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* setup_incoming_varargs ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ;} ;
struct TYPE_4__ {TYPE_1__ calls; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 TYPE_2__ targetm ; 

__attribute__((used)) static void
assign_parms_setup_varargs (struct assign_parm_data_all *all,
			    struct assign_parm_data_one *data, bool no_rtl)
{
  int varargs_pretend_bytes = 0;

  targetm.calls.setup_incoming_varargs (&all->args_so_far,
					data->promoted_mode,
					data->passed_type,
					&varargs_pretend_bytes, no_rtl);

  /* If the back-end has requested extra stack space, record how much is
     needed.  Do not change pretend_args_size otherwise since it may be
     nonzero from an earlier partial argument.  */
  if (varargs_pretend_bytes > 0)
    all->pretend_args_size = varargs_pretend_bytes;
}