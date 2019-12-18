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
struct debug_typed_constant {int /*<<< orphan*/  val; int /*<<< orphan*/ * type; } ;
struct TYPE_2__ {struct debug_typed_constant* typed_constant; } ;
struct debug_name {TYPE_1__ u; } ;
struct debug_handle {int dummy; } ;
typedef  int /*<<< orphan*/ * debug_type ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_LINKAGE_NONE ; 
 int /*<<< orphan*/  DEBUG_OBJECT_TYPED_CONSTANT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 struct debug_name* debug_add_to_current_namespace (struct debug_handle*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct debug_typed_constant*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmalloc (int) ; 

bfd_boolean
debug_record_typed_const (void *handle, const char *name, debug_type type,
			  bfd_vma val)
{
  struct debug_handle *info = (struct debug_handle *) handle;
  struct debug_name *n;
  struct debug_typed_constant *tc;

  if (name == NULL || type == NULL)
    return FALSE;

  n = debug_add_to_current_namespace (info, name, DEBUG_OBJECT_TYPED_CONSTANT,
				      DEBUG_LINKAGE_NONE);
  if (n == NULL)
    return FALSE;

  tc = (struct debug_typed_constant *) xmalloc (sizeof *tc);
  memset (tc, 0, sizeof *tc);

  tc->type = type;
  tc->val = val;

  n->u.typed_constant = tc;

  return TRUE;
}