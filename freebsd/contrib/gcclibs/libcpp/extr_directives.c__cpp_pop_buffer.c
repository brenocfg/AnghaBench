#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct if_stack {size_t type; int /*<<< orphan*/  line; struct if_stack* next; } ;
struct _cpp_file {int dummy; } ;
struct TYPE_10__ {scalar_t__ skipping; } ;
struct TYPE_11__ {int /*<<< orphan*/  buffer_ob; TYPE_3__* buffer; TYPE_1__ state; } ;
typedef  TYPE_2__ cpp_reader ;
struct TYPE_12__ {int /*<<< orphan*/  notes; struct TYPE_12__* prev; struct if_stack* if_stack; struct _cpp_file* file; } ;
typedef  TYPE_3__ cpp_buffer ;
struct TYPE_13__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_DL_ERROR ; 
 int /*<<< orphan*/  LC_LEAVE ; 
 int /*<<< orphan*/  _cpp_do_file_change (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cpp_pop_file_buffer (TYPE_2__*,struct _cpp_file*) ; 
 int /*<<< orphan*/  cpp_error_with_line (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_5__* dtable ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,TYPE_3__*) ; 

void
_cpp_pop_buffer (cpp_reader *pfile)
{
  cpp_buffer *buffer = pfile->buffer;
  struct _cpp_file *inc = buffer->file;
  struct if_stack *ifs;

  /* Walk back up the conditional stack till we reach its level at
     entry to this file, issuing error messages.  */
  for (ifs = buffer->if_stack; ifs; ifs = ifs->next)
    cpp_error_with_line (pfile, CPP_DL_ERROR, ifs->line, 0,
			 "unterminated #%s", dtable[ifs->type].name);

  /* In case of a missing #endif.  */
  pfile->state.skipping = 0;

  /* _cpp_do_file_change expects pfile->buffer to be the new one.  */
  pfile->buffer = buffer->prev;

  free (buffer->notes);

  /* Free the buffer object now; we may want to push a new buffer
     in _cpp_push_next_include_file.  */
  obstack_free (&pfile->buffer_ob, buffer);

  if (inc)
    {
      _cpp_pop_file_buffer (pfile, inc);

      _cpp_do_file_change (pfile, LC_LEAVE, 0, 0, 0);
    }
}