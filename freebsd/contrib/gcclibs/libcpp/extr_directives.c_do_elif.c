#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct if_stack {scalar_t__ type; int skip_elses; scalar_t__ mi_cmacro; int /*<<< orphan*/  line; } ;
struct TYPE_8__ {int skipping; } ;
struct TYPE_9__ {TYPE_1__ state; TYPE_3__* buffer; } ;
typedef  TYPE_2__ cpp_reader ;
struct TYPE_10__ {struct if_stack* if_stack; } ;
typedef  TYPE_3__ cpp_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_DL_ERROR ; 
 scalar_t__ T_ELIF ; 
 scalar_t__ T_ELSE ; 
 int /*<<< orphan*/  _cpp_parse_expr (TYPE_2__*) ; 
 int /*<<< orphan*/  cpp_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cpp_error_with_line (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
do_elif (cpp_reader *pfile)
{
  cpp_buffer *buffer = pfile->buffer;
  struct if_stack *ifs = buffer->if_stack;

  if (ifs == NULL)
    cpp_error (pfile, CPP_DL_ERROR, "#elif without #if");
  else
    {
      if (ifs->type == T_ELSE)
	{
	  cpp_error (pfile, CPP_DL_ERROR, "#elif after #else");
	  cpp_error_with_line (pfile, CPP_DL_ERROR, ifs->line, 0,
			       "the conditional began here");
	}
      ifs->type = T_ELIF;

      /* Only evaluate this if we aren't skipping elses.  During
	 evaluation, set skipping to false to get lexer warnings.  */
      if (ifs->skip_elses)
	pfile->state.skipping = 1;
      else
	{
	  pfile->state.skipping = 0;
	  pfile->state.skipping = ! _cpp_parse_expr (pfile);
	  ifs->skip_elses = ! pfile->state.skipping;
	}

      /* Invalidate any controlling macro.  */
      ifs->mi_cmacro = 0;
    }
}