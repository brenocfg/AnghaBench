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
struct TYPE_2__ {struct debug_set_type* kset; } ;
struct debug_type {TYPE_1__ u; } ;
struct debug_set_type {int /*<<< orphan*/  bitstringp; struct debug_type* type; } ;
struct debug_handle {int dummy; } ;
typedef  struct debug_type* debug_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_KIND_SET ; 
 struct debug_type* DEBUG_TYPE_NULL ; 
 struct debug_type* debug_make_type (struct debug_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct debug_set_type*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmalloc (int) ; 

debug_type
debug_make_set_type (void *handle, debug_type type, bfd_boolean bitstringp)
{
  struct debug_handle *info = (struct debug_handle *) handle;
  struct debug_type *t;
  struct debug_set_type *s;

  if (type == NULL)
    return DEBUG_TYPE_NULL;

  t = debug_make_type (info, DEBUG_KIND_SET, 0);
  if (t == NULL)
    return DEBUG_TYPE_NULL;

  s = (struct debug_set_type *) xmalloc (sizeof *s);
  memset (s, 0, sizeof *s);

  s->type = type;
  s->bitstringp = bitstringp;

  t->u.kset = s;

  return t;
}