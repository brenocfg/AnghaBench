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
struct debug_parameter {char const* name; int kind; struct debug_parameter* next; int /*<<< orphan*/  val; int /*<<< orphan*/ * type; } ;
struct debug_handle {TYPE_1__* current_function; int /*<<< orphan*/ * current_unit; } ;
typedef  enum debug_parm_kind { ____Placeholder_debug_parm_kind } debug_parm_kind ;
typedef  int /*<<< orphan*/ * debug_type ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_2__ {struct debug_parameter* parameters; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  debug_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct debug_parameter*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmalloc (int) ; 

bfd_boolean
debug_record_parameter (void *handle, const char *name, debug_type type,
			enum debug_parm_kind kind, bfd_vma val)
{
  struct debug_handle *info = (struct debug_handle *) handle;
  struct debug_parameter *p, **pp;

  if (name == NULL || type == NULL)
    return FALSE;

  if (info->current_unit == NULL
      || info->current_function == NULL)
    {
      debug_error (_("debug_record_parameter: no current function"));
      return FALSE;
    }

  p = (struct debug_parameter *) xmalloc (sizeof *p);
  memset (p, 0, sizeof *p);

  p->name = name;
  p->type = type;
  p->kind = kind;
  p->val = val;

  for (pp = &info->current_function->parameters;
       *pp != NULL;
       pp = &(*pp)->next)
    ;
  *pp = p;

  return TRUE;
}