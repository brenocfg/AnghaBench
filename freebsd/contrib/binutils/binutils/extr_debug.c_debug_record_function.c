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
struct TYPE_4__ {struct debug_function* function; } ;
struct debug_name {TYPE_2__ u; } ;
struct debug_handle {TYPE_1__* current_file; struct debug_function* current_block; struct debug_function* current_function; int /*<<< orphan*/ * current_unit; } ;
struct debug_function {struct debug_function* blocks; void* end; void* start; int /*<<< orphan*/ * return_type; } ;
struct debug_block {struct debug_block* blocks; void* end; void* start; int /*<<< orphan*/ * return_type; } ;
typedef  int /*<<< orphan*/ * debug_type ;
typedef  void* bfd_vma ;
typedef  scalar_t__ bfd_boolean ;
struct TYPE_3__ {int /*<<< orphan*/  globals; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_LINKAGE_GLOBAL ; 
 int /*<<< orphan*/  DEBUG_LINKAGE_STATIC ; 
 int /*<<< orphan*/  DEBUG_OBJECT_FUNCTION ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 struct debug_name* debug_add_to_namespace (struct debug_handle*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct debug_function*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmalloc (int) ; 

bfd_boolean
debug_record_function (void *handle, const char *name,
		       debug_type return_type, bfd_boolean global,
		       bfd_vma addr)
{
  struct debug_handle *info = (struct debug_handle *) handle;
  struct debug_function *f;
  struct debug_block *b;
  struct debug_name *n;

  if (name == NULL)
    name = "";
  if (return_type == NULL)
    return FALSE;

  if (info->current_unit == NULL)
    {
      debug_error (_("debug_record_function: no debug_set_filename call"));
      return FALSE;
    }

  f = (struct debug_function *) xmalloc (sizeof *f);
  memset (f, 0, sizeof *f);

  f->return_type = return_type;

  b = (struct debug_block *) xmalloc (sizeof *b);
  memset (b, 0, sizeof *b);

  b->start = addr;
  b->end = (bfd_vma) -1;

  f->blocks = b;

  info->current_function = f;
  info->current_block = b;

  /* FIXME: If we could handle nested functions, this would be the
     place: we would want to use a different namespace.  */
  n = debug_add_to_namespace (info,
			      &info->current_file->globals,
			      name,
			      DEBUG_OBJECT_FUNCTION,
			      (global
			       ? DEBUG_LINKAGE_GLOBAL
			       : DEBUG_LINKAGE_STATIC));
  if (n == NULL)
    return FALSE;

  n->u.function = f;

  return TRUE;
}