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
struct TYPE_2__ {struct debug_indirect_type* kindirect; } ;
struct debug_type {TYPE_1__ u; } ;
struct debug_indirect_type {char const* tag; struct debug_type** slot; } ;
struct debug_handle {int dummy; } ;
typedef  struct debug_type* debug_type ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_KIND_INDIRECT ; 
 struct debug_type* DEBUG_TYPE_NULL ; 
 struct debug_type* debug_make_type (struct debug_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct debug_indirect_type*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmalloc (int) ; 

debug_type
debug_make_indirect_type (void *handle, debug_type *slot, const char *tag)
{
  struct debug_handle *info = (struct debug_handle *) handle;
  struct debug_type *t;
  struct debug_indirect_type *i;

  t = debug_make_type (info, DEBUG_KIND_INDIRECT, 0);
  if (t == NULL)
    return DEBUG_TYPE_NULL;

  i = (struct debug_indirect_type *) xmalloc (sizeof *i);
  memset (i, 0, sizeof *i);

  i->slot = slot;
  i->tag = tag;

  t->u.kindirect = i;

  return t;
}