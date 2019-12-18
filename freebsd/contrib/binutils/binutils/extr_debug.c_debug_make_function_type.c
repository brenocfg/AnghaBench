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
struct TYPE_2__ {struct debug_function_type* kfunction; } ;
struct debug_type {TYPE_1__ u; } ;
struct debug_handle {int dummy; } ;
struct debug_function_type {int /*<<< orphan*/  varargs; struct debug_type** arg_types; struct debug_type* return_type; } ;
typedef  struct debug_type* debug_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_KIND_FUNCTION ; 
 struct debug_type* DEBUG_TYPE_NULL ; 
 struct debug_type* debug_make_type (struct debug_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct debug_function_type*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmalloc (int) ; 

debug_type
debug_make_function_type (void *handle, debug_type type,
			  debug_type *arg_types, bfd_boolean varargs)
{
  struct debug_handle *info = (struct debug_handle *) handle;
  struct debug_type *t;
  struct debug_function_type *f;

  if (type == NULL)
    return DEBUG_TYPE_NULL;

  t = debug_make_type (info, DEBUG_KIND_FUNCTION, 0);
  if (t == NULL)
    return DEBUG_TYPE_NULL;

  f = (struct debug_function_type *) xmalloc (sizeof *f);
  memset (f, 0, sizeof *f);

  f->return_type = type;
  f->arg_types = arg_types;
  f->varargs = varargs;

  t->u.kfunction = f;

  return t;
}