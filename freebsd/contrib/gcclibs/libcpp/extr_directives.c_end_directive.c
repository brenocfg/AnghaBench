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
struct TYPE_9__ {int save_comments; scalar_t__ angled_headers; scalar_t__ in_expression; scalar_t__ in_directive; int /*<<< orphan*/  prevent_expansion; scalar_t__ in_deferred_pragma; } ;
struct TYPE_8__ {int /*<<< orphan*/  base; } ;
struct TYPE_10__ {int /*<<< orphan*/ * directive; TYPE_2__ state; TYPE_1__ base_run; int /*<<< orphan*/  cur_token; TYPE_1__* cur_run; int /*<<< orphan*/  keep_tokens; } ;
typedef  TYPE_3__ cpp_reader ;

/* Variables and functions */
 scalar_t__ CPP_OPTION (TYPE_3__*,int /*<<< orphan*/ ) ; 
 size_t T_DEFINE ; 
 int /*<<< orphan*/  _cpp_remove_overlay (TYPE_3__*) ; 
 int /*<<< orphan*/  discard_comments ; 
 int /*<<< orphan*/ * dtable ; 
 int /*<<< orphan*/  skip_rest_of_line (TYPE_3__*) ; 
 int /*<<< orphan*/  traditional ; 

__attribute__((used)) static void
end_directive (cpp_reader *pfile, int skip_line)
{
  if (pfile->state.in_deferred_pragma)
    ;
  else if (CPP_OPTION (pfile, traditional))
    {
      /* Revert change of prepare_directive_trad.  */
      pfile->state.prevent_expansion--;

      if (pfile->directive != &dtable[T_DEFINE])
	_cpp_remove_overlay (pfile);
    }
  /* We don't skip for an assembler #.  */
  else if (skip_line)
    {
      skip_rest_of_line (pfile);
      if (!pfile->keep_tokens)
	{
	  pfile->cur_run = &pfile->base_run;
	  pfile->cur_token = pfile->base_run.base;
	}
    }

  /* Restore state.  */
  pfile->state.save_comments = ! CPP_OPTION (pfile, discard_comments);
  pfile->state.in_directive = 0;
  pfile->state.in_expression = 0;
  pfile->state.angled_headers = 0;
  pfile->directive = 0;
}