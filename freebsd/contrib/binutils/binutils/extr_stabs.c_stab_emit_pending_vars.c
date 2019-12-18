#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct stab_pending_var {struct stab_pending_var* next; int /*<<< orphan*/  val; int /*<<< orphan*/  kind; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct stab_handle {struct stab_pending_var* pending; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debug_record_variable (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct stab_pending_var*) ; 

__attribute__((used)) static bfd_boolean
stab_emit_pending_vars (void *dhandle, struct stab_handle *info)
{
  struct stab_pending_var *v;

  v = info->pending;
  while (v != NULL)
    {
      struct stab_pending_var *next;

      if (! debug_record_variable (dhandle, v->name, v->type, v->kind, v->val))
	return FALSE;

      next = v->next;
      free (v);
      v = next;
    }

  info->pending = NULL;

  return TRUE;
}