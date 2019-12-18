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
struct if_stack {scalar_t__ was_skipping; struct if_stack* next; scalar_t__ mi_cmacro; } ;
struct TYPE_8__ {scalar_t__ skipping; } ;
struct TYPE_9__ {int mi_valid; int /*<<< orphan*/  buffer_ob; TYPE_1__ state; scalar_t__ mi_cmacro; TYPE_3__* buffer; } ;
typedef  TYPE_2__ cpp_reader ;
struct TYPE_10__ {struct if_stack* if_stack; } ;
typedef  TYPE_3__ cpp_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_DL_ERROR ; 
 scalar_t__ CPP_OPTION (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_eol (TYPE_2__*) ; 
 int /*<<< orphan*/  cpp_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,struct if_stack*) ; 
 int /*<<< orphan*/  warn_endif_labels ; 

__attribute__((used)) static void
do_endif (cpp_reader *pfile)
{
  cpp_buffer *buffer = pfile->buffer;
  struct if_stack *ifs = buffer->if_stack;

  if (ifs == NULL)
    cpp_error (pfile, CPP_DL_ERROR, "#endif without #if");
  else
    {
      /* Only check EOL if was not originally skipping.  */
      if (!ifs->was_skipping && CPP_OPTION (pfile, warn_endif_labels))
	check_eol (pfile);

      /* If potential control macro, we go back outside again.  */
      if (ifs->next == 0 && ifs->mi_cmacro)
	{
	  pfile->mi_valid = true;
	  pfile->mi_cmacro = ifs->mi_cmacro;
	}

      buffer->if_stack = ifs->next;
      pfile->state.skipping = ifs->was_skipping;
      obstack_free (&pfile->buffer_ob, ifs);
    }
}