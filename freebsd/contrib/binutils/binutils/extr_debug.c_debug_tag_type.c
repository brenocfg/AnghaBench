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
struct debug_type {scalar_t__ kind; TYPE_1__ u; } ;
struct debug_named_type {struct debug_name* name; struct debug_type* type; } ;
struct TYPE_6__ {struct debug_type* tag; } ;
struct debug_name {TYPE_3__ u; int /*<<< orphan*/  name; } ;
struct debug_handle {TYPE_2__* current_file; } ;
typedef  struct debug_type* debug_type ;
struct TYPE_5__ {int /*<<< orphan*/  globals; } ;

/* Variables and functions */
 scalar_t__ DEBUG_KIND_TAGGED ; 
 int /*<<< orphan*/  DEBUG_LINKAGE_NONE ; 
 int /*<<< orphan*/  DEBUG_OBJECT_TAG ; 
 struct debug_type* DEBUG_TYPE_NULL ; 
 int /*<<< orphan*/  _ (char*) ; 
 struct debug_name* debug_add_to_namespace (struct debug_handle*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_error (int /*<<< orphan*/ ) ; 
 struct debug_type* debug_make_type (struct debug_handle*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct debug_named_type*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ xmalloc (int) ; 

debug_type
debug_tag_type (void *handle, const char *name, debug_type type)
{
  struct debug_handle *info = (struct debug_handle *) handle;
  struct debug_type *t;
  struct debug_named_type *n;
  struct debug_name *nm;

  if (name == NULL || type == NULL)
    return DEBUG_TYPE_NULL;

  if (info->current_file == NULL)
    {
      debug_error (_("debug_tag_type: no current file"));
      return DEBUG_TYPE_NULL;
    }

  if (type->kind == DEBUG_KIND_TAGGED)
    {
      if (strcmp (type->u.knamed->name->name, name) == 0)
	return type;
      debug_error (_("debug_tag_type: extra tag attempted"));
      return DEBUG_TYPE_NULL;
    }

  t = debug_make_type (info, DEBUG_KIND_TAGGED, 0);
  if (t == NULL)
    return DEBUG_TYPE_NULL;

  n = (struct debug_named_type *) xmalloc (sizeof *n);
  memset (n, 0, sizeof *n);

  n->type = type;

  t->u.knamed = n;

  /* We keep a global namespace of tags for each compilation unit.  I
     don't know if that is the right thing to do.  */

  nm = debug_add_to_namespace (info, &info->current_file->globals, name,
			       DEBUG_OBJECT_TAG, DEBUG_LINKAGE_NONE);
  if (nm == NULL)
    return DEBUG_TYPE_NULL;

  nm->u.tag = t;

  n->name = nm;

  return t;
}