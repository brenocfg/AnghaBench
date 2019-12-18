#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int manual_bundling_on; } ;
struct TYPE_7__ {int manual_bundling_off; } ;
struct TYPE_5__ {scalar_t__ X_op; } ;
struct TYPE_6__ {int manual_bundling; int /*<<< orphan*/  default_explicit_mode; int /*<<< orphan*/  mode_explicitly_set; scalar_t__ explicit_mode; scalar_t__ detect_dv; TYPE_1__ qp; } ;

/* Variables and functions */
 TYPE_4__ CURR_SLOT ; 
 scalar_t__ O_absent ; 
 scalar_t__ O_register ; 
 TYPE_3__ PREV_SLOT ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  as_bad (char*) ; 
 int /*<<< orphan*/  as_warn (char*) ; 
 int /*<<< orphan*/  dot_dv_mode (char) ; 
 scalar_t__ ignore_input () ; 
 char* input_line_pointer ; 
 int /*<<< orphan*/  insn_group_break (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ md ; 

void
ia64_start_line ()
{
  static int first;

  if (!first) {
    /* Make sure we don't reference input_line_pointer[-1] when that's
       not valid.  */
    first = 1;
    return;
  }

  if (md.qp.X_op == O_register)
    as_bad ("qualifying predicate not followed by instruction");
  md.qp.X_op = O_absent;

  if (ignore_input ())
    return;

  if (input_line_pointer[0] == ';' && input_line_pointer[-1] == ';')
    {
      if (md.detect_dv && !md.explicit_mode)
	{
	  static int warned;

	  if (!warned)
	    {
	      warned = 1;
	      as_warn (_("Explicit stops are ignored in auto mode"));
	    }
	}
      else
	insn_group_break (1, 0, 0);
    }
  else if (input_line_pointer[-1] == '{')
    {
      if (md.manual_bundling)
	as_warn ("Found '{' when manual bundling is already turned on");
      else
	CURR_SLOT.manual_bundling_on = 1;
      md.manual_bundling = 1;

      /* Bundling is only acceptable in explicit mode
	 or when in default automatic mode.  */
      if (md.detect_dv && !md.explicit_mode)
	{
	  if (!md.mode_explicitly_set
	      && !md.default_explicit_mode)
	    dot_dv_mode ('E');
	  else
	    as_warn (_("Found '{' after explicit switch to automatic mode"));
	}
    }
  else if (input_line_pointer[-1] == '}')
    {
      if (!md.manual_bundling)
	as_warn ("Found '}' when manual bundling is off");
      else
	PREV_SLOT.manual_bundling_off = 1;
      md.manual_bundling = 0;

      /* switch back to automatic mode, if applicable */
      if (md.detect_dv
	  && md.explicit_mode
	  && !md.mode_explicitly_set
	  && !md.default_explicit_mode)
	dot_dv_mode ('A');
    }
}