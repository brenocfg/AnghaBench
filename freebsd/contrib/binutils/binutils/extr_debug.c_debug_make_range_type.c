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
struct TYPE_2__ {struct debug_range_type* krange; } ;
struct debug_type {TYPE_1__ u; } ;
struct debug_range_type {void* upper; void* lower; struct debug_type* type; } ;
struct debug_handle {int dummy; } ;
typedef  struct debug_type* debug_type ;
typedef  void* bfd_signed_vma ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_KIND_RANGE ; 
 struct debug_type* DEBUG_TYPE_NULL ; 
 struct debug_type* debug_make_type (struct debug_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct debug_range_type*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmalloc (int) ; 

debug_type
debug_make_range_type (void *handle, debug_type type, bfd_signed_vma lower,
		       bfd_signed_vma upper)
{
  struct debug_handle *info = (struct debug_handle *) handle;
  struct debug_type *t;
  struct debug_range_type *r;

  if (type == NULL)
    return DEBUG_TYPE_NULL;

  t = debug_make_type (info, DEBUG_KIND_RANGE, 0);
  if (t == NULL)
    return DEBUG_TYPE_NULL;

  r = (struct debug_range_type *) xmalloc (sizeof *r);
  memset (r, 0, sizeof *r);

  r->type = type;
  r->lower = lower;
  r->upper = upper;

  t->u.krange = r;

  return t;
}