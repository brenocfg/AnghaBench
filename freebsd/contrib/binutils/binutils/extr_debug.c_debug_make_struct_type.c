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
struct TYPE_2__ {struct debug_class_type* kclass; } ;
struct debug_type {TYPE_1__ u; } ;
struct debug_handle {int dummy; } ;
struct debug_class_type {int /*<<< orphan*/ * fields; } ;
typedef  struct debug_type* debug_type ;
typedef  int /*<<< orphan*/  debug_field ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  scalar_t__ bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_KIND_STRUCT ; 
 int /*<<< orphan*/  DEBUG_KIND_UNION ; 
 struct debug_type* DEBUG_TYPE_NULL ; 
 struct debug_type* debug_make_type (struct debug_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct debug_class_type*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmalloc (int) ; 

debug_type
debug_make_struct_type (void *handle, bfd_boolean structp, bfd_vma size,
			debug_field *fields)
{
  struct debug_handle *info = (struct debug_handle *) handle;
  struct debug_type *t;
  struct debug_class_type *c;

  t = debug_make_type (info,
		       structp ? DEBUG_KIND_STRUCT : DEBUG_KIND_UNION,
		       size);
  if (t == NULL)
    return DEBUG_TYPE_NULL;

  c = (struct debug_class_type *) xmalloc (sizeof *c);
  memset (c, 0, sizeof *c);

  c->fields = fields;

  t->u.kclass = c;

  return t;
}