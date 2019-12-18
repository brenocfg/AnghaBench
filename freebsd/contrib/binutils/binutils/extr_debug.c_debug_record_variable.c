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
struct debug_variable {int kind; int /*<<< orphan*/  val; int /*<<< orphan*/ * type; } ;
struct debug_namespace {int dummy; } ;
struct TYPE_6__ {struct debug_variable* variable; } ;
struct debug_name {TYPE_3__ u; } ;
struct debug_handle {TYPE_2__* current_block; TYPE_1__* current_file; int /*<<< orphan*/ * current_unit; } ;
typedef  enum debug_var_kind { ____Placeholder_debug_var_kind } debug_var_kind ;
typedef  enum debug_object_linkage { ____Placeholder_debug_object_linkage } debug_object_linkage ;
typedef  int /*<<< orphan*/ * debug_type ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_5__ {struct debug_namespace* locals; } ;
struct TYPE_4__ {struct debug_namespace* globals; } ;

/* Variables and functions */
 int DEBUG_GLOBAL ; 
 int DEBUG_LINKAGE_AUTOMATIC ; 
 int DEBUG_LINKAGE_GLOBAL ; 
 int DEBUG_LINKAGE_STATIC ; 
 int /*<<< orphan*/  DEBUG_OBJECT_VARIABLE ; 
 int DEBUG_STATIC ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 struct debug_name* debug_add_to_namespace (struct debug_handle*,struct debug_namespace**,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debug_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct debug_variable*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmalloc (int) ; 

bfd_boolean
debug_record_variable (void *handle, const char *name, debug_type type,
		       enum debug_var_kind kind, bfd_vma val)
{
  struct debug_handle *info = (struct debug_handle *) handle;
  struct debug_namespace **nsp;
  enum debug_object_linkage linkage;
  struct debug_name *n;
  struct debug_variable *v;

  if (name == NULL || type == NULL)
    return FALSE;

  if (info->current_unit == NULL
      || info->current_file == NULL)
    {
      debug_error (_("debug_record_variable: no current file"));
      return FALSE;
    }

  if (kind == DEBUG_GLOBAL || kind == DEBUG_STATIC)
    {
      nsp = &info->current_file->globals;
      if (kind == DEBUG_GLOBAL)
	linkage = DEBUG_LINKAGE_GLOBAL;
      else
	linkage = DEBUG_LINKAGE_STATIC;
    }
  else
    {
      if (info->current_block == NULL)
	nsp = &info->current_file->globals;
      else
	nsp = &info->current_block->locals;
      linkage = DEBUG_LINKAGE_AUTOMATIC;
    }

  n = debug_add_to_namespace (info, nsp, name, DEBUG_OBJECT_VARIABLE, linkage);
  if (n == NULL)
    return FALSE;

  v = (struct debug_variable *) xmalloc (sizeof *v);
  memset (v, 0, sizeof *v);

  v->kind = kind;
  v->type = type;
  v->val = val;

  n->u.variable = v;

  return TRUE;
}