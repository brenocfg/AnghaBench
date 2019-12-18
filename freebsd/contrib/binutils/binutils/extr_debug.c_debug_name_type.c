#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct debug_named_type* knamed; } ;
struct debug_type {TYPE_1__ u; } ;
struct debug_named_type {struct debug_name* name; struct debug_type* type; } ;
struct TYPE_6__ {struct debug_type* type; } ;
struct debug_name {TYPE_3__ u; } ;
struct debug_handle {TYPE_2__* current_file; int /*<<< orphan*/ * current_unit; } ;
typedef  struct debug_type* debug_type ;
struct TYPE_5__ {int /*<<< orphan*/  globals; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_KIND_NAMED ; 
 int /*<<< orphan*/  DEBUG_LINKAGE_NONE ; 
 int /*<<< orphan*/  DEBUG_OBJECT_TYPE ; 
 struct debug_type* DEBUG_TYPE_NULL ; 
 int /*<<< orphan*/  _ (char*) ; 
 struct debug_name* debug_add_to_namespace (struct debug_handle*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_error (int /*<<< orphan*/ ) ; 
 struct debug_type* debug_make_type (struct debug_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct debug_named_type*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmalloc (int) ; 

debug_type
debug_name_type (void *handle, const char *name, debug_type type)
{
  struct debug_handle *info = (struct debug_handle *) handle;
  struct debug_type *t;
  struct debug_named_type *n;
  struct debug_name *nm;

  if (name == NULL || type == NULL)
    return DEBUG_TYPE_NULL;

  if (info->current_unit == NULL
      || info->current_file == NULL)
    {
      debug_error (_("debug_name_type: no current file"));
      return DEBUG_TYPE_NULL;
    }

  t = debug_make_type (info, DEBUG_KIND_NAMED, 0);
  if (t == NULL)
    return DEBUG_TYPE_NULL;

  n = (struct debug_named_type *) xmalloc (sizeof *n);
  memset (n, 0, sizeof *n);

  n->type = type;

  t->u.knamed = n;

  /* We always add the name to the global namespace.  This is probably
     wrong in some cases, but it seems to be right for stabs.  FIXME.  */

  nm = debug_add_to_namespace (info, &info->current_file->globals, name,
			       DEBUG_OBJECT_TYPE, DEBUG_LINKAGE_NONE);
  if (nm == NULL)
    return DEBUG_TYPE_NULL;

  nm->u.type = t;

  n->name = nm;

  return t;
}