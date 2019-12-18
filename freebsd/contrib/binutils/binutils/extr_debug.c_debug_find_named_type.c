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
struct TYPE_8__ {int /*<<< orphan*/  type; } ;
struct debug_name {scalar_t__ kind; char const* name; TYPE_4__ u; struct debug_name* next; } ;
struct debug_handle {TYPE_2__* current_unit; struct debug_block* current_block; } ;
struct debug_file {TYPE_3__* globals; struct debug_file* next; } ;
struct debug_block {TYPE_1__* locals; struct debug_block* parent; } ;
typedef  int /*<<< orphan*/  debug_type ;
struct TYPE_7__ {struct debug_name* list; } ;
struct TYPE_6__ {struct debug_file* files; } ;
struct TYPE_5__ {struct debug_name* list; } ;

/* Variables and functions */
 scalar_t__ DEBUG_OBJECT_TYPE ; 
 int /*<<< orphan*/  DEBUG_TYPE_NULL ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  debug_error (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

debug_type
debug_find_named_type (void *handle, const char *name)
{
  struct debug_handle *info = (struct debug_handle *) handle;
  struct debug_block *b;
  struct debug_file *f;

  /* We only search the current compilation unit.  I don't know if
     this is right or not.  */

  if (info->current_unit == NULL)
    {
      debug_error (_("debug_find_named_type: no current compilation unit"));
      return DEBUG_TYPE_NULL;
    }

  for (b = info->current_block; b != NULL; b = b->parent)
    {
      if (b->locals != NULL)
	{
	  struct debug_name *n;

	  for (n = b->locals->list; n != NULL; n = n->next)
	    {
	      if (n->kind == DEBUG_OBJECT_TYPE
		  && n->name[0] == name[0]
		  && strcmp (n->name, name) == 0)
		return n->u.type;
	    }
	}
    }

  for (f = info->current_unit->files; f != NULL; f = f->next)
    {
      if (f->globals != NULL)
	{
	  struct debug_name *n;

	  for (n = f->globals->list; n != NULL; n = n->next)
	    {
	      if (n->kind == DEBUG_OBJECT_TYPE
		  && n->name[0] == name[0]
		  && strcmp (n->name, name) == 0)
		return n->u.type;
	    }
	}
    }

  return DEBUG_TYPE_NULL;
}