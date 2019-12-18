#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct if_stack {scalar_t__ type; int skip_elses; int /*<<< orphan*/  was_skipping; scalar_t__ mi_cmacro; int /*<<< orphan*/  line; } ;
struct TYPE_9__ {int skipping; } ;
struct TYPE_10__ {TYPE_1__ state; TYPE_3__* buffer; } ;
typedef  TYPE_2__ cpp_reader ;
struct TYPE_11__ {struct if_stack* if_stack; } ;
typedef  TYPE_3__ cpp_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_DL_ERROR ; 
 scalar_t__ CPP_OPTION (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ T_ELSE ; 
 int /*<<< orphan*/  check_eol (TYPE_2__*) ; 
 int /*<<< orphan*/  cpp_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cpp_error_with_line (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  warn_endif_labels ; 

__attribute__((used)) static void
do_else (cpp_reader *pfile)
{
  cpp_buffer *buffer = pfile->buffer;
  struct if_stack *ifs = buffer->if_stack;

  if (ifs == NULL)
    cpp_error (pfile, CPP_DL_ERROR, "#else without #if");
  else
    {
      if (ifs->type == T_ELSE)
	{
	  cpp_error (pfile, CPP_DL_ERROR, "#else after #else");
	  cpp_error_with_line (pfile, CPP_DL_ERROR, ifs->line, 0,
			       "the conditional began here");
	}
      ifs->type = T_ELSE;

      /* Skip any future (erroneous) #elses or #elifs.  */
      pfile->state.skipping = ifs->skip_elses;
      ifs->skip_elses = true;

      /* Invalidate any controlling macro.  */
      ifs->mi_cmacro = 0;

      /* Only check EOL if was not originally skipping.  */
      if (!ifs->was_skipping && CPP_OPTION (pfile, warn_endif_labels))
	check_eol (pfile);
    }
}