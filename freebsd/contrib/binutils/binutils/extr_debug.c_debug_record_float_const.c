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
struct TYPE_2__ {double float_constant; } ;
struct debug_name {TYPE_1__ u; } ;
struct debug_handle {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_LINKAGE_NONE ; 
 int /*<<< orphan*/  DEBUG_OBJECT_FLOAT_CONSTANT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 struct debug_name* debug_add_to_current_namespace (struct debug_handle*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bfd_boolean
debug_record_float_const (void *handle, const char *name, double val)
{
  struct debug_handle *info = (struct debug_handle *) handle;
  struct debug_name *n;

  if (name == NULL)
    return FALSE;

  n = debug_add_to_current_namespace (info, name, DEBUG_OBJECT_FLOAT_CONSTANT,
				      DEBUG_LINKAGE_NONE);
  if (n == NULL)
    return FALSE;

  n->u.float_constant = val;

  return TRUE;
}