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
struct stab_pending_var {char const* name; int kind; int /*<<< orphan*/  val; int /*<<< orphan*/  type; struct stab_pending_var* next; } ;
struct stab_handle {scalar_t__ gcc_compiled; struct stab_pending_var* pending; scalar_t__ n_opt_found; int /*<<< orphan*/  within_function; } ;
typedef  enum debug_var_kind { ____Placeholder_debug_var_kind } debug_var_kind ;
typedef  int /*<<< orphan*/  debug_type ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int DEBUG_GLOBAL ; 
 int DEBUG_STATIC ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debug_record_variable (void*,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct stab_pending_var*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static bfd_boolean
stab_record_variable (void *dhandle, struct stab_handle *info,
		      const char *name, debug_type type,
		      enum debug_var_kind kind, bfd_vma val)
{
  struct stab_pending_var *v;

  if ((kind == DEBUG_GLOBAL || kind == DEBUG_STATIC)
      || ! info->within_function
      || (info->gcc_compiled == 0 && info->n_opt_found))
    return debug_record_variable (dhandle, name, type, kind, val);

  v = (struct stab_pending_var *) xmalloc (sizeof *v);
  memset (v, 0, sizeof *v);

  v->next = info->pending;
  v->name = name;
  v->type = type;
  v->kind = kind;
  v->val = val;
  info->pending = v;

  return TRUE;
}