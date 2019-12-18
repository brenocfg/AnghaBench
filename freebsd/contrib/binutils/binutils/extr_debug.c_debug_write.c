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
struct debug_write_fns {int /*<<< orphan*/  (* start_source ) (void*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* start_compilation_unit ) (void*,int /*<<< orphan*/ ) ;} ;
struct debug_unit {struct debug_file* files; int /*<<< orphan*/  linenos; struct debug_unit* next; } ;
struct debug_name {struct debug_name* next; } ;
struct debug_handle {scalar_t__ current_write_lineno_index; int /*<<< orphan*/  current_write_lineno; struct debug_unit* units; int /*<<< orphan*/ * id_list; int /*<<< orphan*/  class_id; int /*<<< orphan*/  base_id; int /*<<< orphan*/  mark; } ;
struct debug_file {TYPE_1__* globals; int /*<<< orphan*/  filename; struct debug_file* next; } ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  scalar_t__ bfd_boolean ;
struct TYPE_2__ {struct debug_name* list; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  debug_write_linenos (struct debug_handle*,struct debug_write_fns const*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_write_name (struct debug_handle*,struct debug_write_fns const*,void*,struct debug_name*) ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (void*,int /*<<< orphan*/ ) ; 

bfd_boolean
debug_write (void *handle, const struct debug_write_fns *fns, void *fhandle)
{
  struct debug_handle *info = (struct debug_handle *) handle;
  struct debug_unit *u;

  /* We use a mark to tell whether we have already written out a
     particular name.  We use an integer, so that we don't have to
     clear the mark fields if we happen to write out the same
     information more than once.  */
  ++info->mark;

  /* The base_id field holds an ID value which will never be used, so
     that we can tell whether we have assigned an ID during this call
     to debug_write.  */
  info->base_id = info->class_id;

  /* We keep a linked list of classes for which was have assigned ID's
     during this call to debug_write.  */
  info->id_list = NULL;

  for (u = info->units; u != NULL; u = u->next)
    {
      struct debug_file *f;
      bfd_boolean first_file;

      info->current_write_lineno = u->linenos;
      info->current_write_lineno_index = 0;

      if (! (*fns->start_compilation_unit) (fhandle, u->files->filename))
	return FALSE;

      first_file = TRUE;
      for (f = u->files; f != NULL; f = f->next)
	{
	  struct debug_name *n;

	  if (first_file)
	    first_file = FALSE;
	  else if (! (*fns->start_source) (fhandle, f->filename))
	    return FALSE;

	  if (f->globals != NULL)
	    for (n = f->globals->list; n != NULL; n = n->next)
	      if (! debug_write_name (info, fns, fhandle, n))
		return FALSE;
	}

      /* Output any line number information which hasn't already been
         handled.  */
      if (! debug_write_linenos (info, fns, fhandle, (bfd_vma) -1))
	return FALSE;
    }

  return TRUE;
}