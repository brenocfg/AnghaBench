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
struct TYPE_2__ {struct debug_array_type* karray; } ;
struct debug_type {TYPE_1__ u; } ;
struct debug_handle {int dummy; } ;
struct debug_array_type {int /*<<< orphan*/  stringp; void* upper; void* lower; struct debug_type* range_type; struct debug_type* element_type; } ;
typedef  struct debug_type* debug_type ;
typedef  void* bfd_signed_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_KIND_ARRAY ; 
 struct debug_type* DEBUG_TYPE_NULL ; 
 struct debug_type* debug_make_type (struct debug_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct debug_array_type*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmalloc (int) ; 

debug_type
debug_make_array_type (void *handle, debug_type element_type,
		       debug_type range_type, bfd_signed_vma lower,
		       bfd_signed_vma upper, bfd_boolean stringp)
{
  struct debug_handle *info = (struct debug_handle *) handle;
  struct debug_type *t;
  struct debug_array_type *a;

  if (element_type == NULL || range_type == NULL)
    return DEBUG_TYPE_NULL;

  t = debug_make_type (info, DEBUG_KIND_ARRAY, 0);
  if (t == NULL)
    return DEBUG_TYPE_NULL;

  a = (struct debug_array_type *) xmalloc (sizeof *a);
  memset (a, 0, sizeof *a);

  a->element_type = element_type;
  a->range_type = range_type;
  a->lower = lower;
  a->upper = upper;
  a->stringp = stringp;

  t->u.karray = a;

  return t;
}